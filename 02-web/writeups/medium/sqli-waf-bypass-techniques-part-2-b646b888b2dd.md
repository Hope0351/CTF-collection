# :globe_with_meridians: SQLi WAF Bypass Techniques Part 2

---

# SQLi WAF Bypass Techniques Part 2

In our last session, we learned primary Time-Based SQL injection WAF bypasses. This time, we will move one step further and try to beat WAF rules for other SQL injection types. Let’s review other ways in which some defenses could be implemented and how to bypass them.

## Defensive Side

Let’s start directly from the defensive side with the already prepared firewall rule. Depending on the target (if it is security-hardened or not), there could be advanced defenses in place. It really depends on how seriously the security team of the program adds some extra layer of protection. Let’s explore the following example:

It will convert the URL query to lowercase and check for 2 blacklisted words: AND and OR.

## Identifying Blacklisted Strings

When we initially approach the target, we won’t know what firewall rule will be present. We can only get some presumptions after getting indications from tools like Ghauri or SQLmap (or by testing manually, of course). If you get blocked by the Web Application Firewall, initially, you want to check which words could be filtered out:

It is pretty similar to bypassing XSS, where you want to check which HTML tags are being filtered out; this time, you want to check which known SQL commands are being filtered out. From the black-box testing perspective, we can see that AND and OR strings are being filtered but not their logical symbols — && and ||. Identifying those strings is the initial step of the WAF Bypasses process.

## Using Atlas to Identify Tampering Script

I have seen some people suggesting using the [Atlas](https://github.com/m4ll0k/Atlas)tool for sqlmap tamper detection. Even though it was updated four years ago, it’s still a valid option for WAF Bypasses. I personally do not use it that much since it could truly create a lot of false positives and it will be wasting my time. But let’s see it in action, and I will let you decide for yourself!

## Preparing Payload For Atlas

Before running Atlas for tamper suggestions, you will need to get an initial payload for SQL injection. You can construct it yourself, or you can use sqlmap. The sqlmap has a verbosity option. To see payloads, you need to set verbosity to at least 3:

There are verbosity levels up to five but those will give a lot of information that we don’t need. We need to copy one of the payloads after running sqlmap:

Next, you need to paste it for the Atlas tool:

```
python3 atlas.py -u 'target.com/endpoint.php?key=value' -p "<YOUR_PAYLOAD>" --random-agent -v
```

As you can see, it gave us a lot of results, although it’s still useful because I know one of them should work:

All in all, you will be spending a lot of time checking each of those tampers. There is a much better way that I personally use, so let me show you.

## Exploring sqlmap Tamper Scripts For WAF Bypasses

Usually, I have a separate tab in the terminal prepared just for showing all sqlmap tampers. To list them out you can simply run the following command:

```
sqlmap --list-tampers
```

There is much to choose from, but if you remember, we need to replace AND and OR strings with logic operators. What I like to do in this case is use the grep command for filtering together with some regex:

```
sqlmap --list-tampers | grep -E " AND | OR "
```

We can see only two of them left out instead of choosing all of them. The symboliclogical tamper script might work the best in our particular case:

```
sqlmap -u 'http://k1t.uk/listproducts.php?cat=1' --random-agent --flush-session --technique=B --hostname --batch --tamper=symboliclogical
```

## Bypassing Rate Limiting Rules

We could play around the whole day doing this, just checking the blocked strings and trying to find ways to bypass them. In real-world scenarios, other elementary blocks could be implemented, like here:

It will check how many requests go from the same IP to our specified endpoint. In this case, if that endpoint receives 10 requests per 10 seconds, your IP will get blocked for some time. In other cases, it could get blocked indefinitely. I recommend using [NordVPN](https://ott3rly.com/nordvpn)and switching your IP in case this happens. This is a VPN that I use; it’s excellent, and I do recommend it. You can get a discount if you use [my link](https://ott3rly.com/nordvpn).

## Get Ott3rly’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

If you don’t want to get blocked in the first place, I suggest using the -delay option in both sqlmap and ghauri. It will be more gentle on the website because you can specify how many seconds between each request to send. Of course, your sqlmap will be much slower, but in this case, your IP will be good to go.

## Last Thoughts

Thank you very much for reading this post. It was my pleasure to share two more extra tips on this topic. This was a pretty short writeup, but we explored both the defensive and offensive sides of the coin.

If you find this information useful, please share this article on your social media, I will greatly appreciate it! I am active on [Twitter](https://ott3rly.com/twitter), check out some content I post there daily! If you are interested in video content, check my [YouTube](https://ott3rly.com/youtube). Also, if you want to reach me personally, you can visit my [Discord](https://ott3rly.com/discord) server. Cheers!

---
