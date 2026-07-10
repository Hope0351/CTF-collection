# :game_die: Hijacking Your Javascript Using Prototype Pollution 8Caeac16B13F

---

## Get sushil phuyal’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

To explain how prototype pollution can be chained with JavaScript injections to exploit vulnerabilities, let’s create an example scenario where an attacker leverages both techniques to carry out a malicious attack. Imagine a web application that has a user profile feature where users can customize their profile with a bio section. The application allows users to input text for their bio, which is then displayed on their profile page. Here’s a simplified example code snippet representing this scenario:

```
let userProfile = {};

function updateBio(newBio) {
userProfile.bio = newBio; // Update user's bio
}

// User input obtained from a form field
let userInputBio = "I love coding!";

updateBio(userInputBio); // User updates their bio

// Display the user's bio on their profile page
console.log("User's Bio:", userProfile.bio);
```

Now, let’s see how an attacker can exploit this application using prototype pollution chained with JavaScript injections:

- Prototype Pollution: The attacker first exploits the prototype pollution vulnerability to manipulate the behavior of the Object prototype. They inject a new property into the prototype chain that alters the behavior of all objects inheriting from it.

```
Object.prototype.attackFunction = function() {
// Malicious code executed by the attacker
console.log("Executing malicious code...");
// Example: Send user data to attacker-controlled server
// sendUserDataToAttacker(this);
};
```

2. JavaScript Injection: Next, the attacker injects a script into the user’s bio input field. They craft the bio text in such a way that it triggers the malicious attackFunction added to the prototype chain.

```
// User input crafted by the attacker
let userInputBio = "I love hacking! <img src='x' onerror='this.attackFunction()'>";

//In this example, the attacker injects an <img> tag with an onerror attribute that calls the attackFunction when the image fails to load (onerror event).
```

3. Chained Exploitiation: When the user updates their bio with the malicious input provided by the attacker, the updateBio function executes, and the attacker’s injected code gets triggered due to the prototype pollution affecting all objects, including userProfile. This action can lead to various malicious activities, such as stealing user session data, redirecting users to phishing sites, or performing actions on behalf of the user without their consent.

```
updateBio(userInputBio); // Malicious code executed due to prototype pollution and JavaScript injection
```

By chaining prototype pollution with JavaScript injections, the attacker gains unauthorized access to execute arbitrary code within the context of the application, leading to serious security implications such as XSS attacks and unauthorized data manipulation. It underscores the importance of thorough input validation, sanitization, and secure coding practices to mitigate such vulnerabilities in web applications.

---
