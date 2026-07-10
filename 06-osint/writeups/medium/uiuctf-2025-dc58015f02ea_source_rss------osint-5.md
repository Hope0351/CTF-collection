# :sleuth_or_spy: UIUCTF 2025. Hello folks today I write about OSINT…

---

Hello folks today I write about OSINT challenges I solved in UIUCTF so lets go to look at challenges :

## First Challenge : Mr. Blue Sky

his profile

*[https://bsky.app/profile/mrbluesky1989.bsky.social](https://bsky.app/profile/mrbluesky1989.bsky.social)*

when read description you should think for check interaction and comments but take care of time of interaction it may from player to pass wrong flags so after I do this nothing found so I thought if he share something and delete it from his account so I will try archiving :

*[https://archive.is/Q4yHX/image](https://archive.is/Q4yHX/image)*

so let’s go to this post

*[https://bsky.app/profile/vickyoutenphoto.bsky.social/post/3lt6xxtx3252z](https://bsky.app/profile/vickyoutenphoto.bsky.social/post/3lt6xxtx3252z)*

if you look at comments finally you reached

but so sorry this’s wrong flag let’s dig deep to check post and we get

who’s followers of him

so finally we get correct flag which : uiuctf{y0u_dr0pp3d_y0ur_cr0wn_k1ngf15h3r_132323098}

and so I know flag format which ended with number so no wrong flags with same format

## Second Challenge : Bad Blood

After I search in accounts and comments I found this

but not forget flag format and time of flag there’s after CTF

So try new thing why not use search bar in bsky to found all flags wrong and right and this result

all this wrong but look at this

right flag : uiuctf{bU7_1m_4_c4pr1c0rn_7098743}

## third Challenge :Age of Aquarius

there’s her account

I can’t solve this but after check her account , I get her birthday date

*[https://www.tumblr.com/16degreesofscorpio](https://www.tumblr.com/16degreesofscorpio)*

June 29 and I was close to guess country from her posts analytics

## Location

- They said: “I’ll be hosting close to where I was born and raised.”

- That implies a return to a familiar or hometown area. However, no specific city, state, or country is publicly mentioned in the post archive. Without explicit details, we cannot ethically or accurately determine their state or exact location.

✅ Conclusion: Location not publicly disclosed.

## Fourth Challenge :Park

after Analytics

while I use google lens I found this

*Brand på restaurang på Tegnergatan i Stockholm‏*

which in Stockholm , Swdeen

let’s verified by walking there

so flag is : uiuctf{Tegnérlunden}

Finally I hope you benefit from my writeup and if you have any question contact me , Good BYE

---
