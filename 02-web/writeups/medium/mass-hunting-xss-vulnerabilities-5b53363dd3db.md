# :globe_with_meridians: Mass Hunting XSS vulnerabilities by Ott3rly

> **Original Source:** [Mass Hunting XSS vulnerabilities by Ott3rly](https://infosecwriteups.com/mass-hunting-xss-vulnerabilities-5b53363dd3db)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Mass Hunting XSS vulnerabilities


In this article, I would like to cover how it is possible to efficiently check thousands of endpoints for potential Cross Site Scripting vulnerabilities in a short amount of time. The technique presented can be completely automated (although I do recommend some manual data filtering to save on server resources). This blueprint could be used to enhance your existing Bug Bounty automation setup. I will be using [Axiom](https://github.com/pry0cc/axiom) tool to help scale XSS hunting to the next level.


*Cross Site Scripting Hunting Results*


If you are not very familiar with Axiom tool, I will highly suggest you to follow [previous parts](https://ott3rly.medium.com/), since it has more in depth description about main features.

## Getting Target Subdomains


To find reflected XSS first, you will need to do proper homework. Subdomains could be collected using various bug bounty tools like **amass**, **subfinder** etc. Many tutorials already explain building a large list of subdomains, so I won’t expand it in this article. **I have covered how it’s possible to do it with help of axiom in **this article.


Also, I do recommend picking a large scope program which has a lot of apex domains. Companies with a lot of attack surface and with old infrastructure have higher probability to have Cross Site Scripting vulnerabilities. The Bug Bounty Game is about calculating where potential vulnerabilities could occur.


For this particular example, I will use [chaos](https://github.com/projectdiscovery/chaos-client) to gather the subdomains for **example.com**. You will need to configure the necessary API keys to use it.


```
chaos -silent -d example.com | tee hostnames.txt
```


*Subdomains from Chaos*


Now let’s check which of these hosts are alive. I will use Axiom to speed up this process. Firstly, we will need to spin up some instances:


```
axiom-fleet xss-hunt -i 8
```


*Initialize axiom fleet of 8 instances*


Next, I suggest editing the **httpx.json** module located at **~/.axiom/modules/** a little bit to scan more ports and give some extra information like status code and response title:


*httpx axiom module*


Now let’s run the axiom-scan command for the selected hosts:


```
axiom-scan hostnames.txt -m httpx | tee alive.txt
```


*Alive subdomains*

## Filtering Subdomains


It’s time to do some manual work in order to save some valuable cloud resources. The first task after collecting alive hosts is to filter them. There are a couple of ways to do it, and every bug hunter has its own approach. The multiple **grep** commands with some status code and title regex filtering will do a trick. Many hunters have certain blacklist words to filter out subdomains. For this particular example, I want to filter **blog**, **api** words from each line and select only subdomains which have **200** status code:


```
cat alive.txt | grep -vE "blog|api" | grep 200 | awk '{print $1}' > alive_selected.txt
```


## Collecting Endpoints


The endpoints for selected hosts could be collected multiple ways, depending on the tooling you want to select. I suggest combining multiple tools and merge results to one huge list. The more tools you use at this point, the more attack surface you will have against targets. In this post, I will show around 2 methods that could be used for this purpose.


## Get Ott3rly’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


**Method #1: Host crawling**


There are multiple unique tools for this purpose like **katana** or **paramspider**. For this tutorial, I will use the **katana** since it does not require a special setup. As far as I checked on the last axiom version, the **paramspider** was not installed correctly on the default provisioner. You need to install it manually on one of instances and make snapshot of it. Anyway, if you just decide simply use project discovery’s **katana** for host crawling, I suggest using this command with axiom:


```
axiom-scan alive_selected.txt -m katana -duc -silent -nc -jc -kf -fx -xhr -ef woff,css,png,svg,jpg,woff2,jpeg,gif,svg | tee -a katana.txt
```


**Method #2: Web archive data**


Gathering web archived endpoints could be helpful as well to form an endpoint list. There are multiple tools for this purpose like **waybackrobots**, **waybackurls**, **gau**, **gauplus** and etc. For this setup, I will utilize **gau**, since it is most advanced at the time. To unlock its full potential I want to modify **gau.json** axiom module as well located at **~/.axiom/modules/**:


*gau axiom module*


I have added some threads to speed up the process, included subdomain collection and blacklisted unnecessary extensions. For the scanning, since we will be using --**subs** flag, I suggest to use apex subdomains wordlist as in this example:

*Target wildcards*


Finally, you can execute the axiom scan with the gau module:


```
axiom-scan targets-wildcards.txt -m gau | tee -a gau.txt
```


*gau axiom module output*

## Preparing Gathered Endpoints for XSS checks


Collected lists will contain much data that requires processing. Last thing you want to pass gathered endpoints to next tool without any filtering. At first, I just recommend selecting only those URLs which already have parameters and sort unique endpoints. For this purpose, I like to use another tomnomnom’s tool — [qsreplace](https://github.com/tomnomnom/qsreplace):


```
cat gau.txt katana.txt | grep -aiE '^http' | grep -aiE '\?' | qsreplace FUZZ > fuzzable_urls.txt
```


Another thing that I like to do is to filter out some parameters and some static endpoints. It really depends on case by case. For example, I have used [gf](https://github.com/tomnomnom/gf) and filtered out some specific keywords using basic regex:


```
cat fuzzable_urls.txt | grep FUZZ | gf xss | grep -iavE 'pdf|txt|\?l=FUZZ$|\?contry=FUZZ$|\?q=FUZZ$|is/image' > filtered_fuzzable_urls.txt
```


## Scanning Cross Site Scripting vulnerabilities


Once you have a fuzz endpoint list available, you are ready to do some XSS hunting. I like to use [freq](https://github.com/takshal/freq) tool for this, which could be scaled with axiom as well. It is not yet included as an axiom module yet, so you might need to add this as a module yourself. I have already covered how you can achieve it in [this post](https://ott3rly.com/axiom-module-part-4/). Finally, you are ready to do some XSS fuzzing using axiom instances:


```
cat filtered_fuzzable_urls.txt | qsreplace "';a=prompt,a()//" > fuzz.tmp && axiom-scan fuzz.tmp -m freq | grep -v 'Not'
```


As you can see, I have used `';a=prompt,a()//` as the payloads for this case, since it does have capabilities bypassing some WAFs.

## Final Words


If you followed this guide carefully, you are ready to start hunting XSS on mass scale. Remember that you should add your own insights into this approach so you could stand out from the crowd. I think this could only give you some insights how mass hunting could be achieved.


If you have liked this story, smash that clap button 50 times and add your own insights in the comments down below. You could also subscribe to not miss any stories like this. I am active on [Twitter](https://ott3rly.com/twitter), check out some content I post there daily! If you are interested in video content, check my [YouTube](https://ott3rly.com/youtube). Also, if you want to reach me personally, you can visit my [Discord](https://ott3rly.com/discord) server. Cheers!

---

*Originally published on [Medium](https://infosecwriteups.com/mass-hunting-xss-vulnerabilities-5b53363dd3db). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
