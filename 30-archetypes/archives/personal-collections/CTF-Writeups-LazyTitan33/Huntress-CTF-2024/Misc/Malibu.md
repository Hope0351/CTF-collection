# Red Phish Blue Phish



## My Solution

When we connect with curl on the provided service, we can see a `MinIO` server banner as well as other headers indicating an Amazon service:  



The `MinIO` is a service that can be used for S3 buckets:  



The word `bucket` would also match with the challenge title and the description. So when we try to access the `/bucket` endpoint we can see a list of items.



We use curl to redirect all the output to a file since it's quite large and then to make parsing easier I have [converted](https://jsonformatter.org/xml-to-json) the XML output to JSON:  



When we access one of the items in the bucket we can see a base64 blob:  



I've used `jq` to parse the json I saved locally and we see many random looking endpoints:  

```bash
cat bucketsid|jq -r '.ListBucketResult.Contents[].Key'
```



I saved all the endpoints to a file:  

```bash
cat bucketsid|jq -r '.ListBucketResult.Contents[].Key' > keys
```

Then I've used `sed` to add the URL to all the endpoints:  

```bash
sed -i 's/^/http:\/\/challenge.ctf.games:31887\/bucket\//g' keys
```



Then I used the following bash oneliner to curl all the endpoints and try to find the flag:  

```bash
while read line;do curl -s $line |grep flag;done <keys
```



`flag{800e6603e86fe0a68875d3335e0daf81}`
