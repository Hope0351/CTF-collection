# :globe_with_meridians: Attack Surface Monitoring using Open-Source Intelligence

---

# Attack Surface Monitoring using Open-Source Intelligence

The paper introduces the case study for attack surface analysis and monitoring with practical application of open-source intelligence (OSINT) methods. The case is based on the perimeters of healthcare organizations and aims to introduce the threat landscape of healthcare industry as well as methods to collect information about entry points and assets on network perimeter. Techniques and tools in this paper are not limited by organization type and can be applied for different network assets to prepare initial information during first stage of penetration testing and red team operations.

## Introduction: Trying to Find All Open Doors

In my previous publications (“Unknown Attacks: Detect and Rate“, “The Phenomena of Targeted Attacks“), I described the key stages of the targeted attacks (so-called ‘kill-chain’). The first stage is called the ‘reconnaissance’ stage, which has to be carried out long in advance before the attacker will reach the first computer of the victim. The overall amount and the quality of the data collected on this stage define the level of success and, which is the most important the final cost of the attack.

One can use different exploits to reach vulnerable services located in the perimeter of the network (e.g. allowing the victim to find you and your exploits in the logs of the security system). At the same time, one can rely on the spear phishing technique to get access to one of the working stations within the perimeter of the company. It’s still to achieve the result in both cases; however, the overall price of their implementation will be totally different.

The intelligence stage is the key element required to define Tactics, Techniques, and Procedures (hereinafter referred to as TTPs), which are going to be the main elements required to reach the goal. However, in the majority of cases these days, the key task of the intelligence stage is the following: to find as much potential entry points to reach the goal as possible, and evaluate the overall implementation cost of the discovered vectors. To make the work of attackers more difficult and decrease the quality of their intelligence efforts, one needs to understand the list of TTPs they are going to use on the current stage.

The number of entry points of the corporate network defines the number of attack vectors available for the mischievous person. One can formally divide entry points into the following groups:

- information systems located on the perimeter of the network and having access to the Internet (servers, working stations, administrative control panels of special equipment and so on).

- mobile devices of the employees used as within the perimeter, as well as out of its borders.

- accounts of the cloud platforms and services used by the employees (including the personal one).

The last item requires some direct interaction of the attacker and the victim (e.g. by sending a fishing link to the victim), which significantly increases the chance to be identified. As a result, in some cases, attackers prefer to use available points of entry, which are located on the perimeter and can be easily exploited.

The network perimeter is a term that fades away as a result of the rapid development of modern technologies and wide implementation of cloud services. Such concepts as “Bring your own device” (BYOD) that allows the employees bringing their own devices to reach all business processes, as well as numerous cloud services simply remove such thing as the perimeter. It becomes almost impossible to control the data sent between the corporate network and the outer world. At the same time, this situation makes the work of attackers much easier, giving them more ways to get access to your network.

In the case of huge companies, perimeters are usually full of forgotten (or hidden) services, which are not in use, while admins have never applied patches for them. I would like to offer you to find such services in the corporate network of your company. We are going to use my favorite medical institutions as the best example to show the variety of attacking vectors. Later, you can easily use the obtained knowledge to analyze and examine the perimeter of the corporate networks located under your control.

## Scan, mark, and repeat…

