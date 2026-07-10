# :globe_with_meridians: Rxss On Mercedes Benz 71A839Da2D31

---

जय श्री राम 🚩

For Non-Members: Free Link

## 📚 Theory: Understanding CVE-2025–4388 (Liferay Portal RXSS)

CVE-2025–4388 is a Reflected Cross-Site Scripting (RXSS) A reflected cross-site scripting (XSS) vulnerability in the Liferay Portal 7.4.0 through 7.4.3.131, and Liferay DXP 2024.Q4.0 through 2024.Q4.5, 2024.Q3.1 through 2024.Q3.13, 2024.Q2.0 through 2024.Q2.13, 2024.Q1.1 through 2024.Q1.12, 7.4 GA through update 92 allows an remote non-authenticated attacker to inject JavaScript into the modules/apps/marketplace/marketplace-app-manager-web.

## 🧩 Affected Software:

- Liferay Portal (Multiple versions likely affected before patch)

- Vulnerable when rendering unsanitized query strings in:

- `meta refresh tags`

- redirect URLs

- certain `GET` parameters in guest/public pages

To discover targets vulnerable to CVE-2025–4388, you can use Shodan, Censys, or similar search engines to look for internet-exposed Liferay instances.

🔍 Shodan Dork Example:

```
html:"liferayPortalCSS"
```

*1.1K Vulnerable Targets.*

Now after selecting the target we have to use this payload for exploiting *REFLECTED*…

---
