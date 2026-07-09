
import json

ccc = open("status.json").read()
jj=json.loads(ccc)

revoked = list(jj['entries'].keys())


with open("src/revoked.rs", "w") as fp:
    fp.write('\n\npub static REVOKED: &[u128] = &[\n')
    for s in revoked:
        val = int(s, 16) if any(c in s for c in "abcdefABCDEF") else int(s)
        fp.write(f'    {val},\n')
    fp.write('];\n\n')


