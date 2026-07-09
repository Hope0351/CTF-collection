# Lab Writeup: Unprotected admin functionality with unpredictable URL

URL: https://portswigger.net/web-security/learning-paths/server-side-vulnerabilities-apprentice/access-control-apprentice/access-control/lab-unprotected-admin-functionality-with-unpredictable-url

## Description

This lab has an unprotected admin panel. It's located at an unpredictable location, but the location is disclosed somewhere in the application.

Solve the lab by accessing the admin panel, and using it to delete the user `carlos`.

## Solution

1. Inspect the web page and see the javascript source code

   ```
   var isAdmin = false;
   if (isAdmin) {
   var topLinksTag = document.getElementsByClassName("top-links")[0];
   var adminPanelTag = document.createElement('a');
   adminPanelTag.setAttribute('href', '/admin-meewxk');
   adminPanelTag.innerText = 'Admin panel';
   topLinksTag.append(adminPanelTag);
   var pTag = document.createElement('p');
   pTag.innerText = '|';
   topLinksTag.appendChild(pTag);
   }
   ```

2. From the above javascript, we could see a URL `/admin-meewxk` go there, delete `carlos` and the lab should be solved.

   ![Unprotected Admin Unpredictable](/assets/unprotected-admin-unpredictable.png)
