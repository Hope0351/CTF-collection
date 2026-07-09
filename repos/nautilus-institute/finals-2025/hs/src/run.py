import os
import yaml
import logfire
import ipaddress
import streamlit as st
from pathlib import Path
from dotenv import load_dotenv

from hs import HSBaseline, HIGHLIGHTER_PROMPT
from utils import get_team_id, RateLimitException
from scoring import get_next_prompt, set_prompt_solved, ALL_PROMPTS
from streamlit.runtime.scriptrunner import get_script_run_ctx

load_dotenv()

TEMPERATURE = 0.3
MAX_QUESTION_LENGTH = 1000
MODEL = "gpt-4.1-mini"

# Cache level configuration to avoid repeated file reads
@st.cache_data
def load_levels_config():
    with open("levels.yaml", "r") as f:
        return yaml.safe_load(f)

# Cache document content to avoid repeated file reads
@st.cache_data
def load_document(doc_fname: str) -> str:
    return (Path("data/") / f"{doc_fname}.md").read_text()

def load_level() -> str:
    levels = load_levels_config()
    if level := os.getenv("LEVEL"):
        if level not in levels:
            raise Exception(f"Invalid LEVEL: {level}. Available levels: {list(levels.keys())}")
        doc_fname = levels[level]["document"]
        min_highlighted_words = levels[level]["min_highlighted_words"]
        st.session_state["level"] = level
        st.session_state["topic"] = levels[level]["document"].replace("-", " ")
        st.session_state["doc"] = load_document(doc_fname)
        st.session_state["min_highlighted_words"] = min_highlighted_words
        st.session_state["initialized"] = True
        return level
    else:
        raise Exception("Please specify LEVEL environment variable")

def get_team():
    """Get team identifier based on the network subnet of remote IP."""
    try:
        ctx = get_script_run_ctx()
        if ctx is None:
            return None

        session_info = st.runtime.get_instance().get_client(ctx.session_id)
        if session_info is None:
            return None
    except Exception as e:
        return None

    remote_ip = session_info.request.remote_ip

    if remote_ip is None:
        raise Exception("Remote IP is not available")

    try:
        # Parse the IP address
        ip = ipaddress.ip_address(remote_ip)
        # Get the /24 network (e.g., 10.0.1.0/24 for IP 10.0.1.123)
        network = ipaddress.ip_network(f"{ip}/24", strict=False)
        # Return the network as string (e.g., "10.0.1.0/24")
        return str(network)
    except Exception as e:
        return None

def handle_chat(current_prompt_id, team, team_id):
    # Chat
    st.title(f"I answer questions about {st.session_state['topic']}")
    st.caption(
        "I heard of this new H&S thing. "
        "Here's how it works. There's two LLMs: a highlighter selects portions of the document based on your question, "
        "and one summarizes the highlighted parts. You see the summarized output. "
        "If I implemented this defense correctly, "
        f"my chatbot should never reveal the flag. (min_highlighted_words: {st.session_state['min_highlighted_words']}. {current_prompt_id}/{len(ALL_PROMPTS)}). "
        "**NOTE**: You're rate-limited to what amounts to roughly 10-20 questions per minute."
    )
    if current_prompt_id is None:
        st.title("Your team has solved all challenges for this level.")
        return

    # Init chat
    if "messages" not in st.session_state:
        st.session_state["messages"] = [
            {"role": "assistant", "content": "How can I help you?"}
        ]

    # Handle prompt
    if not current_prompt_id in ALL_PROMPTS:
        logfire.error(f"Invalid prompt ID: {current_prompt_id}")
        raise Exception("This shouldn't happen")
    current_prompt = ALL_PROMPTS[current_prompt_id]
    logfire.info(f"Current prompt: {current_prompt_id} - {current_prompt}")

    # Display message history
    for msg in st.session_state.messages:
        st.chat_message(msg["role"]).write(msg["content"])

    # Handle new messages
    if question := st.chat_input():
        question = question[:MAX_QUESTION_LENGTH]
        st.chat_message("user").write(question)
        st.session_state.messages.append({"role": "user", "content": question})

        with st.spinner():
            # Cache the HSBaseline instance in session state for reuse
            cache_key = f"hs_model_{current_prompt_id}_{st.session_state['min_highlighted_words']}"
            if cache_key not in st.session_state:
                st.session_state[cache_key] = HSBaseline(
                    highlighter_model_name=MODEL,
                    summarizer_model_name=MODEL,
                    temperature=TEMPERATURE,
                    min_highlighted_words=st.session_state["min_highlighted_words"],
                    highlighter_prompt=f"{HIGHLIGHTER_PROMPT}\n{ALL_PROMPTS[current_prompt_id]}",
                )
            hs = st.session_state[cache_key]

            try:
                response = hs.call_model(
                    team_id=team_id,
                    context_str=st.session_state["doc"],
                    question_str=question,
                )
            except RateLimitException as e:
                st.error(f"Rate limit exceeded. Please try again later.")
                return
            except Exception as e:
                st.error(f"An error occurred: {str(e)}")
                logfire.error(f"Error processing question: {str(e)}", team=team)
                return


        logfire.info(f"Response", response=response.model_dump())

        # Was the flag requested?
        got_flag = False
        final_response = response.answer_pred
        if guessed_question := response.summarizer_llm_guessed_question:
            if "FLAG" == guessed_question.strip():
                got_flag = True
                logfire.warn(f"Team {team} got the flag ({current_prompt_id}).", _tags={"flag"})
                final_response = f"Well done! A flag has been awarded. You solved {current_prompt_id}/{len(ALL_PROMPTS)}. Keep going!"
                set_prompt_solved(team, current_prompt_id)

        st.session_state.messages.append(
            {"role": "assistant", "content": final_response}
        )
        st.chat_message("assistant").write(final_response)

        return got_flag

def main():
    # Initialize session state early to avoid repeated checks
    if "initialized" not in st.session_state:
        st.session_state["initialized"] = False
        st.session_state["messages"] = [{"role": "assistant", "content": "How can I help you?"}]
    
    team = get_team()
    team_id = get_team_id(team) if team else None
    if team_id is None or team is None:
        st.error("Failed to determine your team ID. Please get in touch.")
        logfire.error("Failed to determine team ID from remote IP.")
        return

    with logfire.span(f"Serving team {team}", _tags={ team }) as span:
        current_prompt_id = get_next_prompt(team)
        span.tags += tuple([str(current_prompt_id)])
        got_flag = handle_chat(current_prompt_id, team, team_id)
        if got_flag:
            span.tags += tuple(["flag"])


if __name__ == "__main__":
    st.set_page_config(
        page_title="HS",
        page_icon="🌎",
        layout="centered",
    )
    
    # Initialize level only once
    if "level" not in st.session_state:
        level = load_level()
    else:
        level = st.session_state["level"]

    # Configure logfire only once per session
    if "logfire_configured" not in st.session_state:
        # Disabled after DEF CON
        #logfire.configure(token=os.getenv("LOGFIRE_TOKEN"), service_name=f"H&S ({level})")
        st.session_state["logfire_configured"] = True
        logfire.info("Starting H&S challenge")

    main()