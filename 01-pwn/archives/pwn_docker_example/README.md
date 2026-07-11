# pwn_docker_example

Example pwnable CTF challenge hosted with Docker. This repo was used to run
a challenge in a server setup with Docker, and then use a Docker container
as the CTF OS to write and run the exploit.

## Why Docker for CTFs?

Docker gives every team an identical, isolated environment. The challenge
binary runs inside the container with a known libc, known kernel, and known
ASLR seed. This eliminates the "works on my machine" problem — if your
exploit works locally against the Docker image, it will work against the
remote challenge.

## Related: Docker fundamentals for CTF

Key concepts to understand before using Docker-hosted pwn challenges:

- **Namespaces** — Docker uses Linux namespaces (PID, network, mount, user)
  to isolate the container. Understanding namespaces is essential for
  container-escape challenges.
- **seccomp** — Docker's default seccomp profile blocks certain syscalls.
  Some pwn challenges require a syscall that seccomp blocks, which itself
  is part of the challenge.
- **OverlayFS** — Docker's storage driver. Exploits that corrupt filesystem
  state inside a container may be limited by the overlay layer.

## Folder contents

This directory contains the Dockerfile, the challenge binary, and a
reference exploit demonstrating the intended solve path.
