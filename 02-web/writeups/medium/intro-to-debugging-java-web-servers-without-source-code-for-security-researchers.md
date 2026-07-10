# :globe_with_meridians: Intro to Debugging Java Web Servers Without Source Code For Security Researchers

---

# Intro to Debugging Java Web Servers Without Source Code For Security Researchers

Debugging Java web servers in an on-premise environment is crucial for pentesting and source code reviews. It’s possible to easily decompile java based apps using tools like JD-GUI.

Often during dynamic analysis, we feel that, there’s a need to debug the application at runtime as if we had the source code, by placing breakpoints.
***Assuming that we do not have the source code, How do we debug Java based On-Premise Webservers ?***

>

“🚀 JD-Eclipse to the Rescue! 🛠️”

## **Steps to Debug On-Premise Java Web Servers Without Source Code —**

First ,Download and Install “**Eclipse IDE for Enterprise Java and Web Developers**”.

Then, Download and Install **JD-Eclipse** Plugin from [here](https://github.com/java-decompiler/jd-eclipse) into your Eclipse IDE.

**Configure Eclipse IDE to associate *.class files without source code to JD Class File Viewer** as follows. This can be done from “**Window > Preferences > General > Editors > File Associations**”.

*Associate *.class files to use JD Class File Viewer*

**Restart the Eclipse IDE** to finish the JD-Eclipse installation setup successfully.

**Install any Java-based web server for pentesting. In this example, we’ll use [ManageEngine Endpoint Central](https://www.manageengine.com/products/desktop-central/)**.Create any Java Project** in Eclipse IDE, For example, in our case I created a Java project with name EC.

Now open the created java project in Eclipse IDE, **create any valid java file inside project source**. It doesn’t matter what the code does.

*Creating valid java file in project src*

Right click on your project folder in Eclipse IDE, Go to “**Properties” -> “Java Build Path” -> “Libraries” -> “Classpath” -> “Add External JARs**” to **Add jar files/libraries associated with the On-Premise software**.

*Adding Libraries & JARs to debug into the Project Build Path*

*Example of Endpoint Central Libraries & JARs*

### **Enabling remote debugging on java web server —**

This step is dependent on the installed Web server & might require some research & changes depending on your web server,

**You need to configure remote debugging in the webserver by enabling JPDA (Java Platform Debugger Architecture).**

For this, you need to find how the server is started & configure [JPDA](https://stackoverflow.com/a/36420167) before starting the server.

For, **Endpoint Central Server, **By viewing the service properties of “**ManageEngine UEMS — Server**”, We find that, The service is started using command “**D:\BB\Zoho\UEMS_CentralServer\bin\wrapper.exe -s D:\BB\Zoho\UEMS_CentralServer\conf\wrapper.conf**”.

Searching for “**JPDA**” word in **wrapper.conf**, shows we need to uncomment few lines to enable JPDA.

*Enable JPDA in Web Server*

**After configuring the server for JPDA, make sure all changes are saved & restart the server.**

### **Configure Eclipse IDE for Remote Debugging —**

Go to “**Run**” -> “**Debug Configurations**” -> “**Remote Java Application**” -> Right Click & select “**New Configuration**” & **Configure connection properties like Name, JPDA Host & Port** to use for debugging.

## Get Jayateertha Guruprasad’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

From **wrapper.conf** we find that *:8787 is used for debugging, Hence we can configure Host as localhost, Port as 8787 in Eclipse as follows.

*Enabling Remote Debugging in Eclipse IDE*

Name can be configured any, for ex: **EC Debug**.

**Apply and Close the Debug Configurations window** for now after configuring the above parameters.

### **Setting Breakpoint for Debugging —**

Now, as we have configured everything, we should be able to debug. But we need to set a initial breakpoint first to track code flow.

As this is Java based server, It should most probably have web.xml file where servlet & filters are configured. This can give a idea of where we can set initial breakpoint.

Searching for web.xml files in Web server directory, We find that web.xml file exists at “**D:\BB\Zoho\UEMS_CentralServer\webapps\DesktopCentral\WEB-INF\web.xml**”

Searching for “**/***” pattern in web.xml file, We find that all urls pass through **SecurityFilter** as follows**.SecurityFilter** class path is com.adventnet.iam.security.SecurityFilter.

Thus, Search for **com.adventnet.iam.security.SecurityFilter** class in Eclipse IDE & add a breakpoint inside **doFilter()** method.

### Debugging the Java Server —

Go to “**Debug Configurations**” -> Select your previously saved configuration under “**Remote Java Application**”, Click on “**Debug**”.

**Open any url associated with Endpoint Central server in a browser, say “**[http://localhost:8020/client#/login](http://localhost:8020/client#/login)**”.Now we can debug the Java Web Server successfully in runtime, giving us the overview of variable values & expressions useful for dynamic analysis purpose.**

*Debug View in Eclipse IDE*

### **Liked my article ? Follow me on **[LinkedIn](https://www.linkedin.com/in/jayateerthag/)**, Twitter (**[@jayateerthaG](https://twitter.com/jayateerthag)**), and **[Medium](https://jayateerthag.medium.com/)** for more content about bugbounty, Infosec, cybersecurity and hacking.**

---
