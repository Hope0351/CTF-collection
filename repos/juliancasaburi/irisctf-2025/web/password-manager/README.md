# Password Manager - Web
## Challenge Information
- **Category**: Web Exploitation
- **Description**: "It looks like skat finally remembered to use his password manager! One small problem though, he forgot his password to the password manager! Can you help him log back in so he can get back to his favorite RF forums?"

## Technical Overview
The challenge presents a web application written in Go that implements a password manager service. The application includes basic authentication mechanisms and file serving capabilities.

### Initial Analysis
1. **Frontend Interface**:
   - Simple login form requiring username and password
   - Static files served from a `/pages/` directory

2. **Source Code Review**:
   - Analysis of the provided `main.go` reveals:
     - Custom path sanitization implementation
     - File serving restricted to `/pages/` directory
     - Basic authentication mechanism

## Vulnerability Assessment
### Path Traversal Protection Analysis
The application implements path traversal protection through string replacement, but the implementation contains several flaws:

1. **String Sanitization Weaknesses**:
   - Simple string replacement of "../" patterns
   - No recursive sanitization
   - Lack of proper path normalization

## Exploitation
### Path Traversal Bypass
The vulnerability was successfully exploited using double forward slash technique:

1. **Payload Construction**:
   ```
   Original path: ../../
   Modified path: ....//....//
   ```

2. **File Access**:
   - Successfully accessed `users.json` outside restricted directory

### Credential Extraction
1. Retrieved credentials from users.json:

2. Authentication:
   - Successfully logged in using extracted credentials
   - Obtained flag upon authentication

## Automated Exploitation
The included `exploit.py` script automates the exploitation process:

1. **Requirements**:
   ```bash
   pip install pwntools requests
   ```

2. **Usage**:
   ```bash
   python3 exploit.py
   ```

The script will:
- Perform path traversal to retrieve users.json
- Extract credentials
- Authenticate to the service
- Retrieve stored passwords

## Security Implications
This challenge highlights common vulnerabilities in path traversal protection:
1. Reliance on simple string replacement
2. Lack of proper path normalization
3. Insufficient input validation

## Mitigation Strategies
To prevent such vulnerabilities:
1. Use built-in path sanitization libraries
2. Implement proper path normalization
3. Use allowlist approaches for file access
4. Implement proper access controls

## Flag
```
irisctf{l00k5_l1k3_w3_h4v3_70_t34ch_sk47_h0w_70_r3m3mb3r_s7uff}
```

![Challenge Solved](../../images/challenge-solved.jpeg)