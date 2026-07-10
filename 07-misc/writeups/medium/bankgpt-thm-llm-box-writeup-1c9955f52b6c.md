# :game_die: BankGPT — THM LLM Box Writeup

---

# BankGPT — THM LLM Box Writeup

By: Kavin Jindal ([@klevr](https://klevrbook.gitbook.io/home))

TryHackMe has been putting out a lot of content related to LLM Hacking recently including walkthroughs and challenges. BankGPT is an easy-rated challenge that requires the user to exploit an actual LLM to extract a secret key. The LLM serves as an AI assistant to help a fictional bank staff, and our objective is to evade the safeguards in place to get the secret key.

## Get Avyukt Security’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

You can get a basic introduction to LLM Hacking by going through the following TryHackMe module:
[https://tryhackme.com/module/attackingllm](https://tryhackme.com/module/attackingllm)

## - 0x01: Solution

- The following webpage was obtained upon visiting the target.

- Before sending a malicious prompt and getting right into action, I sent some normal messages just to know about the LLM.

- Turns out the LLM was running the Gemma model by Google, which is said to be a lightweight version of Gemini.

- Next, I began testing the conventional Prompt Injection attacks on the LLM.

- I knew exploiting the LLM wouldn’t be this easy but I just wanted to see how the model would respond to such requests.

- I even tried the DAN Override method but it didn’t work.

- Next, I tried the following prompt.

- As you can see, there was a slight change in the model’s tone considering I had posed myself as the chief executive of the bank, I had a sense that I was close to my objective of attaining the flag.

- Next, I modified the above prompt as follows and successfully obtained the secret key.

- This is a classic example of jailbreaking and system prompt leakage. I manipulate the LLM to assume a new role as the security head and provide me (the executive) with important information including the secret flag in accordance with the modified rules and regulations. This is also an example of sandwiching, a prompt injection technique in which the malicious query is embedded between a legitimate message, and in pursuing the legitimate query, the model also fulfills the malicious embedded task.

## -0x02: Conclusion

BankGPT was a pretty easy room to go through. Anyone with even basic knowledge of prompt injection can solve this easily within a few tries. Apart from that, there is no conventional way to break LLMs and different models require different techniques for exploitation. Overall, the room was a good introduction to LLM Hacking and gave the user a sense of how actual models are exploited in real-world scenarios.

I hope you found this write-up helpful. Don’t forget to follow Avyukt Security for more cybersecurity content.

Happy Hacking!

---