Obviously, to understand the list of things located within the perimeter of the corporate network, one needs to get a detailed list of IP-addresses belonging to the chosen company. Such a list may include IP-addresses of third parties (service providers, subcontractors and so on). The attackers can easily add them to their list, while you have to avoid doing that at any cost. The list of IP-addresses can be added to a port scanning tool. Instead of using nmap, I recommend masscan[[1]](https://makrushin.com/attack-surface-osint/#_ftn1) or ZMap, which will significantly decrease the overall scanning time.

For example, to evaluate the list of the entry points available in a medical corporate network, one gets the IP ranges from RIPE containing the required names and keywords:

After that, one can launch the port scanner and get results in the next couple of days (Figure 1).

Figure 1 The fragment of a masscan report

While using ZMap for port scanning, one can later use ZTag to add required tags for each of the discovered services. Tags will be assigned according to the collected base of banners.

In the case of the medical institutions, all the services will be divided into the following groups (Figure 2).

Figure 2 Top services on the perimeter of the medical infrastructure

One can easily find many interesting apps among the myriads of web-apps and mailing services: building management systems [3]; printers (without any passwords for admin panels); NAS-storages (and even special PACS servers); smart kettles and other equipment. By using each of the discovered services, the attacker can create new vectors for their activity to evaluate the complexity (i.e. price) of their implementation (Figures 3, 4, 5).

Figure 3 Here’s an example of information obtained from a device using Niagara Fox protocol

Figure 4 This is a printer control panel that shows us the list of the available wireless networksFigure 5 This is an example of the medical portal that has a vulnerability and shows us the medical information

## OSINT without interaction

Another very popular way to get information about the perimeter without having any direct interaction with it is to use logs of Shodan and other similar systems, which robots are able to make all the work on behalf of the attacker.

## Get Denis Makrushin’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

As one can see from the logs above, all available servers are public, even though they may contain specific information about the activity of the target company, as well as other important and sensitive data. For example, if we take medical companies, the perimeter of their networks usually consists of DICOM devices and PASC servers (Picture Archiving and Communication System). All these devices are medical systems based on the DICOM (Digital Imaging and Communications in Medicine. DICOM is a well-known medical standard for the creation, storage, transmission and visualization of medical images and documents of the patients (according to Wikipedia). DICOM consists of the following components:

- DICOM Client: medical devices capable to connect to the DICOM to send information

- DICOM Server: a set of hardware and software solutions intended to receive and store information from the clients (including PACS servers as one of their varieties)

- DICOM stations and DICOM printers: a set of software and hardware tools intended to process, visualize and print medical images

One of the main distinctive features of the majority of such systems is the existence of a web interface that is used to control devices via the network. Such interfaces may contain vulnerabilities, which can be easily used by the attackers to get access to important processes and sensitive information. One needs to pay a lot of attention to such systems to understand if they can be used as an entry point by attackers.

One can make send a very simple query to Shodan engine to find DICOM devices: DICOM port:104 (Figure 6).

Figure 6 The list of DICOM servers

One can also search for special diagnostic DICOM stations, i.e. PACS-systems, which are used to process, diagnose and create a visual representation of the data. To make an example, one can use the following query for Censys search engine: pacs and autonomous_system.organization: (hospital or clinic or medical or healthcare) (Figure 7).

Figure 7 Login panels of diagnostic stations

By using a set of standard queries for Shodan to get the list of available resources on port 445 (SMB), attackers can sometimes get the names of internal resources (servers and working stations). Such names can be used to identify the list of interesting targets and avoid working with useless resources (Figure 8).

Figure 8 Information about the names of the resources in the local network of the company

## Collecting information for social engineering

As I mentioned above, one of the most efficient ways to get access to the corporate network perimeters is the usage of the wide range of social engineering tools. For example, one can send phishing links and attachments to lead workers to special phishing resources.

To implement such scenarios, the attacker needs to collect some information about the victim to increase the chance that one of the workers will follow the link or download the attachment. Currently, the security services of the biggest companies from all over the world, are trying to work with their staff to inform them about phishing, which is not the best thing for the attackers. These days, the attackers need not only to go through the filters of the victim and add some useful information to their letter but to create motivation for the victim to perform required actions without causing even a slight suspicion.

The wide range of social networks, as well as the open approach of the majority of the users, allows the attacker to gain access to the required information by adding some ‘useful payload’ to their original message: it can be a letter or a style of communication and so on.

This task is truly creative and depends on a specific situation. The best example is a resource based on the API of the most popular social networks to get the most important information about the accounts (Figure 9).

Figure 9 Here’s an example of OSINT web-service based on the APIs of the social networks

For example, using data extracted from LinkedIn, the attacker can identify the list of the key employees of the companies to implement a spear-phishing attack using their names, surnames, and contacts (addresses). By using this information, one can easily find personal profiles of these employees on Facebook and other networks. The mentioned service can also collect some stats, e.g. information about the hotels they used to stay in (by using their locations and check-ins). After that, the attacker can easily send a letter about Resort Fees, which must be paid, adding an invoice in PDF. Profit!

## Recon as a form of art

The topic about the extraction of information about the victim is endless, and there are materials [4] telling us only about the intelligence based on the open sources of information. That’s why I decided to use this article to tell you about the collection of technical information about the perimeter of the corporate network that contains (in many cases) so-called open doors, which can be open for many years in a row, while the owner of the network is simply not aware of them.

Furthermore, the attacker trying to get to the corporate network through external resources does not need to interact with a real human (as it happens in the case with social engineering), thus they need to overcome a single obstacle: various IDS/IPS, WAF, and other systems intended to detect all kinds of activity on the perimeter. In case there are any of them installed.

## Conclusion

The paper introduced the case study for attack surface analysis and monitoring with practical application of open-source intelligence (OSINT) methods. The case is based on the perimeters of healthcare organizations and aims to introduce the threat landscape of the healthcare industry as well as methods to collect information about entry points and assets on the network perimeter. Techniques and tools in this paper are not limited by organization type and can be applied for different network assets to prepare initial information during the first stage of penetration testing and red team operations.

### Acknowledgments

Thanks to Alexander Barabanov, Dmitry Zheregelya, and Igor Korkin for proofreading, editing, and constructive feedback.

---
