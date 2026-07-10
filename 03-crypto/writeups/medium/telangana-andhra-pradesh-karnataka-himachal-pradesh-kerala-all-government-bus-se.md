# :locked_with_key: Telangana Andhra Pradesh Karnataka Himachal Pradesh Kerala All Government Bus Se

> **Original Source:** [Telangana Andhra Pradesh Karnataka Himachal Pradesh Kerala All Government Bus Se](https://infosecwriteups.com/telangana-andhra-pradesh-karnataka-himachal-pradesh-kerala-all-government-bus-services-were-885b44c21a)
> **Platform:** infosecwriteups.com | **Category:** `CRYPTO`

---

Now the next part — TICKET CANCELLATION


- First of all, fetch all the victim details whose ticket is to be canceled by an attacker. The details like PNR No., Txn. Password, Mobile number (These three are only required for cancellation)

- Here Txn. Password and PNR are directly available from part one vulnerability. Now what we need is only the victim’s mobile number.

- To obtain the mobile number of the victim follow the steps below.

- On the last page of the ticket ( we fetched the victim ticket from part one), there is an option called send SMS/email. Click on that and intercept the request on a web interceptor tool like burp suite


```
GET /oprs-web/booking/ticket/sendSMS.do?id=<REDACTED>&mobileNo=<REDACTED> HTTP/2
Host: online.keralartc.com
Cookie: <REDACTED>
Upgrade-Insecure-Requests: 1
User-Agent: <REDACTED>
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Sec-Gpc: 1
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Referer: https://online.keralartc.com/oprs-web/print/tickets.do?id=<REDACTED>
Accept-Encoding: gzip, deflate
Accept-Language: en-GB,en;q=0.9
```


5. Here in this request, we can see the parameter called ‘mobileNo’ and it reveals the victim's mobile number. (It is <REDACTED> in this writeup due to security reasons.)


## Get Krishnadev P Melevila’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


6. Now we got all that we needed to cancel a victim’s ticket.7. Now visit [https://online.keralartc.com/oprs-web/guest/ticket/cancel.do](https://online.keralartc.com/oprs-web/guest/ticket/cancel.do) And enter all three details (PNR, TXN Password, Mobile Number) we have and click on search.Now we can see the full details of the victim. And there is an option for cancellation too... If we click that the victim's ticket will be canceled.

---

*Originally published on [Medium](https://infosecwriteups.com/telangana-andhra-pradesh-karnataka-himachal-pradesh-kerala-all-government-bus-services-were-885b44c21a). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
