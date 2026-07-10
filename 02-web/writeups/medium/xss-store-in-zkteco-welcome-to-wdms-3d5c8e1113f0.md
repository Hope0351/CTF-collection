# :globe_with_meridians: Medium

---

## Context

Hello everyone! On this occasion, I would like to share how I discovered a vulnerability in a ZKTeco WDMS system. It all started when I had to review third-party systems, as in this case, where the opportunities to exploit these circumstances are crucial, especially when economic constraints prevent the acquisition of these platforms.

## Whats ZKTeco WDMS?

WDMSis Web-based Data Master System, an advanced middleware.
As a middleware, WDMSallows you to deploy on servers and databases for devices and transactions management. Administrators can access WDMSanywhere by the browser or a third-party software by API to handle thousands of devices.

## **Technical Details:**

- **Vendor:** ZKTeco

- **Vendor Website:** [https://www.zkteco.com](https://www.zkteco.com)

- **Affected Version:** ZKTeco WDMS 5.1.3

- **Vulnerable Endpoint:** `/iclock/data/employee`

## Review Vulnerability

The first thing we encounter is a typical user access. We will skip this process as it is not relevant to this publication.

*login panel*

After logging into the application, a panel is displayed that features a menu, allowing us to view, modify, and delete specific information. This menu serves as a key interface that enables efficient data management. From here, various functions are accessible, facilitating interaction and administration of the information contained in the platform.

## Get Miguel Angel Méndez Z.’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

*application*

Now, we proceed to attempt to modify employee information in the “Emp Name” (EName) field. Initially, we tested with a small payload; however, the results were not satisfactory. This is because the form is validated on the frontend, and the payload must adhere to a maximum of 40 characters.

*form*

The results when trying to inject payloads into the form are as follows.

*error input*

Now, the vulnerability in this form lies in the fact that the information is only validated on the frontend, as mentioned earlier. However, this validation is not performed on the backend, allowing the possibility to intercept the request and modify the information before it is sent.

---
