# :game_die: TeamCyprus ECSC Qualifiers CTF - WassApp Challenge Writeup

---

As expected I received an encrypted response which most likely included the flag. Observing the requests in dev tools more closely I noticed two interesting ones.

```
POST /api/handshake HTTP/1.1Request:{
"with":"1842042",
"jwk":{
"crv":"P-256",
"ext":true,
"key_ops":[],
"kty":"EC",
"x":"mZSbHWKlhRmDHOmThoaa8plRNejzeavpEbPSEVGs7hI",
"y":"La3z3VfSxacl7iLKZEMNISFB_dkmLA-0yjlFjPBblos"
}
}Response:{
"kty":"EC",
"crv":"P-256",
"x":"8-U6UxCRGJlnCLtB78R3JytBd9A4DKndobXGZDsfqwk",
"y":"Ph9OsNWDnriGECHioB7wpboFFIJY36gYcd3MnxDtsg0"
}POST /api/reply HTTP/1.1Request:{
"to":"1842042",
"encMsg":{
"ciphertext":"1DjaZ6PsPysxerzK1u3xEg==",
"iv":"1zxHfnjMdyonoMdlAkm5Pg=="
}
}Response:{
"iv":"x1IHO6KN6fYXOk9hlyto7w==",
"ciphertext":"AbwZFJtHVT1qGMzJ5JCwd+Gs2/gEAAXdsiMsLfBsYrkJvifw5pJToqSud0zyeYgB2s4fA4Nz0OJPbAioby36HnYJGF1eC0EsEtkOdr4cj3g="
}
```

Obviously the *reply *endpoint was for communicating the encrypted messages with the server but the *handshake *seemed to contain information that will be useful for decryption.

Examining further, I noticed they had a “We are hiring” link at the bottom of the page. This redirected me to a page listing the requirements of potential applicants.

>

Random pages like this always serve some purpose in these competitions.

In this case, a specific line caught my attention: “Experienced with Web Crypto API.”. Looking this up quickly, it turns out that it is an interface for using cryptographic primitives in scripts. It was very likely that this is the technology used for encrypting and potentially decrypting the message.

Keeping this in mind, the next step was to take a look in the source code. The most important part was a javascript file which was minified and obfuscated so it was rather difficult to read. I used the dev tools debugger to step in some of the code while sending and receiving a message and I found some interesting code snippets.

```
return new Promise(function(e, t) {
window.crypto.subtle.generateKey({
name: "ECDH",
namedCurve: "P-256"
}, !1, ["deriveKey", "deriveBits"]).then(function(t) {
e(t)
}).catch(function(e) {
t(e)
})
}
)
}
, i = function(e, t) {
return new Promise(function(n, r) {
window.crypto.subtle.deriveKey({
name: "ECDH",
namedCurve: "P-256",
public: t
}, e, {
name: "AES-CBC",
length: 256
}, !1, ["encrypt", "decrypt"]).then(function(e) {
n(e)
}).catch(function(e) {
r(e)
})
}
)
}
, l = function(e, t) {
var n = new TextEncoder
, r = n.encode(t)
, a = window.crypto.getRandomValues(new Uint8Array(16));
return new Promise(function(t, n) {
window.crypto.subtle.encrypt({
name: "AES-CBC",
iv: a
}, e, r).then(function(e) {
t({
ciphertext: o(e),
iv: o(a)
})
}).catch(function(e) {
n(e)
})
}
)
}
```

This snippet covered the whole procedure from key-generation to encryption. Checked in with the Web Crypto API saved from earlier and bingo! This is exactly what was used.

After browsing through the Web Crypto API documentation I realized that I had everything that I needed to decrypt the messages.

There were two options from here. Try to import the public key using the information from the handshake network request and use it with the appropriate private key which was somewhere in the codebase, OR get directly the secret key required for decryption from the function generating it!

Of course, I went with the quick and dirty way. Why bother re-deriving the keys, let’s just snag it from that function *deriveKey.* It returns a promise resolved with the key we need.

### Getting the Key

For that task, I used a handy chrome plugin called [Resource Override](https://chrome.google.com/webstore/detail/resource-override/pkoacgokdfckfpndoffpifphamojphii?hl=en)*. *This allows to setup regular expression patterns and replace any resources ( css, js, images etc..) that match, with the ones that you specify — even locally! Using that I was able to create a local version of the main javascript file that was used for crpyptography and apply persistent changes to it.

In order to access the Crypto Key I just made it to a global variable by adding the following line into the code.

```
i = function(e, t) {
return new Promise(function(n, r) {
window.crypto.subtle.deriveKey({
name: "ECDH",
namedCurve: "P-256",
public: t
}, e, {
name: "AES-CBC",
length: 256
}, !1, ["encrypt", "decrypt"]).then(function(e) {
window.cryptoKey = e;
n(e)
}).catch(function(e) {
r(e)
})
})
},
```

I reloaded the page, made sure that the resource was replaced, crossed my fingers and hoped for the best!

---
