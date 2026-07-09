import string

LOWERCASE_OFFSET = ord("a")
ALPHABET = string.ascii_lowercase[:16]

def b16_decode(enc):
	enc = [enc[i:i+2] for i in range(0, len(enc), 2)] # breaks string into pairs of letters
	plain = ""
	for pair in enc:
		n1 = "{0:04b}".format(ALPHABET.index(pair[0]))
		n2 = "{0:04b}".format(ALPHABET.index(pair[1]))
		binary = int(n1 + n2, 2)
		plain += chr(binary)
	return plain

def unshift(c, k):
	t1 = ord(c) - LOWERCASE_OFFSET
	t2 = ord(k) - LOWERCASE_OFFSET
	return ALPHABET[(t1 - t2) % len(ALPHABET)]

cipher = "mlnklfnknljflfjljnjijjmmjkmljnjhmhjgjnjjjmmkjjmijhmkjhjpmkmkmljkjijnjpmhmjjgjj"
for key in ALPHABET:
	assert all([k in ALPHABET for k in key])
	assert len(key) == 1
	decode = ""
	for i, c in enumerate(cipher):
		decode += unshift(c, key[i % len(key)])
	flag = b16_decode(decode)
	print(f"Key: {key}, Flag: {flag}")