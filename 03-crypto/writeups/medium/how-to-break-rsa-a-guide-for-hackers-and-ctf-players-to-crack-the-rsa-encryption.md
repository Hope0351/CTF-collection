# :locked_with_key: How to break RSA encryption algorithm

---

# Breaking RSA encryption algorithm: A step-by-step guide for Hackers and CTF players to crack RSA

In this article, you will learn how to crack RSA, which is one of the most widely used encryption algorithms in the modern world, as well as CTF challenges

*AI Generated*

Before moving on, it is recommended to have a good understanding of how RSA encryption works, which I explained in one of my previous articles

>

🎁Resources: At the end of this writeup I have share a useful resource to test your skill by putting the knowledge into practice

### Security of RSA

The security of RSA depends on the difficulty of factoring n into its prime components `p` and `q`. Factoring time grows with larger primes, so the selection of large prime numbers `p`& `q` in the RSA algorithm key generation process contributes to entropyEntropy means the randomness or unpredictability of data. High entropy means the data is highly random and difficult to predict. It increases the brute force time, which prevents attackers from easily predicting the prime numbers `p`& `q`

Here is the example Python script that demonstrates how factoring time grows with larger primes:

```
import time
from sympy.ntheory import factorint

# Small n (product of two small primes)
n_small = 253 # 11 × 23
start = time.time()
factorint(n_small)
print(f"Time to factor {n_small}: {time.time() - start:.6f} seconds")

# Medium n
n_medium = 988027 # 941 × 1051
start = time.time()
factorint(n_medium)
print(f"Time to factor {n_medium}: {time.time() - start:.6f} seconds")

# Large n
n_large = 2147483647 # A large prime
start = time.time()
factorint(n_large)
print(f"Time to factor {n_large}: {time.time() - start:.6f} seconds")
```

Output

*factor_time.py*

## Breaking the RSA

In this section, we are going to apply the technical expertise to crack the RSA. It is required to have access to some information in order to successfully break the algorithm. In this case, we have the following data:

```
Public Key(p) = 43941819371451617899582143885098799360907134939870946637129466519309346255747
Exponent(e) = 65537
Ciphertext(c) = 9002431156311360251224219512084136121048022631163334079215596223698721862766

```

♦️Task: Retrieve the private key exponent and recover the plaintext

Here is the step by step process to extract the private key and decrypt the encrypted text:

### 1️⃣ Factorize n

Since`n`is the product of two large primes `p` and `q`, the factorization of `n` can produce two primes `p` & `q`

## Get Huzaifa Malik’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

You can utilize [FactorDB](https://factordb.com/) (online tool) or following python script to factorize `n`:

```
from sympy import factorint
# Given values
n = 43941819371451617899582143885098799360907134939870946637129466519309346255747
# Factor n
factors = factorint(n)
p, q = factors.keys()
print("Prime factors:")
print("p =", p)
print("q =", q)
```

>

Note: It is recommended to use an online tool because it takes a long time to successfully factorize the local machine.

Input

```
n = 43941819371451617899582143885098799360907134939870946637129466519309346255747
```

*Factor DB (online tool)*Output

```
p = 205237461320000835821812139013267110933
q = 214102333408513040694153189550512987959
```

### 2️⃣Compute phi (φ)

As:

```
φ(n) = (p-1)*(q-1)
```

Use following python script to calculate the φ(n):

```
p = 205237461320000835821812139013267110933
q = 214102333408513040694153189550512987959
phi_n = (p - 1) * (q - 1)
print("Phi(n) =", phi_n)
```

*phi_n.py*Output

```
Phi(n) = 43941819371451617899582143885098799360487795145142432760613501190745566156856
```

### 3️⃣Finding the Private Key exponent (d)

As:

```
Private Key exponent(d) = modular inverse of (e mod φ(n) )
```

Command to install pycryptodome library

```
pip install pycryptodome --break-system-packages
```

Now, use following script to calculate the Private key exponent `d`

```
from Crypto.Util.number import inverse, long_to_bytes
phi_n = 43941819371451617899582143885098799360487795145142432760613501190745566156856
e = 65537
d = inverse(e, phi_n)

print("Private key exponent (d):", d)
```

*Private Key Exponent (d)*Output

```
Private key exponent (d): 42863673506531127160266519316271436658935017712647978759376543290403486562425
```

>

Private key exponent (d) obtained

### 4️⃣Decrypt ciphertext

Script to decrypt the ciphertext:

```
from Crypto.Util.number import inverse, long_to_bytes

# Given values
c = 9002431156311360251224219512084136121048022631163334079215596223698721862766
d = 42863673506531127160266519316271436658935017712647978759376543290403486562425
n = 43941819371451617899582143885098799360907134939870946637129466519309346255747
decrypted = pow(c, d, n)
plaintext = long_to_bytes(decrypted)
print(plaintext.decode())
print("Decrypted Plaintext:", plaintext)
```

*decrypt.py*

>

Cipher text decrypted successfully

---
