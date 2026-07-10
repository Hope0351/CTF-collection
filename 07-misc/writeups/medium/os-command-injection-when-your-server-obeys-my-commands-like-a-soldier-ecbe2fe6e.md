# :game_die: Medium

---

# 🧨 OS Command Injection — When Your Server Obeys My Commands Like a Soldier

## You were just thinking “ping”? I was already thinking “root access.”

### 🎬 Introduction

*The interface looked harmless.
Just a simple page to convert an image from one format to another.
Practical. Intuitive.*

*I drag in a test photo.
I type “png” as the output format. All good.
Then, just to see, I replace “png” with: *`*png; whoami*`*. And I click “Convert.”
A few seconds later, my screen displays… the username of the server.*

*This was the case for a feature I encountered during a penetration test.
Since I didn’t have permission to exploit it on the real application,
I decided to recreate the exact same scenario in a homemade web application.*

*That day, I realized this image converter wasn’t just a design tool.
It was an entry point. A remote execution vector.
A terminal access point cleverly disguised.*

Let’s see how a simple image conversion feature, designed to make life easier for users, can turn into a **powerful vector**…

---
