# [Collaborative Development](https://play.picoctf.org/practice/challenge/410)

## Overview

**Category**: [General Skills](../)

**Difficulty**: Easy

**Event**: picoCTF 2024

## Description

My team has been working very hard on new features for our flag printing program! I wonder how they'll work together?
You can download the challenge files here:
- [challenge.zip](https://artifacts.picoctf.net/c_titan/71/challenge.zip)

## Hints

1. `git branch -a` will let you see available branches
2. How can file 'diffs' be brought to the main branch? Don't forget to `git config`!
3. Merge conflicts can be tricky! Try a text editor like nano, emacs, or vim.

## Solution

Use `git checkout <branch_name>` to switch to the different branches. Parts of the flag are in different branches.  

You can either manually put the flag together, or use `git merge <branch_name>` in the main branch to merge the branches into the main branch. 

Use `nano` or any other text editor to resolve the merge conflicts. Remember to add and commit the changes after resolving the conflicts.

## Flag

`picoCTF{t3@mw0rk_m@k3s_th3_dr3@m_w0rk_4c24302f}`
