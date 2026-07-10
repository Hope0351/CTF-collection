# :globe_with_meridians: Xss In Google Idx Workstation Rce 22 500 Bounty Earned 2D09F0176869

> **Original Source:** [Xss In Google Idx Workstation Rce 22 500 Bounty Earned 2D09F0176869](https://infosecwriteups.com/xss-in-google-idx-workstation-rce-22-500-bounty-earned-2d09f0176869)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## 🧩 Root Cause


The problem was postMessage origin validation in `webWorkerExtensionHostIframe.html`


```
const parentOrigin = searchParams.get('parentOrigin') || window.origin;
self.onmessage = (event) => {
if (event.origin !== parentOrigin) return;
worker.postMessage(event.data, event.ports);
}
```


By controlling `parentOrigin`, attackers could relay arbitrary postMessages → inject JS → achieve XSS.


## Get Aditya Sunny’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


PostMessages carry binary data (converted to hex) sent to the worker.


[Gist with full payloads](https://gist.githubusercontent.com/Sudistark/a643a2e8216e5a93f92bde9121333337/raw/b100c95bcb227ad70e64518ff370f3a07cc7a23f/pwn-idx.txt)

---

*Originally published on [Medium](https://infosecwriteups.com/xss-in-google-idx-workstation-rce-22-500-bounty-earned-2d09f0176869). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
