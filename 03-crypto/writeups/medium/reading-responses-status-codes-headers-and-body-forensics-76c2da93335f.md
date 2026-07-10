# :locked_with_key: Reading Responses: Status Codes, Headers, and Body Forensics

---

## Status Codes as Forensic Artifacts

Status codes tell you what the server decided. They also tell you things the server did not intend to reveal.

200 OK

The endpoint exists, accepted your request, and returned content. For pentesters, a 200 is a starting point, not a conclusion. Note the response size and content type — a 200 returning 0 bytes or a tiny body is worth investigating. A 200 on an endpoint that should require authentication is a finding.

301 Moved Permanently / 302 Found

Redirects. The `Location` header tells you where. Capture it:

```
curl -I http://target.com | grep -i location
```

Note that `Location` Only appears in redirect responses — on a 200, this grep will return nothing. Redirect destinations reveal infrastructure: internal hostnames, load balancer addresses, CDN URLs, and admin subdomains. A 301 to `https://` Also confirms the site is serving unencrypted traffic on port 80 — worth noting.

400 Bad Request

Your request was malformed — or the server thinks it was. In testing contexts, a 400 on a request that should be valid can indicate WAF intervention, an input validation rule, or a parsing issue. Compare a 400 response against a known-good request to identify what the server rejected.

401 Unauthorized

Authentication is required and was not provided, or was provided but is invalid. The distinction from 403 is important: 401 is about missing or invalid credentials, while 403 is about valid credentials that still lack permission. The `WWW-Authenticate` header tells you the authentication scheme expected: `Basic`, `Digest`, `Bearer`, `NTLM`. This is your cue to look at Article 6.

403 Forbidden

The server understood your request and chose not to fulfill it. This is different from 401 — the issue is authorization, not authentication. You may be authenticated, or the resource may be public, but access is still denied.

In most cases, a 403 response indicates that the resource exists and is protected. A 404 suggests it does not. A server returning 403 on `/admin` is likely confirming that `/admin` is a real path with access controls, which is more useful than a 404. That said, some applications intentionally return 404 for protected resources to hide their existence entirely, so treat a 403 as a strong signal rather than a guarantee.

404 Not Found

A 404 usually means the resource is not there — but verify before moving on. Check whether the application returns genuine 404s or custom error pages with a 200 status code, commonly called soft 404s. A soft 404 often returns a 200 with a generic error page, which is why size comparison matters. Compare the response size against a path that definitely does not exist (`/zzznotreal`). If they match, the application may be masking its 404s.

405 Method Not Allowed

Your HTTP method is not accepted on this endpoint. A standard 405 response should include a `Allow` header listing what methods the endpoint does accept. A 405 on a `DELETE` request that returns `Allow: GET, POST` tells you exactly what is permitted — useful for method discovery and understanding what operations the endpoint supports.

500 Internal Server Error

Something broke server-side. In a testing context, a 500 triggered by your input is a signal worth capturing. It may indicate that your payload reached the application logic and caused an unhandled exception — a common indicator of injection points. Save the request and response.

502 Bad Gateway / 503 Service Unavailable

Infrastructure responses. A 502 indicates that a reverse proxy or load balancer could not reach its backend. A 503 means the service is temporarily unavailable. These are less interesting for direct exploitation but can indicate infrastructure topology.

---
