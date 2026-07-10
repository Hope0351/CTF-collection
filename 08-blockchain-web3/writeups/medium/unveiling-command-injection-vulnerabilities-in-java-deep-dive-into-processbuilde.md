# :link: Unveiling Command Injection Vulnerabilities In Java Deep Dive Into Processbuilde

> **Original Source:** [Unveiling Command Injection Vulnerabilities In Java Deep Dive Into Processbuilde](https://infosecwriteups.com/unveiling-command-injection-vulnerabilities-in-java-deep-dive-into-processbuilder-and-runtime-50d8e25d06ab)
> **Platform:** infosecwriteups.com | **Category:** `BLOCKCHAIN`

---

### PROCESS BUILDER


- ProcessBuilder Syntax


Before delving into potential vulnerabilities, let’s first understand the various syntax offered by ProcessBuilder.


```
private static void syntaxExplained(){
String userInput = "touch example1";
//All these 4 Syntax are Same

//METHOD1: Using constructor ProcessBuilder(String...)
ProcessBuilder pb1 = new ProcessBuilder("sh", "-c", userInput);

//METHOD2: Using constructor ProcessBuilder(String[])
String[] cmdList = new String[] {"sh", "-c", userInput};
ProcessBuilder pb2 = new ProcessBuilder(cmdList);

//METHOD3: Using command(String...)
ProcessBuilder pb3 = new ProcessBuilder();
pb3.command("sh", "-c", userInput); //Overrides if anything was passed in ProcessBuilder("cmd")

//METHOD4: Using command.add(string)
ProcessBuilder pb4 = new ProcessBuilder();
pb4.command().add("/bin/sh"); //Keeps appending to the list
pb4.command().add("-c");
pb4.command().add(userInput);
}
```


2. ProcessBuilder(UserInput)

>

When a *command* contains spaces, processBuilder wraps it inside double quotes.


- Only a single input command will work.

- This is because the entire userInput is interpreted as the binary name, potentially leading to a “Program not found” error.


```
private static void insecurePB_DirectInput() throws IOException {
String userInput = "whoami"; //Works
String userInput2 = "touch test"; //Error: Program "touch test" not found

ProcessBuilder pb = new ProcessBuilder(userInput);
Process processInfo = pb.start();
}
```


3. ProcessBuilder(UserInput.split())


- Here, the first item will be treated as the binary name and the rest will be considered as its argument.

- So, we can directly run any arbitrary command.


```
private static void insecurePB_DirectInput_SpaceSplit() throws IOException {
String userInput = "touch /tmp/testing/hacker1";
String[] cmdList = userInput.split(" "); //This makes it => [touch, "/tmp/testing/hacker3"], so valid

ProcessBuilder pb = new ProcessBuilder(cmdList);
Process processInfo = pb.start();
}
```


4. ProcessBuilder(“sh -c <userInput>”)


- This will spawn a shell and can run any arbitrary command.


```
private static void insecurePB_BinSh_ArgInput() throws IOException {
String userInput = "touch /tmp/testing/hacker2";

ProcessBuilder pb = new ProcessBuilder("sh", "-c", userInput); //Vuln: Can directly run any command
Process processInfo = pb.start();
}
```


5. ProcessBuilder(“sh -c <binary> <userInput>”)


- This will also spawn a shell and can run any arbitrary command.


```
private static void insecurePB_BinSh_Binary_AppendInput() throws IOException {
String userInput = "test; touch /tmp/testing/hacker3";

//Vuln
ProcessBuilder pb = new ProcessBuilder("/bin/sh","-c", "curl" + userInput).start();

//Vuln
ProcessBuilder pb2 = new ProcessBuilder("/bin/sh","-c", "curl " + userInput).start();

//Safe: As "curl + userInput" will be treated as binaryname, errors with program not found
ProcessBuilder pb3 = new ProcessBuilder("curl " + userInput).start();
}
```


6. Argument Injection — InputSplit


- If the userInput is split and passed into ProcessBuilder following a command, it may become vulnerable to Argument Injection.


```
private static void insecurePB_ArgumentInjection_InputSplit() throws IOException {
String userInput = "* -exec whoami ;";


ProcessBuilder pb = new ProcessBuilder("find", "/tmp/testing", "-name");
pb.command().addAll(Arrays.asList(userInput.split(" "))); //Vulnerable to argument injection

Process processInfo = pb.start();
}

```


7. Argument Injection — Python/Bash/OtherLang


- This scenario can be exploited by finding a way to upload a malicious file onto the server and then executing it.


```
private static void insecurePB_Python_ArgInput() throws IOException,InterruptedException {
String userInput1 = "/tmp/testing/exploit.py";
ProcessBuilder pb1 = new ProcessBuilder("/usr/bin/python3",userInput1);
Process process1 = pb1.start();


String userInput2 = "/tmp/testing/exploit.sh"; //Ex Scenario: Exploit Script uploaded via fileupload
ProcessBuilder pb2 = new ProcessBuilder("/bin/sh",userInput2);
Process process2 = pb2.start();


```


8. Secure: Argument Injection


```
private static void securePB_ArgumentInjection() throws IOException,InterruptedException {
String userInput = "* -exec whoami ;";

ProcessBuilder pb = new ProcessBuilder("find", "/tmp/testing", "-name", userInput);
ProcessBuilder pb = new ProcessBuilder("find", "/tmp/testing", "-name");
pb.command().add(userInput);
Process processInfo = pb.start();
printProcessBuilderOutput("insecurePB_ArgumentInjection()", pb, processInfo); //Wont't work as the entire input is treated as arg value for -name
//ProcessBuilder pb = new ProcessBuilder("find", "/tmp/testing", "-name", "*", "-exec", "whoami", ";"); //This will work


//Also Secure: Coz userinput1 is taken as value for flag -t
String userinput1 = "-f";
String userinput2 = "/etc/password";
ProcessBuilder pb = new ProcessBuilder("ssh-keyscan", "-t", userinput1, userinput2);
}
```


9. Secure: Process Builder


```
private static void securePB() throws IOException,InterruptedException {
String url = "http://sickuritywizard.com; touch /tmp/testing/hacker0";

ProcessBuilder pb = new ProcessBuilder("/usr/bin/curl",url);
Process processInfo = pb.start();
}
```


---

*Originally published on [Medium](https://infosecwriteups.com/unveiling-command-injection-vulnerabilities-in-java-deep-dive-into-processbuilder-and-runtime-50d8e25d06ab). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of blockchain CTF writeups.*
