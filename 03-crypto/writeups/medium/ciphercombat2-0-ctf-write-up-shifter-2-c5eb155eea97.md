# :locked_with_key: Ciphercombat2 0 Ctf Write Up Shifter 2 C5Eb155Eea97

---

### 3rd Block

Now this looks like

>

Initialize a var > do something > add 1 to it> check if var =>0xf i.e (15)base > repeat

Looks familiar? loops something with increasing variable?

It’s nothing but a for()/while() loop implementation which iterates for 15 times, same as our character array length.

so let’s define it as for(int i=1;i≤15;i++){ loop body }

also, at the end of loop body it compares something and if it fails it shows “Better Luck next time” and then exit.

Other wise it completes the loop and exit with “c0ngrats!” message

### The loop body

The loop body is pretty interesting, it might look intimidating to new reverse engineer but it’s really simple.With some experience, you can already tell what it’s doing.

Let’s have a look at it.

now as we know it’s a loop and *var_4h is our control variable let’s call it “i”. *First we load the value of i in EAX, then we load the address of rax*8 to RDX, and then move our ARGUMENT(var_60h) into RAX. Then we do logical and RAX,RDX and mov Quad Word value at address of RAX to RAX, now we Move with Zero extended (movzx) byte value of RAX to …… ahhhhh… i am pretty sure this does not make it easier for you to understand it, all i am doing is dictating the instructions one by one…

>

Know this : Look at it, remember the pattern and know that it is one of the methods compilers implement fetching an element at some given index

You can ofcourse take some values yourself and try this but the full explaination is out of scope for this writeup, also it will make it boring and long enough.

*Some important instruction reference (links):*

[Convert Doubleword to Quadword (CDQE)](https://www.felixcloutier.com/x86/cbw:cwde:cdqe)

[Move with Zero-Extend (MOVZX)](https://www.felixcloutier.com/x86/movzx)

[Move with Sign-Extension (MOVSX)](https://www.felixcloutier.com/x86/movsx:movsxd)

Okay so what it actually did? Lemme explain:

- Take value at [i-1] index from our argument =argv[i-1] let’s say = arg

- Take value at [i-1] index from our character array = charp[i-1]

- Add i to our charp = charp[i-1]+i

- Add 1 to Step3 = charp[i-1]+i+1 , let’s say = charpnew

- Compare arg == charpnew.

These instructions are responsible for step 3 and 4, remember we stored our i in EAX ? and then we add EAX (i.e. i )to ECX, our element which is stored in EAX and then again add 1 to new EAX.

and now converting it to code we have :

*Code reversed from Assembly Graph*

Now instead of checking the flag we can print it !!

Here’s is relatively clean Python Implementation of above algorithm, Running it spits out the flag.

And we got the flag HE{shift3r_returns} we can also check it with the C++ program we reconstructed.

---
