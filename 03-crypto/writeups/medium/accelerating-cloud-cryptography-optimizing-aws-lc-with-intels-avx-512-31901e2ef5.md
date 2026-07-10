# :locked_with_key: ​​Accelerating Cloud Cryptography: Optimizing AWS-LC with Intel’s AVX-512

> **Original Source:** [​​Accelerating Cloud Cryptography: Optimizing AWS-LC with Intel’s AVX-512](https://infosecwriteups.com/accelerating-cloud-cryptography-optimizing-aws-lc-with-intels-avx-512-31901e2ef566)
> **Platform:** infosecwriteups.com | **Category:** `CRYPTO`

---

# ​​Accelerating Cloud Cryptography: Optimizing AWS-LC with Intel’s AVX-512


Learn how AVX-512 optimization in AWS-LC delivers faster, more efficient cloud cryptography for modern data security needs


*source: author*

## Background and Motivation


With the rapid expansion of cloud computing, the importance of efficient and high-performance cryptography has grown substantially. Encryption is essential for safeguarding data both in transit and at rest, but at cloud scale, strong cryptographic protections can introduce significant computational demands. These demands may impact system performance, increase operational costs, and influence the overall user experience.


Given these challenges, the choice of cryptographic library is becoming increasingly important for cloud providers and application developers. OpenSSL has long been the industry standard, but its large and complex codebase can make it difficult to maintain, optimize, and audit effectively. In contrast, AWS-LC is designed with a leaner, security-focused approach, making it easier to use correctly and more suitable for targeted performance improvements. Its streamlined design, combined with growing support from AWS and the open-source community, has led to rapid adoption, especially in environments where both security and efficiency are critical.


In this context, optimizing the Advanced Encryption Standard (AES) implementations within AWS-LC emerged as a key priority. By fully utilizing the capabilities of Intel’s AVX-512 instruction set, which is available on modern Xeon processors, it became possible to achieve much greater parallelism and acceleration. These enhancements were implemented with the goal of maximizing encryption throughput, reducing CPU utilization, and delivering measurable performance improvements for a wide range of real-world cloud workloads and applications.

## Why AVX-512?


AVX-512 represents Intel’s most advanced Single Instruction, Multiple Data (SIMD) extension, allowing modern CPUs to process 512 bits of data in a single instruction. This capability is particularly impactful in the field of cryptography, where it enables the simultaneous encryption or authentication of multiple data blocks, significantly increasing overall throughput. Prior to our collaboration, the AES implementations within AWS-LC were not fully leveraging the potential of AVX-512. As a result, much of the available parallel processing power in contemporary Xeon processors remained underutilized, with substantial performance improvements yet to be realized.

## AES-GCM Optimization with AVX-512


### Why AES-GCM Optimization Matters for Cloud Performance?


AES-GCM (Galois/Counter Mode) is a widely adopted encryption standard for securing data in transit and at rest, especially in cloud environments. Its combination of confidentiality and integrity makes it a default choice for protocols like TLS and for encrypting cloud storage. However, at scale, the computational intensity of both encryption and authentication can become a bottleneck, impacting system throughput and increasing operational costs. Optimizing AES-GCM is therefore critical for enabling secure, high-speed data processing in modern cloud infrastructure.

### How AVX-512 Improves AES-GCM


A new AVX-512 code path was introduced for AES-GCM, leveraging two key Intel instructions:


vAES: Accelerates AES block encryption.
vPCLMULQDQ: Accelerates GHASH authentication (polynomial multiplication in GF(2¹²⁸).


The implementation processes multiple blocks in parallel by:


- Interleaving Data: Organizing blocks across 512-bit AVX-512 registers.

- Loop Unrolling: Reducing loop control overhead for large buffers.

- Vectorization: Applying AES rounds and GHASH operations to all blocks simultaneously.


Pseudocode


```
# N = AVX-512 register capacity (8/16 blocks)
for i in range(0, len(plaintext), N):
# Load N plaintext blocks into AVX-512 registers
blocks = avx512_load(plaintext[i:i+N])
# Encrypt all N blocks in parallel (vAES)
encrypted_blocks = aes_encrypt_parallel(blocks, round_keys)
# Authenticate all N blocks in parallel (vPCLMULQDQ)
ghash_accumulate_parallel(encrypted_blocks, hash_key)
# Store results
avx512_store(ciphertext[i:i+N], encrypted_blocks)
```


## Comparison with Prior Implementation


The transition from legacy SIMD approaches (such as AVX2 and SSE) to AVX-512 brings significant advances in how AES-GCM handles encryption and authentication at scale. The following table highlights the key differences between the previous and optimized implementations:


```
Aspect Legacy Approach AVX-512 Optimization
Parallelism 1–4 blocks 8–16 blocks
Loop Overhead High Reduced by ~75%
CPU Utilization Partial Full utilization
GHASH Throughput Sequential All blocks simultaneously
```


Performance Impact


*source: author*

## Key Insights


Parallelism is transformative: AVX-512’s 512-bit registers allow 8–16 AES blocks to be encrypted and authenticated in a single operation, dramatically reducing per-block overhead.


ISA alignment matters: Legacy code mixed scalar and SIMD operations, causing pipeline stalls. The AVX-512 path is optimized for sustained vector throughput.


## Get Shireesh Kumar Singh’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


By aligning AES-GCM with modern hardware capabilities, this optimization ensures cloud workloads can scale securely without compromising performance.


For more technical details and implementation specifics, please refer to the corresponding Pull Request:[PR #692](https://github.com/aws/aws-lc/pull/692).

## AES-XTS Optimization with AVX-512


### Why AES-XTS Optimization Matters for Cloud Performance?


AES-XTS (XEX-based Tweaked CodeBook Mode with Ciphertext Stealing) is widely recognized as the standard for encrypting storage devices such as disks and databases. By introducing a unique tweak for each data block, AES-XTS ensures that identical plaintext blocks are encrypted into distinct ciphertexts, effectively protecting against pattern-based attacks. However, as the volume of data grows — especially in multi-terabyte cloud environments — the computational demands of AES-XTS can place significant strain on CPU resources. Optimizing this encryption mode is therefore crucial for achieving fast, scalable, and secure disk encryption in modern cloud infrastructure.

### How AVX-512 Improves AES-XTS


A dedicated AVX-512 code path was introduced for AES-XTS, leveraging:


vAES: Parallel AES block encryption.
Vectorized XOR: Simultaneous tweak application across multiple blocks.


The implementation processes disk sectors in parallel by:


- Parallel Tweak Computation: Generating tweaks for multiple blocks at once.

- Interleaved Encryption: Applying AES and XOR operations across all blocks in a single pass.

- Runtime Dispatch: Automatically selecting the optimal code path (AVX-512 or legacy) based on CPU support.


Pseudocode


```
# N = AVX-512 register capacity (8/16 blocks)
for i in range(0, len(data), N):
// Compute N tweaks in parallel
tweaks = compute_tweaks_parallel(initial_tweak, i, N)
// Encrypt N blocks in parallel (tweak pre/post-XOR and AES)
encrypted_blocks = aes_encrypt_parallel(data[i:i+N] ⊕ tweaks, key) ⊕ tweaks
// Store results
store(ciphertext[i:i+N], encrypted_blocks)
```


## Comparison with Prior Implementation


The shift from legacy scalar and AVX2 approaches to AVX-512 brings major efficiency gains to AES-XTS encryption. With AVX-512, both tweak computation and encryption are parallelized across many blocks, dramatically reducing loop overhead and maximizing throughput. This enables AES-XTS to deliver fast, scalable disk encryption ideally suited for modern cloud storage environments


```
Aspect | Legacy Approach (Scalar/AVX2) | AVX-512 Optimization
-----------------------|-----------------------------------|-----------------------
Tweak Computation | Sequential (per block) | Parallel (all blocks in group)
Encryption | 1–4 blocks per iteration | 8–16 blocks per iteration
Loop Efficiency | High overhead for large buffers | ~80% fewer iterations
Throughput | Limited by serial tweak generation| Maximized via parallel tweak + AES
```


Performance Impact


*source: author*

## Key Insights


Parallel tweaks eliminate bottlenecks: Generating tweaks in parallel removes a critical sequential dependency, enabling full utilization of AVX-512’s vector units.


Memory alignment matters: Aligning data to 64-byte boundaries ensures optimal AVX-512 load/store performance.


By rethinking AES-XTS’s pipeline for parallelism, this optimization ensures disk encryption no longer limits I/O performance in high-throughput cloud storage systems.


For implementation details, see the corresponding Pull Request: [PR #1004](https://github.com/aws/aws-lc/pull/1004).Conclusion
The AVX-512 optimization for AES-XTS in AWS-LC delivers substantial performance improvements, especially for large-scale disk encryption workloads. By enabling parallel computation of tweaks and simultaneous encryption of multiple blocks, this enhancement fully utilizes the capabilities of modern processors and significantly reduces CPU overhead. The resulting speedups, which approach a fourfold increase for bulk data, demonstrate how effective software optimization can unlock the true potential of advanced hardware features. This ensures that strong encryption remains both efficient and scalable in today’s demanding cloud environments.


Legal & Licensing
All of the optimizations and results described in this article stem from our contributions to the AWS-LC cryptography library through Pull Requests [#692](https://github.com/aws/aws-lc/pull/692)and [#1004](https://github.com/aws/aws-lc/pull/1004). These enhancements were developed during my time at Intel, as part of a collaborative project with AWS. The code and performance data referenced are fully open source under the Apache License 2.0, and all information presented here is public and reproducible; no proprietary or internal material is included.

### References


[https://builders.intel.com/docs/networkbuilders/advanced-encryption-standard-galois-counter-mode-optimized-ghash-function-technology-guide-1693300747.pdf](https://builders.intel.com/docs/networkbuilders/advanced-encryption-standard-galois-counter-mode-optimized-ghash-function-technology-guide-1693300747.pdf)


[https://aws.amazon.com/blogs/big-data/save-big-on-opensearch-unleashing-intel-avx-512-for-binary-vector-performance/](https://aws.amazon.com/blogs/big-data/save-big-on-opensearch-unleashing-intel-avx-512-for-binary-vector-performance/)

---

*Originally published on [Medium](https://infosecwriteups.com/accelerating-cloud-cryptography-optimizing-aws-lc-with-intels-avx-512-31901e2ef566). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
