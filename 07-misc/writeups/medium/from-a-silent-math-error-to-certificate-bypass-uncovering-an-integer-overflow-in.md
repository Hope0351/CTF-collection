# :game_die: From A Silent Math Error To Certificate Bypass Uncovering An Integer Overflow In

---

## 1. The Background: Understanding VLQs and ASN.1 DER

To understand the vulnerability, we first need to look at how X.509 certificates store large numbers, like Tags and OIDs. They use an encoding format called Variable-Length Quantity (VLQ) in ASN.1 DER.

In this Base-128 format:

- The data is processed byte by byte.

- The Most Significant Bit (MSB) of each byte is a flag:

- `1` means "more bytes are coming."

- `0` means "this is the final byte."

- The remaining 7 bits of each byte hold the actual data, which are shifted and added together to form the final large integer.

## 2. The Vulnerability: The Silent Overflow

While reviewing the library’s `DerReader` component, I found the function responsible for decoding these VLQ integers. The code looked exactly like this:

```
private fun readVariableLengthLong(): Long {
// A developer comment here literally said: "TODO: detect overflow." 🚩
var result = 0L
while (true) {
val byteN = source.readByte().toLong() and 0xff
if ((byteN and 0b1000_0000L) == 0b1000_0000L) { // If continuation bit is 1
result = (result + (byteN and 0b0111_1111)) shl 7 // Shift left by 7
} else {
return result + byteN
}
}
}
```

The Logical Flaw:

The `result` variable is a 64-bit signed `Long`. The `while` loop continuously shifts bits to the left (`shl 7`) as long as the continuation bit is set. There is absolutely no boundary or size validation.

If an attacker feeds the parser a malicious sequence of 11 bytes (10 continuation bytes + 1 final byte), the parser performs 70 bits of left shifts ($10 \times 7 = 70$). Because the container is only 64 bits wide, the most significant bits simply “fall off” the edge of the register and disappear.

The program doesn’t crash; it silently truncates the massive number into a tiny, incorrect value.

## 3. The Exploitation: Crafting the Payload

To prove this, I built a local test harness linked directly to the target library’s source files. I crafted a payload designed to perfectly overflow the register and leave behind a specific value: `1`.

The Malicious Byte Array (Hex):

## Get Hacker MD’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

`0x1F, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x01, 0x00`

- `0x1F`: Extended Tag marker to trigger the `readVariableLengthLong` function.

- `0x81...0x01`: The 11-byte VLQ representing a massive 77-bit logical integer.

- `0x00`: Dummy length byte.

The Result:

When I executed the parser against this payload, it effortlessly processed the 77-bit number and outputted:

`Resulting Tag Value: 1`

I had successfully forced a massive identifier to masquerade as the number `1`.

## 4. The Security Impact: OID Spoofing

Why does a mathematical truncation matter? Because this parser is the gatekeeper for TLS trust.

During a TLS handshake, the library parses X.509 certificates and relies on OIDs to identify critical elements, such as the Signature Algorithm or Root CA identifiers.

By utilizing this overflow, an attacker can engineer a rogue certificate with a “Massive OID.” When parsed, the library silently truncates this massive OID into a smaller value. If the attacker crafts the payload so that the truncated value matches the internal ID of a Trusted Standard OID, the library will process the malicious certificate as “Valid.”

This creates a logic bypass, opening the door to certificate spoofing and Man-in-the-Middle (MitM) attacks.

## 5. The Remediation

The fix is straightforward. I proposed adding a boundary check *before* the bitwise shift occurs to ensure the 64-bit limit isn’t breached:

```
if (result > (Long.MAX_VALUE ushr 7)) {
throw ProtocolException("Variable length long overflow")
}
result = (result + bits) shl 7
```

With this patch, the parser immediately detects the malicious input and throws a fatal exception, closing the connection instead of processing corrupted trust data.

---
