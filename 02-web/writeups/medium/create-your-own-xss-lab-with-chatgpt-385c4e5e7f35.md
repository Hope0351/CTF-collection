# :globe_with_meridians: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/create-your-own-xss-lab-with-chatgpt-385c4e5e7f35)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Create Your Own XSS Lab with ChatGPT


## Get up and running quickly with this easy-to-follow tutorial on creating and running your own custom XSS lab with ChatGPT.


Having trouble learning a vulnerability type? Just have ChatGPT make you a lab!

### 1. What do you want to learn?


DOM XSS is a popular vulnerability type to hunt for because they’re everywhere, hard to scan for, and typically have high rewards.


## Get Mike Takahashi (TakSec)’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


**Prompt:**

>

Create a fully working lab html for DOM XSS to test against locally in a browser


### 2. Run the XSS Lab


Now that you have the HTML code, copy the code and paste it into your favorite text editor. Save the file as a `.html` file and open it in a browser.


### 3. Play with It


Just like a real target in the wild, interact with the page as a normal user first. In this case, anything entered in the search box is reflected on the page and becomes a GET request parameter in the URL:


### 4. Open Developer Tools


Open the developer tools panel of your browser by right-clicking on the page and selecting “Inspect” if using Chrome. You can manipulate the `q` parameter value directly in the URL bar of the browser. Try different probes or XSS payloads to test how they reflect.


### 5. Pop that XSS alert()


For this lab, any basic XSS payload such as `<script>alert()</script>` will work, but also try other ones to see them in action in this context.


### 6. More Labs


- XSS labs for different contexts such as injecting directly inside javascript.

- More complex XSS labs involving different types of filters and character restrictions.

- Other vulnerability types such as CSRF, IDOR, and XXE. As you try these other labs, it may require a web server to function. Try asking ChatGPT for instructions if you’ve never done it before.

---

*Originally published on [Medium](https://infosecwriteups.com/create-your-own-xss-lab-with-chatgpt-385c4e5e7f35). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
