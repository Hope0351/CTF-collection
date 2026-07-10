# :game_die: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/bac-improper-authorization-in-public-facebook-groups-5345a7f49173)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# [BAC] Improper Authorization in Public Facebook Groups Allows Moderators to Change “Who Can Participate” Setting


## Storytelling Write-up


While testing access control mechanisms in Facebook Groups, I started with a simple assumption: each role should have clearly defined permissions. In this case, **moderators are not supposed to modify sensitive group settings**, especially options like *“Who can participate in the group.”*


To validate this, I first attempted to access the group settings page directly as a moderator:


```
https://web.facebook.com/groups/GROUP_ID/edit
```


As expected, I was redirected to an error page. This confirmed that, at the UI level, only admins are allowed to access and modify these settings.


However, I decided to dig deeper.


To understand how the setting is actually updated, I created another group where I had **admin privileges**. While changing the *“Who can participate in the group”* option (e.g., *Profiles and Pages* ↔ *Only Profiles*), I intercepted the request sent to the server.


This request was handled via a GraphQL mutation:


```
useGroupEditPageJoinPermissionMutation
```


At this point, I attempted to replicate the same request — but under a different context:


- Using a **moderator account**

- Replacing the `group_id` parameter with the ID of a target group where I was only a moderator


After sending the modified request, the result was unexpected:

>

*The server responded with 200 OK, and the change was successfully applied.*


This indicates that **the backend failed to properly validate the user’s role**, allowing a moderator to perform an action that should be restricted to admins only.

## Impact


This issue affects **public Facebook groups** and leads to the following risks:


- Moderators can change the **“Who can participate in the group”** setting without admin approval

- The setting can be switched between:

- *Profiles and Pages*

- *Only Profiles*

- Violates **role-based access control (RBAC)** principles

- Undermines admin authority over group configuration

- May be abused to:

- Alter participation rules without consent

- Disrupt group interaction dynamics


Even though the group is public, this setting remains a **sensitive administrative control** and should not be accessible to moderators.

## Reproduction Steps


**Users:**


- User A (Admin)

- User B (Moderator)


**Steps:**


## Get Abu Idris Al-Muhaqqiq’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


1. User A creates Group C (Public Group)
2. User B joins Group C
3. User A assigns User B as a Moderator
4. User B attempts to access:


*/groups/GROUP_C_ID/edit*


→ Redirected to an error page (expected behavior)


6. User B creates Group D (where they are Admin)
7. User B changes the “***Who can participate in the group***” setting in Group D while intercepting the request
8. Capture the GraphQL request (***useGroupEditPageJoinPermissionMutation***)
9. Modify the parameter:


*“group_id”:”GROUP_D_ID”*


→ Replace with:


*“group_id”:”GROUP_C_ID”*


10. Resend the request
11. Server responds with *200 OK*
12. The setting in Group C is successfully updated (verified by User A)

## Root Cause


- Missing authorization checks on the backend

- Sensitive operations rely only on frontend/UI restrictions

- The GraphQL endpoint does not validate whether the actor has admin privileges

## Timeline


December 27, 2025: Submit Report
December 28, 2025: Initial Evaluation
January 29, 2026: Unable to reproduce
January 29, 2026: More information sent
January 30, 2026: Triaged
March 26, 2026: Fixed
March 26, 2026: Fix Confirmed
March 28, 2026: Bounty Awarded + Bonus

---

*Originally published on [Medium](https://infosecwriteups.com/bac-improper-authorization-in-public-facebook-groups-5345a7f49173). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
