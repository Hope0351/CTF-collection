# :game_die: CyberDefender: “The Crime Lab” Challenge Writeup

---

**ALEAPP** churned through the data, producing a comprehensive report in output_report/index.html. Opening it in a browser revealed a treasure trove of artifacts:

- **SMS/MMS**: Messages with timestamps, senders, and content.

- **Call Logs**: Incoming and outgoing calls with durations.

- **Contacts**: Phone numbers and names.

- **Location Data**: GPS coordinates from apps or system logs.

- **App Data**: Artifacts from messaging apps or notes.

This report was my first stop for flag hunting, offering a high-level view of the victim’s activities.

## Questions

>

***Q1: Based on the accounts of the witnesses and individuals close to the victim, it has become clear that the victim was interested in trading. This has led him to invest all of his money and acquire debt. Can you identify the ***`***SHA256***`*** of the trading application the victim primarily used on his phone?***

Upon reviewing the list of installed applications on the victim’s phone using ALEAPP, we identified a suspicious app related to trading: `com.ticno.olymptrade`. This aligns with witness reports regarding the victim’s financial activities.

We extracted the APK information and calculated the SHA256 hash of the application package.

```
✅ Answer:
4f168a772350f283a1c49e78c1548d7c2c6c05106d8b9feb825fdc3466e9df3c
```

>

***Q2: According to the testimony of the victim’s best friend, he said, “***`***While we were together, my friend got several calls he avoided. He said he owed the caller a lot of money but couldn't repay now***`***". How much does the victim owe this person?***

We examined the SMS database and located a threatening message from the number `+201172137258` received on **2023-09-20 20:09:49**. The message clearly states:

>

“Prepare the sum of **250,000 EGP**, and I’ll expect your call within an hour at most.”

This corroborates the testimony of the victim’s best friend, confirming the victim owed this person money.

```
✅ Answer:
250,000 EGP
```

>

***Q3: What is the name of the person to whom the victim owes money?***

From the threatening SMS sent by`+201172137258`, we cross-referenced this number with the **contacts database** on the victim’s phone using ALEAPP or manually via `contacts2.db` DB Browser for SQLite.

The number **+201172137258** is saved under the contact name:

>

***Shady Wahab***

This confirms the identity of the person demanding repayment.

```
✅ Answer:
Shady Wahab
```

>

***Q4: Based on the statement from the victim’s family, they said that on ***`***September 20, 2023***`***, he departed from his residence without informing anyone of his destination. Where was the victim located at that moment?***

Further analysis of the **recent app activity logs** revealed that the **Google Maps application** (`com.google.android.apps.maps`) was actively used on **September 20, 2023 at 23:50:29**.

## Get SHENOBIE’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

From the extracted metadata:

- **App:** Google Maps

- **Location shown in snapshot:The Nile Ritz-Carlton**

- **Activity:** `MapsActivity`

- **Image evidence:** `6.jpg` (screenshot of location)

This indicates that the **victim was either searching for or navigating to “The Nile Ritz-Carlton”** at that specific time, shortly after receiving the threatening message earlier that night.

## Final Conclusion:

Based on timestamped app activity and screenshot evidence, **the victim’s last known location** on the night of **September 20, 2023,** was:

```
✅ Answer:
The Nile Ritz-Carlton
```

>

***Q5: The detective continued his investigation by questioning the hotel lobby. She informed him that the victim had reserved the room for 10 days and had a flight scheduled thereafter. The investigator believes that the victim may have stored his ticket information on his phone. Look for where the victim intended to travel.***

ALEAPP did not yield relevant location data, so a manual inspection was conducted.

## Investigative Process:

- **Checked ALEAPP’s location artifacts** — No usable results were found.

- **Manually browsed the device file system**, particularly the `Media/Download` folder.

- **Found a saved image or document** indicating a location.

- Based on naming, metadata, or visible content, it pointed to **Las Vegas**.

This strongly suggests the victim was in **Las Vegas** around the time in question, despite not informing family of his whereabouts

```
✅ Answer:
Las Vegas
```

>

***Q6: After examining the victim’s Discord conversations, we discovered he had arranged to meet a friend at a specific location. Can you determine where this meeting was supposed to occur?***

We reviewed the victim’s **Discord messages**, focusing on conversations around **September 20, 2023**.

A key message was found from user **rob1ns0n**, timestamped:

>

**2023–09–20T20:46:02Z**
*“What a wonderful news! We’ll meet at The Mob Museum, I’ll await your call when you arrive. Enjoy your flight bro ❤️”*

This indicates the victim was scheduled to meet at **The Mob Museum**.

```
✅ Answer:
The Mob Museum
```

Through a combination of forensic tool analysis and manual investigation, we successfully traced the victim’s financial troubles, identified the individual he owed money to, uncovered his last known location, and confirmed his intended meeting spot on the day of the incident.

This comprehensive investigation demonstrates the critical importance of endpoint forensics in reconstructing events and uncovering the truth in digital crime scenes.

The pieces now fit — and the story is clear.
**Case Progress: Solid. Trust, kept.** ✅🕵️‍♂️

---
