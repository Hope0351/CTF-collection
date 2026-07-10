# :game_die: Portswigger - Command Injection All Labs Walkthrough(Bug Bounty Prep)[by dollarboysushil]

---

# Portswigger — Command Injection All Labs Walkthrough(Bug Bounty Prep)[by dollarboysushil]

Link to portswigger academy: [https://portswigger.net/web-security/os-command-injection](https://portswigger.net/web-security/os-command-injection)

>

For any correction / query /suggestion contact on
*Instagram *[dollarboysushil](https://instagram.com/dollarboysushil)
*Twitter *(X) [dollarboysushil](https://twitter.com/dollarboysushil)
*Youtube *[dollarboysushil](https://youtube.com/dollarboysushil)
*Linkedin *[dollarboysushil](https://www.linkedin.com/in/dollarboysushil/)

### What is OS command injection?

OS command injection or shell injection is an attack which allows attacker to execute os commands on the server that is running an application.

### How OS command injection attack works?

Lets look at an example

```
https://insecure-website.com/stockStatus?productID=381&storeID=29
```

In the above url, the application gives stock status by taking two arguments `productID` and `storeID` .

To provide the stock information, the application must query various legacy systems. For historical reasons, the functionality is implemented by calling out to a shell command with the product and store IDs as arguments:

`stockreport.pl 381 29`

The command then outputs the stock status.
If there isn’t any proper sanitization or defenses, attacker can submit `& echo abcdef &` in productID, which will become
`stockreport.pl & echo abcdef& 29`

Then the overall output will be
`Error — productID was not provided
abcdef
29: command not found`

Link to lab: [https://portswigger.net/web-security/os-command-injection/lab-simple](https://portswigger.net/web-security/os-command-injection/lab-simple)

>

Aim: execute whoami command and get current user name

Click access the lab

Click on View details.

With your `burpsuite` ready click on check stock.

Select the request created when clicking check stock.
And send this request to repeater

Then change the value of productId to `& whoami &` then url encode this string using `ctrl + U`

Then send this request which gives us, output of `whoami` command.

Lab 1 done ✅

## Get dollarboysushil’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

— — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

>

Aim: cause 10sec delay.

Click on `Submit Feedback`

Enter random data and intercept the request using burpsuit.

select `/feedback/submit` request and send it to repeater.

When we send this request we get response in `439mills`

Then change the value of email parameter to `& ping -c 10 127.0.0.1 &`
this will send 10 ICMP echo request packets to the loopback address 127.0.0.1.

Then select this payload and `Ctrl + U` to url encode and send the request.
Now we get response in 9640 millis

Which completes the lab.

Lab 2 done ✅

— — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

Link to lab: [https://portswigger.net/web-security/os-command-injection/lab-blind-output-redirection](https://portswigger.net/web-security/os-command-injection/lab-blind-output-redirection)

Same as before send the reques to repeater.

Then time change the value of email to `& whoami > /var/www/images/output.txt &`
This will output the value of whoami command into `output.txt` file.

Select and url encode the payload and send the request.

Now we need to open the output.txt file which holds the result of whoami command.

Open any of the post form the lab.
Right click on the image and click on open image in new tab.

Then change the value to `output.txt` which will display the output of whoami command.

Lab 3 done ✅

## Lab 4 and 5 needs premium version of burpsuite.

— — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

>

For any correction / query /suggestion contact on
*Instagram *[dollarboysushil](https://instagram.com/dollarboysushil)
*Twitter *(X) [dollarboysushil](https://twitter.com/dollarboysushil)
*Youtube *[dollarboysushil](https://youtube.com/dollarboysushil)
*Linkedin *[dollarboysushil](https://www.linkedin.com/in/dollarboysushil/)

---
