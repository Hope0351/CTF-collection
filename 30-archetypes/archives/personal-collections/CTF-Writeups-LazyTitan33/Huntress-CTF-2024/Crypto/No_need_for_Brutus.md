# No need for Brutus



## My Solution

The title is a clear reference to Caesar and the Caesar Cipher also known as ROT13. However, in this case, using [cyberchef](https://gchq.github.io/CyberChef/#recipe=ROT13(true,true,false,10)&input=c3F1aXFoeWlpeWNmYnVkZWR1dXR2ZWhyaGtqa2k) we just need to rotate 10 times to find a readable string:  



And then MD5 sum it using [cyberchef](https://gchq.github.io/CyberChef/#recipe=ROT13(true,true,false,10)MD5()&input=c3F1aXFoeWlpeWNmYnVkZWR1dXR2ZWhyaGtqa2k) since we are already in it, to get the correct hash for the flag:  



flag{c945bb2173e7da5a292527bbbc825d3f}
