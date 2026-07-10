# :game_die: Day 12 Blind Sql Injection With Conditional Errors Zero To Hero Blind Injection 

---

>

But wait a minute, we tried `' and 1=2`, which is clearly a false condition (because, yeah, 1 is never equal to 2, not even in developer dreams). Yet, we still got a 200 OK response! No error, no change, no sign of rejection.

This is where things get tricky. When both true (`' and 1=1`) and false (`' and 1=2`) conditions return the same response, we can't rely on visual cues or error messages. Welcome to the world of Blind SQL Injection — where the injection is happening, but the app acts like nothing’s wrong. It's like trying to read a poker face... in the dark!

---
