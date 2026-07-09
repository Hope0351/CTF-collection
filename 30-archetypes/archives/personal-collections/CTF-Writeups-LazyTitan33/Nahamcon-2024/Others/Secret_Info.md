## Secret Info

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Enumeration

For this challenge, I built the docker using the provided source code. I logged into the administration panel to see where the file is located. Within the docker, the file was accessible publicly from:  

`/wp-content/uploads/2024/05/flag_secret_not_so_random_get_me_1337.png`

## Solution

Turns out that the same is valid for the challenge instance as well.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`CTF{it_is_a_feature_by_core_xd}`

Note: I didn't understand the point of this challenge. It felt lazy and a missed opportunity to do something with a potentially cool wordpress plugin.
