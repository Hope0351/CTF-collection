# :globe_with_meridians: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/open-source-tool-for-ai-specific-threat-modeling-fast-context-aware-and-developer-friendly-2c047fdc1781)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Open Source Tool for AI-Specific Threat Modeling — Fast, Context-Aware, and Developer-Friendly


Artificial Intelligence is transforming every sector — from healthcare and finance to marketing and national security. But while the hype around AI continues to skyrocket, the risks are quietly multiplying in the background. Traditional security practices, which evolved around web apps, APIs, or infrastructure, often fall short when applied to AI systems. The threats in AI go beyond injection and DoS — they include things like model inversion, data poisoning, prompt manipulation, and misuse through chained components.


That’s where **AI Threat Modeling** comes in. And more importantly, why we need the right tools to do it consistently and thoroughly.


In this article, I introduce an open-source project I recently released: the AI [Threat Modeling Assistant](https://www.aimlthreats.com). It’s a lightweight, developer-friendly tool that helps engineers and security teams model AI-specific threats by simply answering a few structured questions. It’s not another checklist — it’s a rules-driven, context-aware engine that outputs detailed threats, maps them to MITRE ATLAS and the NIST CIA+Abuse taxonomy, and even highlights chained attack paths.

## Why We Need a New Threat Modeling Tool for AI


Security teams have been using frameworks like STRIDE or PASTA to model threats for years. But these frameworks were not built with AI in mind.


Take STRIDE: it assumes an application has clear entry points, defined user roles, and unidirectional data flow. Now imagine you’re threat modeling a Retrieval-Augmented Generation (RAG) system that pulls real-time data from untrusted sources and feeds it into an LLM via prompt templates. The attack surface is fundamentally different.


Here are some **specific challenges AI systems introduce**:


- **Prompt Injection and Model Manipulation**: Especially in generative AI, untrusted inputs can influence model behavior unpredictably.

- **Training Data Poisoning**: Attackers can inject malicious samples into training datasets, compromising future predictions.

- **Model Theft and Inversion**: With sufficient access, adversaries can extract training data or clone the model altogether.

- **Infrastructure Chaining**: Many AI solutions include a chain of components — vector databases, API gateways, orchestration layers — all with their own risks.

- **Regulatory Misalignment**: LLM misuse can trigger violations of GDPR, HIPAA, or AI-specific guidance like the EU AI Act.


And yet, most development teams are either skipping threat modeling entirely or trying to repurpose traditional methods. We need a tool that:


- Understands AI building blocks (models, data pipelines, interfaces),

- Maps threats in a deterministic, repeatable way,

- Offers actionable mitigations, not just high-level flags,

- Highlights where compliance is being broken,

- Can be run easily by developers — not just security engineers.


This is what the **AI Threat Modeling Assistant** aims to solve.

### **What the Tool Does (and Doesn’t Do)**


The [AI Threat Modeling Assistant](https://www.aimlthreats.com) is a free, open-source tool built with Streamlit. It’s designed to be dead simple to use: answer a structured set of questions about your AI system, and it returns a detailed threat model.


Under the hood, it uses a **rule-based engine** to analyze your responses and generate:


- **Relevant Threats** based on your architecture

- **Chained Attack Paths** that span multiple components

- **Mappings to MITRE ATLAS** tactics (e.g., Data Poisoning, Supply Chain)

- **Categorization using NIST’s CIA + Abuse taxonomy**

- **Developer-friendly mitigation guidance**

- **Compliance gaps** (e.g., HIPAA, SOC 2) associated with each threat


It’s not a deep AI scanner. It won’t statically analyze your model weights or prompt templates. But it *will* guide you to uncover systemic threats early in the lifecycle — while design decisions can still be changed.

## **How It Works: A Peek Under the Hood**


The assistant has two core components:


**1. The Interactive UI (Streamlit App)**


The front-end walks users through a questionnaire tailored for AI systems. It covers areas such as:


- **Model Types**: Is it a classification model? A generative model? An ensemble?

- **Data Sources**: Where does your data come from? Is it internal, scraped, user-generated?

- **Deployment Mode**: SaaS, on-prem, hybrid cloud?

- **Interfaces**: Are there APIs, chatbots, dashboards? Is user input filtered?

- **Third-Party Dependencies**: Are you using open-source models, APIs, vector DBs?

- **Security Controls**: Rate limiting, RBAC, prompt filters, logging, etc.


This information helps establish the *attack surface* and *threat entry points*.


## Get Purple Security’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


**2. The Rules Engine (Python Logic)**


Once inputs are collected, a deterministic Python engine evaluates each condition against a list of pre-defined threat patterns. These rules live in the file you can inspect [here on GitHub](https://github.com/sandeepsaxenagit/ai-threat-model-assistant/blob/main/rules_engine.py).


Each rule includes:


- Matching criteria (e.g., if user input is unfiltered AND model is generative)

- Applicable threat (e.g., Prompt Injection via User Inputs)

- MITRE ATLAS mapping

- NIST CIA/Abuse category

- Suggested mitigations

- Compliance concerns triggered (e.g., GDPR, PCI-DSS, SOC 2)


Additionally, some rules look for **chained conditions** — for instance, if data is scraped *and* not validated *and* the model uses this data for zero-shot classification, you may see threats like “Data Poisoning via Insecure Ingestion Pipeline.”


Here’s a simplified example of one such rule:


```
{
"match": ["unfiltered_user_input", "llm_used"],
"threat": "Prompt Injection via User Input",
"mitre_atlas": "Prompt Injection",
"cia_abuse": "Integrity",
"mitigations": ["Sanitize input", "Use structured prompting", "Apply output validation"],
"compliance_issues": ["SOC2-CC7.1", "ISO27001-A.12.2.1"]
}
```


Each threat in the report is the result of evaluating these logical patterns — this makes the output consistent, explainable, and extensible.


**Try It Yourself**


You can use the hosted tool here:
[https://ai-threat-model-assistant-nniwbpphkmjhacnxsrebbw.streamlit.app](https://ai-threat-model-assistant-nniwbpphkmjhacnxsrebbw.streamlit.app/)


Or explore, fork, and improve it from the GitHub repo:
️[github.com/sandeepsaxenagit/ai-threat-model-assistant](https://github.com/sandeepsaxenagit/ai-threat-model-assistant)


The code is written in plain Python, with minimal dependencies. You can run it locally by cloning the repo and executing:


```
pip install -r requirements.txt
streamlit run main.py
```


**Who Is This For?**


This tool is intentionally **developer-first**. It’s not meant for a compliance auditor filling in a spreadsheet. If you’re:


- A developer shipping AI models,

- A security engineer responsible for ML systems,

- A product manager who needs to explain AI risk to leadership,

- Or even a student building AI projects —


This tool can give you a structured, consistent, and repeatable way to think through AI-specific risks.


It can also be used **before** deploying anything — just as a design-time assistant to provoke the right questions and anticipate risks early.


**What’s Next?**


This is version 1. There’s a lot of room to grow:


- Add more rules for newer attack vectors (e.g., jailbreak detection bypasses, embedding poisoning)

- Integrate auto-mapping with OWASP LLM Top 10

- Offer export to threat modeling diagrams (using Graphviz or Mermaid)

- Support team collaboration (multi-user input and export)

- Enable model-specific advice (e.g., transformer vs tree-based threats)


If this aligns with your work, consider contributing. Every rule added strengthens the community’s ability to build safer AI systems.


**Final Thoughts**


AI is not just a technological leap — it’s a security paradigm shift. As we embed LLMs and models into everything from search engines to surgery bots, we must rethink how we identify and mitigate threats.


The **AI Threat Modeling Assistant** isn’t trying to boil the ocean. It’s trying to give developers and teams a pragmatic, accessible way to understand and reduce their AI-specific risks — right from the design stage.


Check it out, try it on your projects, and if you find a gap — submit a PR.


Let’s build AI responsibly. Together.


*Want to contribute or suggest improvements? Fork the project on GitHub: ***[github.com/sandeepsaxenagit/ai-threat-model-assistant](https://github.com/sandeepsaxenagit/ai-threat-model-assistant)

---

*Originally published on [Medium](https://infosecwriteups.com/open-source-tool-for-ai-specific-threat-modeling-fast-context-aware-and-developer-friendly-2c047fdc1781). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
