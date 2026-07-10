# :sleuth_or_spy: OSINT Information Gathering with Informer

---

Before you start, You can join our discord server to engage with like minded people and share everything that you can share with people to help them and get your queries answered by people.

Informer is OSINT based information gathering tool made with python programming language. It has reach features like whois information gathering, geo-location information gathering, DNS information gathering, sub-domain information gathering, and shodan information gathering abilities.

>

GitHub Link : [https://github.com/sudo0x18/informer](https://github.com/sudo0x18/informer)

## 1. Download and Setup

For downloading and installation you must have git and python installed on your device. Clone the repository with git into your computer device and install all requirements.

```
#Clone repo
git clone [https://github.com/sudo0x18/informer.git](https://github.com/sudo0x18/informer.git)#Move into directory
cd informer#Install requirements
pip install -r requirements.txt
```

## 2. Usage and Menu

Usage and available option in every tool are very important to understand. Let’s look at them very quickly.

```
*python3 informer.py --help*Options:
-h, --help Show this help message and exit
-t TARGET, --targetTARGET Target domain name.
-d , --dns Get DNS Information
-g , --geolocation Get Geolocation Information.
-s , --shodan Get Shodan Information.
-sd, --subdomain Get Subdomain Information.
-o OUTPUT, --output OUTPUT Save output to the desired file.
```

## Get Jay Vadhaiya’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

## 3. Whois info and DNS info gathering

Informer makes whois information and DNS information gathering very fast and in a very easy way. We just need o to provide a valid domain name and specify valid flags to get the desired results.

```
*python3 informer.py -t google.com -d*# -t : Specify the target domain
# -d : Tells informer to fetch DNS info
```

## 4. Sub-Domain Information gathering

Gathering sub-domain information is very important in web application pen-testing. *Informer* makes this thing very easy and fasts effectively. You can gather sub-domain info as below.

```
*python3 informer.py -t example.com -sd*#-sd : Tells informer for sub-domain info gathering
```

## 5. Other options and their usage

The informer also provides location information gathering, shodan info, and saving the output to a file. It will automatically store shodan info in a file called shodan_<domain>.json with a pretty much indentation.

```
*python3 informer.py -t example.com -g -s -o filename.txt*# -g : For geo-location info gathering
# -s : For shodan info gathering
# -o : To store the output in a file
```

---
