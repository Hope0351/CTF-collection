# :electric_plug: Hunting for Prototype Pollution and it’s vulnerable code on JS libraries

---

# Hunting for Prototype Pollution and it’s vulnerable code on JS libraries

It’s been months since I have released [ppmap](https://github.com/kleiton0x00/ppmap) and it didn’t take much for the tool to be popular because of how crazy and trending Prototype Pollution vulnerability actually is.

On this article I’m not going to introduce you what Prototype Pollution is, since there are a lot of articles/videos out there which explain it better than me. This article is a work of several weeks of research on this topic, to bring you new and innovative ideas (well not all of them) on how to scan massively on Javascript Packages ([npm packages](https://www.npmjs.com/) as well) and how to manual debug (for much complex Javascript code) to find the root cause of client-side Prototype Pollution.

## Searching for client-side Prototype Pollution

Well for this type of hunting we are going to use Chrome/Chromium, since they have the Developer Tools which is for sure more compatible for debugging.

The exploitation starts by first finding is the website is vulnerable to client-side prototype pollution or not. We are going to use [ppmap](https://github.com/kleiton0x00/ppmap) which will automatically try different payloads to pollute the variables on global context. After downloading the tool to your local machine, simply run it on the target website by using the following command, simple as that:

```
echo '[https://grey-acoustics.surge.sh](https://grey-acoustics.surge.sh)' | ./ppmap
```

*Prototype Pollution found by ppmap*

Great, let’s open the website with the payload [ppmap](https://github.com/kleiton0x00/ppmap) displayed as vulnerable ([https://grey-acoustics.surge.sh/?constructor%5Bprototype%5D%5Bppmap%5D=reserved](https://grey-acoustics.surge.sh/?constructor%5Bprototype%5D%5Bppmap%5D=reserved)) and open the Console (on Developer Tools) to confirm if we successfully polluted that.

## Setting up the breakpoints

It’s time to find the vulnerable code, so to do that we need to go to Source and set a breakpoint on the first script of the page. The reason to do this is that we don’t want the whole Javascript executed because then we won’t know when ppmap gadget will be polluted. After setting a breakpoint, click on “Resume Script Execution” button. Simply refresh the website to apply the changes, and the website should be Paused on debugger.

*Set a breakpoint and then resume script execution*

In this case Line 7 would be the first executed javascript code so we will put a breakpoint on that line. If we enter ppmap on console, it will be shown as undefined, since the website is stuck on breakpoint and ppmap is not polluted yet.

*Website paused on debugger*

## Checking whenever the property gets polluted with the help of a Snippet code

Now we have to run a Snippet which you can get it from [here](https://gist.githubusercontent.com/dmethvin/1676346/raw/24cde96c341e524dc8706104afbd0748752c7432/gistfile1.txt). The script will set a breakpoint once a property is polluted (in this case ppmap property). To do that, simply to go Source, then click on Snippet and create a new one by adding the code like in the image below:

*Executing the Snippet*

Execute the Snippet and you will just see an “undefined” output on console, means that the Snippet has run successfully.

## Get kleiton0x7e’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Go back to Console tab and execute the following code, which will set a breakpoint automatically once a Pollution happened to “ppmap” property. It means it will redirect us to the vulnerable code where the pollution occurs:

```
debugAccess(Object.prototype, 'ppmap')
```

*command executed on console*

There is no output, but that is completely fine.

## Finding the root cause of Prototype Pollution

Go back to Sources and click “Resume script execution”. After you do that, the whole javascript will be executed and ppmap will be polluted again as expected. With the help of the Snippet we can find where exactly the ppmap property is polluted. We can click on the Call Stack and you will face different stacks where the pollution happened.

But which one to choose? Most of the time Prototype Pollution happens on Javascript libraries, so aim for the stack which is attached to the .js library files (look at the right side just like in the image to know which endpoint the stack is attached to). In this case we have 2 stacks on line 4 and 6, logically we will choose the 4th line because that line is the first time where Pollution happens, which mean that this line is the reason of the vulnerability. Clicking on the stack will redirect us to the vulnerable code.

With the help of Beautifier, we can see the vulnerable code of the JS library:

```
params.replace(/\+/g, ' ').split('&').forEach(function(v) {
var param = v.split('='),
key = decodeURIComponent(param[0]),
val, cur = obj,
i = 0,
keys = key.split(']['),
keys_last = keys.length - 1;
if (/\[/.test(keys[0]) && /\]$/.test(keys[keys_last])) {
keys[keys_last] = keys[keys_last].replace(/\]$/, '');
keys = keys.shift().split('[').concat(keys);
keys_last = keys.length - 1;
} else {
keys_last = 0;
}
```

This is not the only reason why the website is vulnerable, if we see closely on the Stacks, there is one more endpoint where ppmap is being polluted (which is located to the index HTML page):

*One more stack to the HTML code*

So here is the vulnerable code of the index HTML page:

```
var query = deparam(location.search.slice(1));
```

If you have some experience with Javascript you will directly identify the issue here. The exploitation starts with the injection of a payload into an input (this case on URL parsing) that is used to build the client-side logic or rendering of the application. The most common source of input is the URL and its different properties, like location.search

---
