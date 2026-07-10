# :game_die: Hack The Box Synced Rsync C8Cef67C795A

---

### Rsync on Port 873: A Gateway for Efficient File Synchronization

The best known file transfer service is the File Transfer Protocol (FTP), which was covered thoroughly in the Fawn machine. The main concern with FTP is that it is a very old and slow protocol. FTP is a protocol used for copying entire files over the network from a remote server. In many cases there is a need to transfer only some changes made to a few files and not to transfer every file every single time. For these scenarios, the rsync protocol is generally preferred.

Rysnc is a versatile file synchronization tool. It is an open source tool and provides fast incremental file transfer. The official definition of rsync according to the Linux [manual](https://linux.die.net/man/1/rsync) page is:

>

Rsync is a fast and extraordinarily versatile file copying tool. It can copy locally, to/from another host over any remote shell, or to/from a remote rsync daemon. It offers a large number of options that control every aspect of its behavior and permit very flexible specification of the set of files to be copied. It is famous for its deltatransfer algorithm, which reduces the amount of data sent over the network by sending only the differences between the source files and the existing files in the destination. Rsync is widely used for backups and mirroring and as an improved copy command for everyday use.

The core strength of rsync lies in its “[delta](https://en.wikipedia.org/wiki/Delta_update)-transfer” algorithm. Instead of blindly copying entire files, rsync intelligently identifies and transmits only the differences between the source and destination files, resulting in significantly faster and more network-efficient transfers.

The main stages of an rsync transfer are the following:

- rsync establishes a connection to the remote host and spawns another rsync receiver process.

- The sender and receiver processes compare what files have changed.

- What has changed gets updated on the remote host.

The way rsync works makes it an excellent choice when there is a need to synchronize files between a computer and a storage drive and across networked computers. Because of the flexibility and speed it offers, it has become a standard Linux utility, included in all popular Linux distribution by default. More information about rsync can be found at the [Wikipedia](https://en.wikipedia.org/wiki/Rsync)page.

### Connecting and Interacting with the Rsync Service

Interaction with an rsync service is primarily achieved through the `rsync` command-line utility (pre-installed in linux distributions), a standard feature in most Unix-like operating systems. The fundamental syntax for connecting to a remote rsync daemon is:

```
rsync [OPTIONS] [USER@]HOST::[MODULE] [DESTINATION]
rsync [USER@]HOST:: (for listing available modules)
```

This command will attempt to connect to the rsync daemon on `HOST/IP/USER@ `and list the publicly accessible modules.

Anatomy of the Connection String:

- `[OPTIONS]`: Thisrefers to the available options in `rsync` . The list with all valid options is available over at the official manual [page](https://linux.die.net/man/1/rsync) of rsync under the section Options Summary . You can also view it by using the — `help `command: `rsync — help`.

- `[USER@]HOST`: This specifies the remote server's hostname or IP address. You can optionally provide a username if the rsync module requires authentication. The `[USER@]` optional parameter is used when we want to access the the remote machine in an authenticated way. In this machine (synced), we don’t have any valid credentials at our disposal so we will omit this portion and try an anonymous authentication.

- `::`: The double colon is crucial. It signifies a connection to an rsync daemon on the specified host, as opposed to using a remote shell like SSH.

- `[MODULE]`: Rsync daemons are configured with "modules," which are essentially aliases for files/directorieson the server that are made available for synchronization. You can think of them as shares. If you omit the module, some servers might list the available modules.

- `[DESTINATION]`: This is the local path where you want to download the files to. If you want to save in the current directory then just mention the name with which you would like to save the file in the local machine.

### Authentication:

Rsync modules can be configured with varying levels of security:

- Anonymous: Some modules may be publicly accessible without any authentication.

- Password-protected: Many modules require a username and password. You may be prompted for a password, or you can store it in a file and use the `--password-file` option.

It often happens that rsync is misconfigured to permit anonymous login, which can be exploited by an attacker to get access to sensitive information stored on the remote machine.

TASK 1: What is the default port for rsync? 873TASK 2: How many TCP ports are open on the remote host?

TASK 3: What is the protocol version used by rsync on the remote machine?

## Get Adhishri Kothiyal’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

TASK 4: What is the most common command name on Linux to interact with rsync?

TASK 5: What credentials do you have to pass to rsync in order to use anonymous authentication?

- anonymous:anonymous,

- anonymous,

- None,

- rsync:rsync

TASK 6: What is the option to only list shares and files on rsync? (No need to include the leading — characters) list-onlySubmit Flag:

We will begin by scanning the remote host for any open ports and running services with a Nmap scan. We will be using the following flags for the scan:

```
nmap -p- --min-rate=1000 -sV {target_IP}
```

```
-p- : This flag scans for all TCP ports ranging from 0-65535
-sV : Attempts to determine the version of the service running on a port
--min-rate : This is used to specify the minimum number of packets that Nmap should
send per second; it speeds up the scan as the number goes higher
```

The scan shows that only port 873 is open. Moreover, Nmap informs us that the service running on this port is rsync.

Now we will try to connect and simply list all the available directories to an anonymous user. Reading through the manual page we can spot the option — list-only , which according to the definition is used to “list the files instead of copying them”. To interact with the machine we execute the following command:

```
rsync --list-only {target_IP}::
or
rsync {target_IP}::
```

Looking at the output, we can see that we can access a directory called public with the description Anonymous Share . It is a common practice to call shared directories just shares . Let’s go a step further and list the files inside the public share. The trailing slash on the module name is important; it signifies that you want to see the contents of the directory.

```
rsync --list-only {target_IP}::public/
or
rsync {target_IP}::public/
```

We notice a file called flag.txt inside the public share. Our last step would be to download/copy/sync the entire content of the `flag.txt` file to our local machine. To do that, we simply follow the general syntax by specifying the SRC as public/flag.txt and the DEST as flag.txt to transfer the file to our local machine.

```
rsync {target_IP}::[SRC] [DESTI]
rsync {target_IP}::public/flag.txt flag.txt
```

Executing this command returns no output. But, on our local directory we have a new file called flag.txt . Let’s read its contents : `cat flag.txt`

Congratulations! You have successfully captured the flag file from the remote machine using the rsync protocol.

And this marks an end to Tier -0 of [Starting Point](https://app.hackthebox.com/starting-point) machines in [Hack The Box Labs](https://app.hackthebox.com/home). Go Start Pwning Machines now… :) Happy Hacking!🪅

---
