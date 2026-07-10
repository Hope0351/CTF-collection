# :game_die: Ctf Write Up Rain D7473E9Ed46B

---

CTF Write-Up: Rain

- CTF challenge available at ctf-mystiko.com.

- Challenge name: Rain

- Category: Misc

— — — —

This challenge shows a very introductory lesson about Azure Active Directory and the Microsoft ecosystem. We start with a zip file. It can be cracked with rockyou:

*Cracking of the zip file*

Inside the zip file we have some credentials:

Please note that anything ending in .onmicrosoft.com belongs to some Azure tenant. The “on microsoft” stresses the fact that it’s an object stored on the Azure cloud, not in an on-prem datacenter. Hence we don’t see the usual .local as the toplevel domain.

Log in to

>

portal.azure.com

And use the credentials (make sure to replace the $ by an s in the username)

User03@dh0ckdomain1.onmicrosoft.com

y7U8r$@u3

## Get Antonio Lara’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

We login to Azure for this user, inside the dh0ckdomain1 domain.

*Azure portal after login*

When you login to Azure with your user, you will be inside a Tenant exclusive for you, and you will be the Global Administrator, to do what you want. However if you don’t own a subscription (not free) you cannot deploy VMs, apps, storage accounts, etc, you can only create a directory in Azure Active Directory (adding users, groups, etc).

Go to Azure Active Directory (red arrow in the picture above) and go to All users. Even if you are a user with no special permissions you can see all other users and groups in the tenant. In this case check User 02

Inside his profile we can see part of the flag:

Now check the groups:

The All Company group is there by default. Go inside and you could see who belongs to this group:

*Go to Yammer*

Now click on the Yammer link. Yammer is a social network by Microsoft. Log in with the credentals that you have and you will see a post with the second half of the flag:

*Second half of the flag.*

If you want to disable Multi factor authentication for a user (I did it on purpose for the challenge, since (according to the login page) after 14 days the MFA will be required) you need to disable it here in the panel (you need permissions to do it, not every user can):

*Doing this as the Global Administrator for the desired user will disable the need to user MFA at login time for that user*

---
