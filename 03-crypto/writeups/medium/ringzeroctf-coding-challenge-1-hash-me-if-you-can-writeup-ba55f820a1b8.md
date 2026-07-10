# :locked_with_key: Ringzeroctf Coding Challenge 1 Hash Me If You Can Writeup Ba55F820A1B8

---

15. Explanation of the script in understandable way :-

a. *requests, re, hashlib library*:- *Requests is the A Python library used to send HTTP requests (GET, POST, etc.) to websites and receive responses like a browser. It handles sessions, cookies, headers, and makes web automation simple and reliable. Re is the Python’s regular expression library used to search, match, and extract patterns from text. It is used when you need to find specific data inside large or messy strings like logs or HTML. Hashlib is the Python’s cryptographic hashing library used to generate hashes like SHA-256 and SHA-512. It converts data into a fixed-length fingerprint used for integrity checks and security tasks*.

b. *I used the requests library of the python to create the session of the website and the extract the response of the text and then i just applied the re.search function to extract the original message which we are given to hash*.

c. *.*? -> ‘.’ means to match any character. ‘*’ means to repeat the process zero or more times. ‘?’ makes it lazy to match little as possible.*

d. *\s* -> To neglect the whitespaces in the reponse.*

e. *strip() function :- This is the function of the python to remove the leading and trailing whitespaces from the text we have selected.*

f. *hashlib.sha512(text.encode()).hexdigest :- Now the extracted text is the alphanumeric characters which the machine do not understand, it understands the language of the bit/bytes so we encoded to the UTF-8 encoding [By Default] using the encode() function and then applied the sha512 function and then after that we again converted to hexadecimal characters for the human readable text.*

g. *At last we added the line of sending requests with the params [parameter] added as well.*

16. With this we executed the script.

---
