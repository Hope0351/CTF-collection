# :globe_with_meridians: Ssrf Via Flawed Request Parsing 7B32A119F047

---

## Methodology

Want to give the lab a try yourself and follow along? You can check it out on PortSwigger’s website [here](https://portswigger.net/web-security/host-header/exploiting/lab-host-header-ssrf-via-flawed-request-parsing) for free.

## The Recon

This application features a shop with products. Unlike many shops however, it doesn’t have any actions associated with the products, just the ability to view a text description.

It looks as if there’s also account functionality, but we have no ability to login using the default lab credentials.

This lab is very simple with what we can interact with, and it doesn’t look like there’s much to click around.

At this point, we should turn our sights to the SiteMap:

We don’t really have anything of interest outside the Root Request. Let’s kick off an active scan on the GET request and send it over to the Repeater so we can start to play around with it.

In the Repeater, we can see that changing the host header results in a *403* response.

We can test supplying an absolute URL in the GET request, seeing that the request now works and returns a *200*.

Let’s try putting both of these techniques together.

This time, we can see we receive a completely different response, a *504* timeout, suggesting that the absolute URL is being validated in place of the Host Header.

Let’s validate that a connection is still taking place.

Input a Collaborator domain in place of the Host Header.

We got a response from our collaborator — confirming our suspicions.

## Testing

Send the request over to Burp Intruder.

Since we don’t want our Host header to match the target we’re sending the request, make sure to uncheck the *Update Host header to match target* at the top of the Payload.

Next, we’ll need to set the host header to scan for the admin interface.

## Get Ryan G. Cox’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

We know the location is somewhere in the range 192.168.0.0/24, which equates to 192.168.0.0–192.168.0.255.

We’ll need to set up a Sniper Attack to search for these endpoints.

First, setup the payload with admin appended to the absolute URL path.

Then, set the base IP in the host header.

Finally, add a payload position on the fourth octet.

Once complete, it should look like this:

Next, navigate to the Payloads tab and sselect Numbers for Payload position 1. Increment the range from 0–255 by 1.

Start the attack.

When it finishes, sort by Status Code. You should see all status codes return a *504*, except for one, returning a *200*.

If you click it, you’ll see we’ve found our admin panel (IP location will be different for each lab instance).

## Exploitation

In the request from our Intruder attack, notice we now how access to the admin panel that can delete users.

There are a few things to make note of here:

- It has an action request located at */admin/delete*

- It requires a *csrf* value to send the POST request, but it includes it in plaintext in the DOM.

- You can submit a user to the endpoint via the *username* parameter.

Let’s head back to the Repeater and edit the request to reflect our new findings.

First, click the GET request and click *Change request method* to change it to a POST.

Add our newly found admin panel location to the Host header. In this specific case: 192.168.0.27.

Append */admin/delete *to the absolute URL.

Add *csrf* and *username* as POST parameters.

Check the post request below. Upon sending, you should recieve a 302, verifying that the lab is solved!

## What We’ve Learned

In this walkthrough, we’ve demonstrated the result of what flimsy SSRF controls can yield. In this case, we exploited a validation discrepancy between the Host header and the Absolute URL, allowing an attacker (us) to access restricted resources with some creative thinking.

—

Remember: The Cybersec Café gets articles first. Subscribe for free [here](https://www.cyberseccafe.com/).

Interested in getting into Cybersecurity? I have a course called the [Security Sip](https://securitysip.cyberseccafe.com/). The curriculum is designed to help you build skills progressively over 12 sections, 85 modules, and 155 exercises. With rapidly evolving threats and technologies widening the skill gap, it’s time to secure your future in cybersecurity. [Available Now](https://securitysip.cyberseccafe.com/#pricing)!

Oh, and if you want even more content and updates, hop over to Ryan G. Cox on [Twitter/X](https://twitter.com/ryangcox_) or my [Website](https://www.ryangcox.com/). Can’t wait to keep sharing and learning together!

---
