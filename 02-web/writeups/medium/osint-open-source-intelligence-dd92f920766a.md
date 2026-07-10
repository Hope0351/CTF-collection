# :globe_with_meridians: Medium

---

# Weekly OSINT(Open Source Intelligence)

Week1

Hello there!!!Hope you are doing well.

This blog is the first page of a informative , exciting book of OSINT. Don’t think of this has some long , boring pages of info being dumped.

Even if you aren’t a person who is interested in offensive security , investigation or forensics **do give a shot at this blog** because this will help you understand

## How can we use search engines effectively?

## How to assess tiny details on a given bit of info and how to get a bigger image out of it?

## And finally you can have some **fun **too.(which is very important 😉)

In this weekly blog I will post a curated list of challenges solved using different aspects and methods used in OSINT .

Also I express the methodology I generally use to solve these challenges so it may not be directly point you to the solution .

The major source of these challenges will be:

- Geoguessr : This is a fantastic resource to improve our OSINT skills on finding info on Geographical location.

2. Different ctf and quiz recommended by OSINT dojo .

3. Hack The Box :

4.Quiztime page in Twitter

This weeks challenges are:

The ctf from OSINT dojo is

1)

So in this challenge we are given a pic of a car and our goal is to find its make and month it was made.

Sounds cool right!!!!

Ok get ready folks with your investigator hat and lets dive into our problem.

This is the image we got from our **Agent** who is assigned to our Person of Interest.

So the first tool we will be using is …………..

**Google**

Most of you would have raised your eyebrows for this but let me show you how is it possible..

Google has lots of features which we aren’t aware of and one such is the Google reverse image search.

This allow us to search for a particular image in the internet by **uploading the image we have**.

We can also use **Yandex reverse image** search for the same.

As a investigator the more the tools we use, the chances of getting relevant information increases so always give a try on everything we have.

We have got the results……

And we got the type of body configuration and lots of companies manufacture this ..So its kinda dead-end.

The other info we have or could visually see is the registration number which is

**CY10 HHB**

Searching for this we get :

And the second link in this page gives us all the required info to construct our flag and even more.

## flag: **FORD JUNE**

There are even mobile apps to do the same and if you have some suggestions let me know!!

— — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

2)

The next challenge is we are given a site through which we have access to a live security camera at some part of the world.

We need to find **Country where **this camera is located so as to find a dangerous criminal.(Another thrilling and exciting task…)

Now another tool to add to our arsenal and my personal favorite and the one of the best tools we have for OSINT is ………

**Shodan**

This is like a search engine for **internet connected device**.

## Get Thirukrishnan’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

So we can access devices like web-cams , servers ,and much more….

>

Though we may have some restrictions posted by the owners ..😂😂

So with shodan we can search for the particular IP of the web-cam we are given.

Another challenge solved ….We found the country

## FLAG:Belgium

3)

I will attach the image and if you are interested to find answers for these do give a try .

SO we are supposed to find the location and time at which the photo was taken.

Using image reverse search did not seem to work so we have to find this is using a different approach.

>

And usually the challenges from this are not straight-forward ones.

So giving a close look to the pic we could see many graffitis in the wall so searching by one of them we get:

search : love hurts with unicorn graffiti

Got the exact picture and visiting the page we got infomation on the location.

Great……

So the location is neukolln Berlin.

And another clue we have is the** flag** the people hold and it is like a protest.

So searching for the particular pattern in the flag I found its **Palestine** flag.

Another location clue is the **Grand Hostel board on the building.**

SO now we know its some protest supporting Palestine done in Berlin.

With all these information we can find the location and date as:

### FLAG: View towards Sonnenallee 6 (Grand Hostel) Berlin, date of free Palestine demo 15.5.21.

## **— — — -A picture is worth a thousand words — — — —**

This challenge is the best one to prove this quote I guess….

4)

The last one for the week is from hackthebox.

We need to find a man named **Roland Sanchez of Birmingham UK**.

And again we use the same tool Google with some different operators.

Operators in Google are the keys to use it effectively and utilize its max potential.

Some common ones are:

- <search-term> intext:<some-text>

This displays only the websites which have a certain text string we mention.

This helps us to find sites , which has some text we know in its body.

2. <search-term> inurl:<some-text>

This operator is same as intext but this matched the specified string with url .

3.<search-term> site: abc.com

This displays the searched query only in the site we have mentioned.

And there are many which include AND, OR ,….

**For further info use:**

SO first I used the search string:

search: Roland Sanchez AND Brimingham UK

This displays results which have both the name and location.

We could see a linkedin page and another blog page which says he is on vacation.

Immediately my investigator mind littttt uppppp…

The flag format for hackthebox is HTB{

With this we can use the intext operator to find the site and it did worked….

— — — — — — — — — — Boooommmm — — — — — — — — — — — — — — —

So as you reached the end of this blog most of you might think

## How will these help me at all???

Let me say some of the wide range of things you can get out of this.

- The operators in Google:

If you are a programmer you can search for source codes or some questions you have effectively by

<project-name> site:github.com

<project-name> site:stackoverflow.com

2. If you are about to buy a second-hand car you can verify the details provided and out on the internet to get a clear picture.(By this I don’t claim the info on internet is valid but still its good to check)

3. For the fun part I mentioned earlier , play Geoguessr to guess the place we are been dropped or visually roam the streets of different parts of the world with the help of Street maps by Google and one can even use Shodan to have fun which I leave it for you to explore.

SO thats it for this week…..

Let us meet soon with more challenges and fun .

Thank YOU!!!!!!

---
