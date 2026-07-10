# :arrows_counterclockwise: Serialization&Deserialization Attacks

> **Original Source:** [Serialization&Deserialization Attacks](https://infosecwriteups.com/serialization-deserialization-attacks-on-php-d5fb02e29248)
> **Platform:** infosecwriteups.com | **Category:** `REVERSE ENGINEERING`

---

# Serialization&Deserialization Attacks


Hello everybody, today I will try to explain how serialization vulnerabilities work.


Before we destroy the pyramids, we need to learn how they built them.


So the first question is what are serialization and deserialization?


Serialization:


Serialization is a mechanism of converting the state of an object into a byte stream.


So basically, it works like that:


Serialization means transforming something (e.g. dog Rex) into a series of 1s and 0s which can be transported over the phone line, stored in memory. My friends overseas can then translate those 1s and 0s back into a perfect representation of a puppy (de-serialization) so they can enjoy Rex’s company.


Why do we need it?


Here’s a simple analogy to understand why we need to serialize data in certain situations: say you’ve got an idea and you want to describe it to your friend. Unfortunately, you’re at home and your friend somewhere else so you decide to write a mail, describing your idea. See what you just did? You serialized the stuff in your head into a mail, something that can be transmitted, stored, rendered, and finally read by your friend. Reading this mail and building an internal model of the idea in the brain is surprised, then the de-serialization process. So, computers are really only copycats of natural processes ;)


For more information, you may look at the below link:


Deserialization:


Deserialization is the reverse process where the byte stream is used to recreate the actual object in memory.


Basically :D

*LOL*


As the legend said, LET’S JUMP INTO THE PRACTICAL THINGS.


Serializing Data on PHP:


*Serialization*Left Pane(Code Description):


In the left pane,


```
class User{public $username;
public $password;
}
```


We create a class User and we assign $username and $password in this class.


`*$obj = new User();*`


We set a new User to our object, and we basically said:


```
*$obj->username=’zer0d’;
$obj->password=’mypass123';*
```


this $username member of $obj


this $password member of $obj


```
*echo serialize($obj);*
```


At the last point, we call our Serialization function with $obj to serialize our object.


Right Pane(Run time):


In the right pane, we are seeing our object as serialized version.


```
*O:4:”User”:2:{s:8:”username”;s:5:”zer0d”;s:8:”password”;s:9:”mypass123";}*
```


what does it mean?


```
Ex: (Type:object):(4 character):( “It is User”): (it has 2 variable)
```


Deserializing Data on PHP:


```
*$obj = unserialize($_POST[‘cmd’]);*
```


On the server-side, a code running like the above deserializes the received serialized objects. I know it is confusing a little bit.


Let’s try to understand the process.


1- The application server serialized the object to send it then sends it to the client browser.


## Get zer0dac’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


2- The attacker finds the serialized object, let's say it was a cookie.


3- If the cookie was encoded as base64, first of all, the attacker needs to decode it to see the string. After then it is a serialized object, so he needs to deserialize it to see what is in the object. At that point, the object probably stores variables like username, isAdmin, etc.


There are two things you need to be careful of while you are doing a serialization attack.


As you know, the characters create strings. And some of the languages separate them if there are characters with meaning these are strings and if there are characters one by one they are characters. But when we are attacking, we will send an object(this attack is object injection), if we send it with changing strings, PHP language can not convert string to object in it. So we need to inject out the malicious objects to the non-string value like boolean, etc.


After we inject our payload, we can serialize it and sent it back.


PHP magic methods are special methods in a [class](https://www.phptutorial.net/php-oop/php-objects/). The magic methods override the default actions when the object performs the actions.


By convention, the names of magic methods start with a double underscore (`__`). And PHP reserves the methods whose names start with a double underscore (`__`) for magic methods.


Every magic method follows certain rules:


-Every magic method starts with a double underscore ( __ ).


-They are predefined and neither can be created nor removed.


-Magic methods have reserved names and their name should not be used for other purposes.


-Magic methods are automatically called when certain criteria are met.


Ex:


__construct()


This method gets called automatically every time the object of a particular class is created.


The function of this magic method is the same as the constructor in any OOP language.


*Examples*


In the attack, the serialization part is like a door, so if they didn’t check our input while serializing that means the door is open. But in order to steal gold, you need to open the drawer. In the codes, the drawer is magic functions.


So, the thing is only serialization is not actually dangerous, we need to jump to magic methods to harm the system with serialization. Otherwise, our payload will be deserialized but the payload can not be executed on the system.


In conclusion of the above two things, the trick is that you need to find the value which is not a string and you need to jump to vulnerable functions(magic methods)by using non-string values to do serialization attack successfully. You will see more details in the attack simulation.


4- The browser sending this request to the backend server.


5- The application deserializes it, to see what’s in the serialized data. In this step, our payload calls the function with harmful wishes :).


6- Shell executed.


Attack Simulation:


Firstly, let’s look at the server-side codes:

*server.php*


As it is a simulation, the code is actually not functional, but let’s think that the developers try to get usernames from clients via the post method and then deserialize it. Also, in the different parts of the code, they are using a magic method __tostring for getting file contents. At that point, if we deserialize the object and serialize it in a malicious way, we can run our dangerous wishes via jumping to the magic method.


Attacker Side:

*attacker.php*


We are writing our PHP script to serialize the same data form with the __construct function to read files from the system. This script creates malicious serialized data.


output:


As you can see in the output, s:8:username is a string value that is pointing to object ReadFile, so with that data, we can send it to the server over browser and run the magic methods with our input on the server-side. So let's copy it to send it via curl.


We have sent a post request to the server with our serialized malicious data.


BOOM! We can read the proof.txt, which is highlighted in the above image.


---

*Originally published on [Medium](https://infosecwriteups.com/serialization-deserialization-attacks-on-php-d5fb02e29248). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of reverse engineering CTF writeups.*
