# :game_die: FluxCloud Frontline. Hack.lu Writeup

---

# FluxCloud Frontline

The challenge FluxCloud Frontline (web, hard) was part of the amazing Hack.lu CTF. It took a friend and me, both playing for the team FAUST, two evenings to crack the great challenge.

In the following, I describe the plain solution and leave out the many rabbit holes we stepped into.

## The Challenge

>

With our brand-new FluxCloud Frontline product, we offer hyper-secure, ultra-rapid edge routing. Of course we have a bug bounty program too! If you can bypass our protections, you will be rewarded with a juicy flag. [https://public.frontline.cloud.flu.xxx:8443/](https://public.frontline.cloud.flu.xxx:8443/)

When we open the challenge, we are provided with the source code of the project. The project consists of various server layers as can be seen in Fig1.

*Fig1: The general setup of the challenge*

First, a request to the domain *frontline.cloud.flu.xxx *enters the firewall. The firewall, implemented as haproxy, decides looking at the subdomain, whether the request is forwarded to the router or rejected. Rejected is everything except for the subdomain *public*.*frontline.cloud.flu.xxx.*

In the next step, the Nginx router forwards the request to the public, private, or metadata server, depending on the subdomain and the path. The path */_meta/flag*, which obviously gives us the flag, is denied.

The goal is to smuggle a request through or past the firewall and the router to call and receive the flag.

## Firewall Bypass

The first stage of the challenge is to bypass the firewall and to ship the request successfully to the secret server.

Below we can see the important parts of the *haproxy.cfg:*

```
frontend ft_ssl_vip
bind 0.0.0.0:443
mode tcp

acl app_public req_ssl_sni -i public.frontline.cloud.flu.xxx
acl app_secret req_ssl_sni -i secret.frontline.cloud.flu.xxx use_backend bk_ssl_app_public if app_public
use_backend bk_ssl_app_secret if app_secret default_backend bk_ssl_defaultbackend bk_ssl_app_public
mode tcp
server server1 router:443 checkbackend bk_ssl_app_secret
mode tcp
# Block access to the secret page!
tcp-request content reject
server server1 router:443 check
```

The bold lines in the config decide the server looking at the Server Name Indication (SNI) in which the hostname of a TLS connection is stored. However, the Nginx router looks at the server name of the HTTP layer.

## Get FHantke’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

This is the flaw that we can use to route our traffic to the secret server. We set the SNI to public but the HTTP host to secret.

In python we can set the SNI in the SSL context and the HTTP host in the HTTP request (full exploit in the end):

```
sslContext = ssl.create_default_context()
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock = sslContext.wrap_socket(s,
server_hostname="public.frontline.cloud.flu.xxx")# "GET / HTTP/1.1\r\n" +
# "Host: secret.frontline.cloud.flu.xxx\r\n"
```

## Router Bypass

Being able to bypass the firewall, the next challenge is the router. The router config denies all requests to the flag endpoint and routes the traffic to the corresponding server, looking at the path location:

```
location / {
proxy_pass [http://app-secret](http://app-secret);
}
location /_meta/api/ {
rewrite ^/_meta(.*)$ $1 break;
proxy_pass [http://metadata](http://metadata);
}

location /_meta/flag {
deny all;
}
location /_meta/socket.io/ {
rewrite ^/_meta(.*)$ $1 break;
proxy_http_version 1.1;
proxy_set_header Upgrade $http_upgrade;
proxy_set_header Connection "Upgrade";
proxy_pass [http://metadata](http://metadata);
}
```

We can see that the metadata server uses socket.io to communicate via WebSockets with the app-secret server. Furthermore, the metadata server contains an open-redirect endpoint `/_meta/api/check?hostname=xy `to send check requests to the hostname (used internally for checking the public and secret server).

With this in mind, we googled for request smuggle vulnerabilities in Nginx and socket.io and eventually found what we were searching for. The situation described in [scenario 2 in the linked post](https://github.com/0ang3el/websocket-smuggle) requires Nginx, socket.io, an internal API (our flag API), and an open-redirect — exactly what we are facing.

The mentioned post describes that we can use the open-redirect to redirect a request to our malicious server. The malicious server has to respond with HTTP 101 which tells the target server to open a WebSocket connection to our client. Via this WebSocket connection, however, we can still send HTTP requests, for instance to the internal API and bypass the router.

*Fig2: The request flow of the request smuggle*

## Final Solution

So the final solution looks as follows. I run it on a Digital Ocean droplet to react to the open-redirect.

And tada, here is the flag:

```
('31.22.122.203', 37290) connected
b'HTTP/1.1 101 Switching Protocols\r\nServer: nginx/1.19.3\r\nDate: Sat, 24 Oct 2020 18:44:08 GMT\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: 2\r\nConnection: upgrade\r\nX-Powered-By: Express\r\nETag: W/"2-eoX0dku9ba8cNUXvu/DyeabcC+s"\r\n\r\n'
send payload
b'HTTP/1.1 200 OK\r\nX-Powered-By: Express\r\nConnection: keep-alive\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: 58\r\nETag: W/"3a-jCTYnFrMoq94M55Ba2sPa6ZdkWU"\r\nDate: Sat, 24 Oct 2020 18:44:08 GMT\r\n\r\nflag{th1s_isnt_y0ur_f1rst_t1me_p3netr4ting_fir3walls_huh?}'
```

flag{th1s_isnt_y0ur_f1rst_t1me_p3netr4ting_fir3walls_huh?}

---
