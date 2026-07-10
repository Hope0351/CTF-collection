# :game_die: Critical Blind SQL Injection leads to $4,134 (7/30 DAYS)

---

# Critical Blind SQL Injection leads to $4,134 (7/30 DAYS)

Understanding the Risk: How a Blind SQL Injection Was Discovered in inDrive

## Hi Bug Bounty Hunters!!!

I’m a security researcher, and I’ve taken on the challenge of explaining one bug bounty report every day for the next 30 days — 30 reports!

The goal is to make these reports easy to understand, share the cool stuff I learn along the way, and inspire others to dive into the world of bug bounties too. Whether you’re a pro or just curious, I hope you’ll find something interesting in this series.

I’ll also share useful tips at the end of each report to help you level up your bug-hunting game. Let’s get started!

Today’s Report: Blind SQL Injection Vulnerability in inDrive API

## Introduction

Security researcher identified a significant security flaw in inDrive’s API. The vulnerability was a blind SQL injection, which allowed attackers to manipulate database queries and extract sensitive information. This report highlights how the vulnerability was discovered, how it could be exploited, and why it was a serious security risk.

## What Is Blind SQL Injection?

---
