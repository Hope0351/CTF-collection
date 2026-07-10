# :game_die: Prototype Pollution - A Deeper Inspection

---

## Prototype Pollution with FETCH API

We now arrive at the final section of this article and one that is perhaps most interesting because it brings together whatever we have discussed thus far into *action*. Before we proceed further it is important to set the *stage *for this section.

The FETCH API*Fetch *is a JavaScript API for browsers that can make HTTP requests. It is widely used in client side JavaScript because it is natively available in the language. More details on it can be found below.

The Fetch API takes an optional argument that takes an *Object* in which you can specify *parameters like Headers, Body etc*. It is possible to use these parameters dangerously in case if the application doesn’t specify them. And that is the basis for our little demo.

Vulnerable Web Application

The web application that we will be working with has been written by me and is written in *NodeJS*. This helps us to demonstrate prototype pollution on both *client* and *server *sides. You can find the source code in my repository below

Given the simplicity of the app, I will encourage you to have a look at the source code or work with it while reading the article.

Here is a brief overview of what it contains. There are 3 main routes in the web application.

- Root or “/”

- /server route

- API endpoint => /planet/position

On the main or root page we have the setup for *Client Side Prototype Pollution*. While on the /server endpoint it has been configured for *Server Side Prototype Pollution*. The API endpoint provides responses to GET & POST requests. It is a very simple API that gives the name of the planet in our Solar System depending upon the *position *provided in the API request. E.g., if the API is queried like */planet/position/4* then it would provide the name of “*Mars*” in response.

## Let’s Dive In - Client Side Prototype Pollution

When we visit the main or root page, we are greeted with the following page.

*Main Page — Vulnerable Web App*

Kindly note that the web application is running on port 3000. You can run it as well if you have NodeJS installed on your system.

## Get Amit Nigam’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Here is what is happening in the application. If you directly click the FETCH button, it will generate some random number between 1 & 9 and query the API and provide the response. Let us see that.

*Response when you click on FETCH*

We can see that it has added 2 items on the page. One is the Planet Name which is Jupiter while the other is not very clear at this point. Let us also look at the Request and Responses that were triggered because of this click.

*Request & Response Headers for FETCH click*

From this we can see that it is making a request to our API endpoint /planet/position/5. We also see the headers available to us.

Before we examine the client side JS, let us also provide a Header value and send the request.

*Providing a Header with the Request. We can see it gets “Reflected” back to us.*

In this case, we provided the application with a Header value to be sent along with the FETCH request and in this case it was *reflected *back to us. Here are the headers for the request & response.

*Headers for Request & Response. We can see a custom X-SomeHeader being set in both Request & Response.*

As can be seen, here the headers contain a *custom header* called X-SomeHeader and it is found in both Request & Response.

At this point, we can develop a fair bit of *intuition *to what might be happening in this *contrived *setup. Here is a quick summary of our intuition.

- The “Header value to send” field contains the value that we want to send inside the *custom header => X-SomeHeader*. We can see the same in the headers snapshot above.

- The server is reflecting the header back to us. And the response is *visible *on the page. This means, that if the response is going into some *unsafe sink* like innerHTML then it can potentially set us up for DOM XSS.

A quick *inspection *of the page confirms the intuition number 2. If you examine the JavaScript on the page by inspecting the page. You will see the following code.

*Discovery of Sink.*

We can see that a FETCH request is getting the data and it is being set inside the DOM with the use of *innerHTML *on line 56. We can confirm our suspicion by sending a *typical XSS* payload to trigger what in this case will be a *DOM based XSS*.

```
<img src=x onerror=alert(1)>
```

*DOM XSS through identified sink*

And voila! we have the *beautiful XSS *on our app.

So, we found the *sink *and were able to effect a *DOM based XSS* in our application by using that sink. This sets us up well for the base work that we needed for Prototype Pollution. Let us examine the client side JavaScript in order to fully understand what is going on.

*Looking at Client Side JavaScript*

The above snippet of code shows an interesting function attached to POLLUTE *button*. We can see that it is creating a “*pollutedObj*” by recursively merging with contents from the* input field *called “Pollutant Data”. From our analysis, we know that this is a perfect recipe for Prototype Pollution. Let us provide a payload for Prototype Pollution here

```
{"__proto__": {"x-someheader":"red"}}
```

*Sending a POLLUTE request*

Here we send out a POLLUTE request based on the payload discussed earlier. After we do that we quickly review in *console*, what is the Object’s Prototype like.

*Object’s Prototype has been successfully polluted!*

We can see that we were able to *successfully pollute the Object’s Prototype on the client side!* If we send a request now, the because the property of* x-someheader* has already been made available on the global Object’s prototype, the code will pick up this value as the *value of the header to be sent *despite us *not sending any headers*. Let us check our assumption.

*And Indeed it picks up the polluted value!*

And as a further confirmation, *no X-SomeHeader was sent* either in Request or Response. It was simply picked up from the Object’s prototype.

*No X-SomeHeader was set in Request or Response. This confirms our Pollution of the Prototype.*

And so, we have successfully polluted the global *Object Prototype* on the client side JavaScript. And in the case of this app, we can leverage our *innerHTML sink* to effect DOM based XSS as well. For that we change our payload like so.

```
{"__proto__": {"x-someheader":"<img src=x onerror=alert(1)>"}}
```

Let us send this out and see if we get XSS or not.

Please, note if you are following along, kindly *refresh *the Web App page so that the pollution of the prototype is *reset* in the browser.

Next, take the payload above and click on POLLUTE. And once it has been polluted you can just click on FETCH to get something from API (*without *setting the Headers) and then that will trigger the XSS.

*Client Side Prototype Pollution Leading to DOM XSS.*

Well, this completes our rather elaborate setup to achieve Client Side Prototype Pollution by leveraging browser’s FETCH API and some faulty web application logic involving recursive merge and JSON.parse!

## Server Side Prototype Pollution

Server side prototype pollution is a little bit more difficult because you don’t have access to JavaScript files like you do with client side PP. But it is *more *damaging because typical prototype pollution will mostly *break some application functionality* resulting in Denial of Service (DOS).

Hence, caution needs to be exercised whenever we are investigating server side PP. A few libraries have been found to be vulnerable to Prototype Pollution e.g., Lodash etc.

Let us look at our web application and see what we can do. Our approach here will be to look at the server side code as well. (White Box).

*Server Side PP — Web App Route*

This is how the endpoint looks like. As indicated the idea is to leverage Request Body to *pollute *Object Prototype. A quick look at Client Side JavaScript reveals the following.

*Client Side JS*

This looks like a very standard client side JS for page. We can see that it is using the value in the “Body Data” field and passing it to server using a FETCH request that contains *body*parameter.

Let us now look at the server side code for this.

*Server Side code for the endpoint.*

Again a *recursive merge* is used to pollute the JavaScript Object prototype on the server side. So we will use the following payload to pollute the prototype.

```
{"__proto__":{"isPolluted":true}}
```

And we will send the request.

*Server Side Prototype Pollution — FETCH request fails!*

When we send out the polluting payload, our FETCH request on the client side of the web page *fails *because the server has crashed or rather the thread running NodeJS got polluted.

We can confirm the same with the Log data in the server side console.

*Server Side Console Log*

From this output, we can see that the *Object Prototype on the server side has also been polluted* and a spurious property of *isPolluted* is available on the Object’s prototype on the server side.

---
