"""LLMFS client that mimics OpenAI's API."""

import os
import json
import time
from pathlib import Path
from typing import List, Dict

NOANSWER_PRED = "No answer found."
FAILED_PRED = "Failed to process the request."

class RateLimitException(Exception):
    """Exception raised when rate limit is exceeded."""
    pass

def get_team_id(team: str) -> str:
    """Returns the team ID based on the team subnet."""
    # If you're playing this challenge after DEF CON 25, this has been edited
    # but it should work in your environment.
    team_id = int(team.split(".")[2])
    return team_id

class ChatCompletionResponse:
    def __init__(self, response: dict):
        self.raw = response
        self.choices = []
        msg = response.get("message")
        if msg:

            class Message:
                def __init__(self, d):
                    self.role = d.get("role", "assistant")
                    self.content = d.get("content", "")

            class Choice:
                def __init__(self, msg):
                    self.index = 0
                    self.message = Message(msg)

            self.choices.append(Choice(msg))
        self.usage = response.get("usage")

    @property
    def output_text(self):
        """Get the first response text"""
        if self.choices:
            return self.choices[0].message.content
        return ""

class OpenAI:
    """OpenAI-compatible client for LLMFS"""

    def __init__(self):
        self.target_file_dir = Path("/mnt/llmfs/")
        self.chat = self
        self.completions = self
        self.responses = self

    def _write_request(self, request: dict, target_file: str):
        """Write JSON request to file"""
        data = json.dumps(request).encode("utf-8")
        off = 0
        with open(target_file, "wb") as f:
            while off < len(data):
                written = f.write(data[off:])
                off += written

    def _read_response(self, target_file: str) -> dict:
        """Read JSON response from file"""
        fd = os.open(target_file, os.O_RDONLY | os.O_DIRECT)
        try:
            # Read until EOF
            chunks = []
            while True:
                chunk = os.read(fd, 8192)
                if not chunk:
                    break
                chunks.append(chunk)

            content = b"".join(chunks)
            content_str = content.decode("utf-8")

            try:
                return json.loads(content_str)
            except json.JSONDecodeError as e:
                return {"status": "pending", "error": str(e)}
        except FileNotFoundError:
            return {"status": "error", "error": "Response file not found"}
        finally:
            os.close(fd)

    def _wait_for_response(self, target_file: str, timeout: int = 60) -> dict:
        """Wait for and return the response"""
        start_time = time.time()

        while True:
            response = self._read_response(target_file)

            if status := response.get("status"):
                if status == "success":
                    return response
                elif status == "error":
                    raise Exception(f"LLM Error: {response.get('error', 'Unknown error')}")
                elif status == "rate_limited":
                    raise RateLimitException("Rate limit exceeded. Please wait and try again later.")
            else:
                raise Exception("Response does not contain status")

            if time.time() - start_time > timeout:
                raise TimeoutError(f"Request timed out after {timeout} seconds")

            time.sleep(1)

    def create(
        self,
        team_id: str,
        model: str,
        messages: List[Dict[str, str]] = None,
        prompt: str = None,
        input: str = None,
        **kwargs,
    ) -> ChatCompletionResponse:
        """Unified create method for all interfaces"""
        # One llmfs endpoint per team
        target_file = self.target_file_dir / f"{team_id}_{model}_1.json"
        # Convert different input formats to messages
        if messages is None:
            if input:  # responses.create style
                messages = [{"role": "user", "content": input}]
            elif prompt:  # completions.create style
                messages = [{"role": "user", "content": prompt}]
            else:
                raise ValueError("Must provide messages, prompt, or input")

        request = {"messages": messages, "temperature": kwargs.get("temperature", 0.7)}

        if "max_tokens" in kwargs:
            request["max_tokens"] = kwargs["max_tokens"]

        # Write request and wait for response
        self._write_request(request, target_file=str(target_file))
        response = self._wait_for_response(target_file=str(target_file), timeout=kwargs.get("timeout", 60))

        return ChatCompletionResponse(response)
