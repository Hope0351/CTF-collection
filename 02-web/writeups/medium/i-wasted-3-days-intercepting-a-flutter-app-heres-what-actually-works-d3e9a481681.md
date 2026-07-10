# :globe_with_meridians: I Wasted 3 Days Intercepting a Flutter App. Here’s What Actually Works.

> **Original Source:** [I Wasted 3 Days Intercepting a Flutter App. Here’s What Actually Works.](https://infosecwriteups.com/i-wasted-3-days-intercepting-a-flutter-app-heres-what-actually-works-d3e9a4816818)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## The Scripts


## Script 1: disable-flutter-tls-v1.js


This one handles the Flutter TLS layer.


Flutter’s BoringSSL has a function called `ssl_verify_peer_cert` in handshake.cc that does the actual peer certificate verification. The script finds this function in memory using byte pattern matching. It has patterns for arm64, arm, x64, and x86 across both Android and iOS. Once it finds the function, it replaces the implementation with one that always returns 0, meaning every certificate passes without any check.


```
function hook_ssl_verify_peer_cert(address) {
Interceptor.replace(address, new NativeCallback((pathPtr, flags) => {
return 0;
}, 'int', ['pointer', 'int']));
}
```


There’s a timing problem that causes silent failures on a lot of devices. Frida attaches to the process before `libflutter.so` finishes loading. Pattern matching runs, finds nothing, exits cleanly, and you see no error, but the bypass never actually happened. The script handles this by retrying up to five times with a one-second delay between attempts. Once the library is found, the retry counter resets so the pattern search also gets its full number of attempts.

## Script 2: universal_bypass.js


This one covers everything in the Java layer, outside Flutter’s Dart runtime.


X509TrustManager is Android’s standard interface for certificate validation. The script registers a custom implementation where checkClientTrusted, checkServerTrusted, and getAcceptedIssuers are all empty. No certificate chain ever gets checked.


```
var TrustManager = Java.registerClass({
name: 'com.burp.bypass.TrustManager',
implements: [X509TrustManager],
methods: {
checkClientTrusted: function(chain, authType) {},
checkServerTrusted: function(chain, authType) {},
getAcceptedIssuers: function() { return []; }
}
});
```


SSLContext.init() gets hooked so that every SSL context created anywhere in the app, including inside third-party libraries, gets the bypass trust manager injected into it at initialization time.


HostnameVerifier is hooked to return true for every hostname. Some apps validate the server hostname as a completely separate step from certificate validation. Without this, you can pass the certificate check and still get blocked.


WebViewClient.onReceivedSslError calls handler.proceed() instead of showing an error page. Without this, any WebView inside the app will just stop loading when Burp intercepts the connection.


InAppWebViewClient is the hook that was missing from every existing script I found. Apps using the flutter_inappwebview plugin register their own WebView client subclass at `com.pichillilorenzo.flutter_inappwebview_android.webview.in_app_webview.InAppWebViewClient`. Hooking the parent WebViewClient class does nothing for this subclass. You have to hook it by its full name specifically.


```
try {
var InAppWebViewClient = Java.use('com.pichillilorenzo.flutter_inappwebview_android.webview.in_app_webview.InAppWebViewClient');
InAppWebViewClient.onReceivedSslError.implementation = function(view, handler, error) {
handler.proceed();
};
} catch(e) {
console.log("[-] InAppWebView not present: " + e);
}
```


The try/catch exists because if the app doesn’t use flutter_inappwebview, that class simply doesn’t exist. A bare Java.use() call on a missing class crashes the entire script before any other hook runs. The catch keeps everything else alive.

## Running both scripts


```
frida -U -f com.your.app.package -l ./disable-flutter-tls-v1.js -l ./universal_bypass.js
```


If the app freezes after launch, type `%resume` in the Frida REPL to unpause it. If you attached to an already running process, skip this — there's nothing to resume.


Watch the output. The Flutter script will log which byte pattern matched and at what address. The Java script logs each hook as it fires. Traffic should start showing up in Burp within a few seconds of the app making its first network request.


On most Flutter apps I’ve tested, this is enough. Try it before going any further.

---

*Originally published on [Medium](https://infosecwriteups.com/i-wasted-3-days-intercepting-a-flutter-app-heres-what-actually-works-d3e9a4816818). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
