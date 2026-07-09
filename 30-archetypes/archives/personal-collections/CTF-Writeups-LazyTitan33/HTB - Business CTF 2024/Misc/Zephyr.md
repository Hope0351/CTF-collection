### Challenge Description

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Enumeration

This challenge gives us a `database.rs` file, a `source.rs` file and a `.git` repo:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Nothing interesting was visible in the two rust file, but we can start enumerating the repo by checking the log first:

```bash
git log --all --graph --decorate
```

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can see a `main` branch and a `w4rri0r-changes` branch. Doing a `git show` on the commit from the `w4rri0r-changes`, we find the first part of the flag.

```bash
git show bfa416eaeaff63de8f5118be829f669ffd0cc6a7
```

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can see in the second commit that they removed some sensitive information:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```bash
git show 1501091a639e565d40a2b3b20df3227e86d72a0e
```

Specifically, they changed the `database.rs` file:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

So in this case, if we want to have a look at the database.rs as it was before removing the sensitive content, we can use `git checkout` one commit prior. In this case, the initial commit.

```bash
git checkout ae4f456dcfe1e989ce13ca25231ac5df2fc4380d
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Now we load the datatabase in sqlite3 and get the second part of the flag.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And lastly, we can do a git show on the latest commit which seems to be just a stash, and we get the 3rd part of the flag:

```bash
git show a38932590c3265c1c2e0160a70e449ecfb39d3e2
```

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution

Putting it all together and we have our final flag:  

`HTB{g0t_tH3_p4s5_gOT_thE_DB_g0T_TH3_sT4sH}`
