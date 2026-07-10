# :electric_plug: Testing SQL Injection Using Google gemma4:31b-cloud on PortSwigger’s Vulnerable Shop

---

# Testing SQL Injection Using Google gemma4:31b-cloud on PortSwigger’s Vulnerable Shop

AI-assisted SQL Injection testing against a deliberately vulnerable e-commerce application.

🔓 [Free Link](https://bashoverflow.com/ef9dc05dd1aa?sk=5c26d628b2622cb7a14d6e14cf91f111)

*SQL Injection Using Google gemma4:31b-cloud*

## Table of Contents

- Overview

- Proof of Concept (PoC)

## Overview

SQL Injection (SQLi) remains one of the most impactful web application vulnerabilities because it allows attackers to manipulate backend database queries through unsanitized user input. In this lab, the testing environment uses the intentionally vulnerable website **ginandjuice.shop**, a training platform developed by PortSwigger specifically for practicing modern web exploitation techniques in a controlled environment.

The application simulates a realistic e-commerce platform containing multiple attack surfaces commonly found in production systems. One of the vulnerable components exposed in this lab is the **Accessories** product category, where user-controlled parameters are processed insecurely within SQL queries. This behavior creates an opportunity to test and validate SQL Injection techniques against the backend database logic.

Unlike conventional manual testing workflows, this assessment leverages **Ollama** integrated with the **Google gemma4:31b-cloud**…

---
