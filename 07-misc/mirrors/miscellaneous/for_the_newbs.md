## USCGA Cyber Security Team


![An early computer](http://s7.computerhistory.org/is/image/CHM/500004289-03-01?$re-medium$)  
Hey maaaan, nice TI-30x




Welcome to the world of cyber security! Whether this is your first step into our world, or you are a cyber wizard; we are happy to have you! Learning about cyber security is a rewarding journey that will allow you to "pull back the curtain" on the world of technology. 

We all have our own reasons for dedicating our time to this craft, mabye you want to learn how computers/phones/internet work, or you are interested in the "internet of things", mabye you read about a recent hack (I'm looking at you Target), or you want to defend yourself in this hectic world, or mabye you just want to become a 133t hacker (I'm not judging). 

**A warning to the timid:** the skills you will learn are technical in nature. You will encounter problems that have very real world implications. So if you find yourself stuck, or getting angry at the 1s and 0s, please refrain from putting your fist through your computer. Take a deep breath, if this wasn't challenging it wouldn't be rewarding. _All is well_.

I have organized lessons like a skill tree, everyone starts at the bottom and builds their way up to one, or many of the branches. Everyone starts at the same point and will learn universally important skills. Here I will also give you a taste of each of the specialty branches you can focus on (not all inclusive by any means). 

The most important _skill_ you can develop is your persistance tackling new problems, and your initiative to research things you do not yet know.

**ToDo:** Do these exercises/lessons/readings  
**Resources:** Extra references, mabye you found something confusing/awesome, don't limit yourself to just these links!  
**Bonus:** If you feel like going the extra mile

### Core Competencies
1. Installing Linux  

  Linux is the operating system of choice for most cyber wizards because it is entirely open source.  I recommend using [Ubuntu 16.04] (a linux distribution), I also recommend [dual booting]. Just trust me on this one, you'll learn to love linux

2. Learn the Command Line  

  Linux relies a lot less on a [graphical user interface] (GUI) than you're probably use to. Most everything will be done from the command line in a "terminal". That's okay! Most of your cyber fun will be done from the command line anyway, and you'll catch on quick!

 **Motivation:**  
 [Go Linux, or go home]

 **ToDo:**  
 [Code Academy Linux Command Line]  \(Don't buy the pro edition, you won't need it)  
 [Over the Wire: Bandit] \(Do challenges 1-11, keep track of level passwords!)

 **Resources:**  
 [Ryan's Command Line Tutorial] \(My personal favorite)

3. Learn a Scripting Language  

 The ability to program is akin to a force multiplier. Instead of working on a problem one solution at a time, you will be able to leverage computing power to try thousands of solutions in a similar time span. This is a critical skill in most aspects of cyber security. Here you will learn the basics of a scripting language. You may have programmed before in Java or C++, these are compiled languages. A scripting language like Python, or Ruby, differs from a compiled language because it doesn't require explicit compilation. It is much quicker to write a script, and a language like Python has loads of libraries that make it great for cyber. Additionally, linux distros like Ubuntu already have python 2.7 built in. Here you're looking to get down the basics of python, we'll look at some important libraries later.

 Choose one of the programming tutorial "ToDos" and do the challenges. If you have never programmed before either tutorial will work great. Code Academy will get you the basics quicker than LPTHW, but I think LPTHW is more thorough. If you have programmed before, eg: you know about for and while loops, maybe some object oriented experience, I recommend LPTHW because it is easier to jump around to fill in knowledge gaps. I highly recommend learning up to and including the basics of Object Oriented Programming (OOP), this will help your understanding later.

 _This is definitely not something you want to rush_

 **Motivation:**  
 [Welcome to the future, it's autonomous] \(You'll see these guys again)

 **ToDo:**  
 [Code Academy Learn Python] \(Once again, don't buy the pro edition)  
 [Learn Python the Hard Way] \(LPTHW, definitely not the hard way)

 **Resources:**  
 [Python Documentation] \(Home sweet home)

 **Bonus:**  
 [Codewars] \(A variety of coding challenges varying in difficulty)  
 [Project Euler] \(Math/Logic based coding challenges ordered by level of difficulty)


4. Learn Basic Network Termonology

  Networks are a fundamental part of cyber security and technology as a whole. Most devices today are connected in some way, eg: the [Internet of Things] \(IOT), and this interconnection of devices is only going to become more profound. Learning some of the basics about networks will help guide your research in the future.

  Please enjoy the resources in order, it'll make more sense that way

  **Motivation:**  
  [Thinking about taking a drive?]
  
  **ToDo:**  
  [Introduction to Network Terminology]  
  [Switches vs. Routers]  
  [IP Addresses]  
  [What is DHCP]  
  [What is NAT] \(Read pages 1-4)  
  [Client/Server]  
  [Introduction to DNS]  
 
  **Bonus:**  
  [Another Computer Networking Intro] \(Talks about HTTP)  
  [Samba] \(This'll pop up from time to time)  
  [Khan Academy Internet 101] \(A really great resource, that I highly recommend)

5. Brief Introduction to Cyber Specialties  

  Up to this point everything you have learned has provided a foundation for more specialized fields of cyber security. On our team we want our members to be strong in one of the following areas: Web Applications, Forensics (Network and Computer), Cryptography, Reverse Engineering, and Operating Systems and Network Engineering. In each area you will learn both offensive and defensive skills. Here we want to give you a taste of what each option offers you. Please do the exercises in each category, you may surprise yourself!

  **Web Applications:**  
  Web applications are everywhere. They are any client-server application that lives in a web browser. As an attacker you can gain access to the severs running the appliction, or the backend databases storing user information such as passwords, credit card numbers, and email addresses. More than half of all real world breaches (that are discovered) are done through web applications. Check out this list of [common web app vulnerabilities]. If you decide to pursue this area further you will learn how websites are created and common vulnerabilities and how to exploit/defend against them.  
  
  **ToDo:** [Over the Wire: Natas] \(Do levels 0-5, 3-5 require a tool called Burp Suite)

  **Forensics:**  
  Forensics is a puzzle where you, the analyst, will determine what actions a user performed in the past. You will work with both networks and computers to track and remove malware. Once a computer has been infected (this is a matter of when, not if), the clock starts ticking. A strong knowledge of forensics will help you to minimze the damage done to the greater network of computers. You will learn about both windows and linux file systems; specialized tools to examing hard disks and RAM; common malware, how it works, and where it lives. All of our CTF and live attack and defend challenges involve specialized forensics challenges.

  **ToDo:**

  **Cryptography:**  
  Cryptography is the oldest field of security. Ever since people could communicate there has been a need to do so secretly. Modern day encryption methods can be very strong, and impossible to break if done _correctly_. _Correctly_ is the key word here. Many times old enryption methods are used or modern methods are implemented incorrectly. It is not enough to that know a method is bad, you must be able to break the encryption. The difficulty of this task can vary from being trivial to requiring a significant amount of skill. The goal is for you to learn about existing cryptographic techniques and how to break them (if possible). If you pursue crypto you will develop strong programming abilities and learn leverage mathematics when tackling problems.

  **ToDo:**

  **Reverse Engineering:**  
  Reverse engineering is the process of breaking open a compiled program to understand how it works. This can be taken a step further by exploiting the program to gain information stored in memory, force code execution on the victims machine, and eventually get shell access. Reverse engineering and binary exploitation is a major component of the CTFs and live attack and defend competitions we attend. By choosing this area you will learn the C programming language, Assembly level programming, and common binary exploitation attacks. You will also learn how to patch programs to secure them from attack.

  **ToDo:**

  **Operating Systems and Network Engineering**  
  This area is not as specific as the previous ones. Instead, it fills a void that became apparent after competing in the Cyber Defense Exercise (CDX) as a blue team. Here you will learn how to setup networks and segregate clients, services, and users. You will learn about implementing ipv4 and ipv6; user and network level firewalls; the different services running, such as DNS and Mail. Hardening operating systems, both windows and linux, is also covered here. Lastly, it will be important to develop programming skills in python, bash, and powershell to automate the tasks you perform. 

  **ToDo:** 


**Acknowledgments**  
Author: Patrick Ledzian  
Created: Saturday, August 6th, 2016  
Last Updated: Sunday, August 21th, 2016


[Another Computer Networking Intro]: https://betterexplained.com/articles/a-simple-introduction-to-computer-networking/

[Client/Server]: http://searchnetworking.techtarget.com/definition/client-server

[Code Academy Learn Python]: https://www.codecademy.com/learn/python

[Code Academy Linux Command Line]: https://www.codecademy.com/learn/learn-the-command-line

[Codewars]: https://www.codewars.com/

[common web app vulnerabilities]: http://www.veracode.com/security/web-application-vulnerabilities

[dual booting]: http://www.howtogeek.com/187789/dual-booting-explained-how-you-can-have-multiple-operating-systems-on-your-computer/

[Go Linux, or go home]: http://null-byte.wonderhowto.com/forum/why-every-hacker-should-know-use-linux-0151287/

[graphical user interface]: https://www.google.com/#q=graphical+user+interface

[Internet of Things]: http://www.wired.com/2014/01/theres-no-good-way-to-patch-the-internet-of-things-and-thats-a-huge-problem/

[Introduction to DNS]: https://www.digitalocean.com/community/tutorials/an-introduction-to-dns-terminology-components-and-concepts

[Introduction to Network Terminology]: https://www.digitalocean.com/community/tutorials/an-introduction-to-networking-terminology-interfaces-and-protocols

[IP Addresses]: http://www.computernetworkbasics.com/2013/10/what-is-an-ip-address/

[Khan Academy Internet 101]: https://www.khanacademy.org/computing/computer-science/internet-intro

[Learn Python the Hard Way]: http://learnpythonthehardway.org/book/

[Over the Wire: Bandit]: http://overthewire.org/wargames/bandit/

[Over the Wire: Natas]: http://overthewire.org/wargames/natas/

[Project Euler]: https://projecteuler.net/archives

[Python Documentation]: https://docs.python.org/2/

[Ryan's Command Line Tutorial]: http://ryanstutorials.net/linuxtutorial/#houserules

[Samba]: https://www.samba.org/samba/docs/using_samba/ch01.html

[Switches vs. Routers]: http://www.cisco.com/cisco/web/solutions/small_business/resource_center/articles/connect_employees_and_offices/networking_basics/index.html

[Thinking about taking a drive?]: https://www.wired.com/2015/07/hackers-remotely-kill-jeep-highway/

[Ubuntu 16.04]: http://www.ubuntu.com/download

[Welcome to the future, it's autonomous]: http://www.darkreading.com/attacks-breaches/team-with-carnegie-mellon-roots-wins-machine-hacking-contest-/d/d-id/1326524

[What is DHCP]: http://www.computernetworkbasics.com/2013/03/how-dhcp-works/

[What is NAT]: http://computer.howstuffworks.com/nat.htm
