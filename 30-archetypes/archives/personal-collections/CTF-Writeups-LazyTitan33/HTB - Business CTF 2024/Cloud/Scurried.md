### Challenge Description

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution

The challenge provides a simple text file with what looks to be an AWS IAM role id: `AROAXYAFLIG2BLQFIIP34`. A bit of research led us to [this](https://hackingthe.cloud/aws/enumeration/enumerate_principal_arn_from_unique_id/) helpful article.

From our own AWS portal, we go to IAM role and create a custom trust policy in which we set the principal AWS to the provided role id.  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can save this with whatever name we want. Then we access the role and look at the Trust Relationships. We will see that the `arn` we need was populated:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{arn:aws:iam::532587168180:role/vault101}`
