# :electric_plug: Deadface CTF 2023 - SQL. Write-ups for Deadface 2023 CTF SQL…

---

## SHAttered Dreams

*SHAttered Dreams challenge*Task

>

DEADFACE is on the brink of selling a patient’s credit card details from the Aurora database to a dark web buyer. Investigate Ghost Town for potential leads on the victim’s identity.

Submit the flag as `flag{Firstname Lastname}`. Example: `flag{John Smith}`.

Use the database dump from *Aurora Compromise*.

Solution

I skipped some SQL challenges near the end of the CTF as my strategy shifted to “get the biggest points you can now”!

This one was fun and I have learned neat functions in MySQL that I have not used before.

The hint in the challenge description suggests that we must crawl the Ghot Town forums and find potential leads to identify our victim.

>

We got a potential buyer
[https://ghosttown.deadface.io/t/we-got-a-potential-buyer/107](https://ghosttown.deadface.io/t/we-got-a-potential-buyer/107)

*Ghost Town forum chatter*

*Ghost Town forum thread*

*Ghost Town thread (cont)*

So what we know so far is that there is a patient that had his details concatenated then a SHA1 sum function was applied to his details.

The following pieces of data were collected from the database.
Take note as we will be hunting for the patient using those details.

Billing table:Patients table:

- patient_id

- patient first name

- patient last name

- patient middle initial

- patient sex

- patient email

- patient address (street, city, state, zip)

- patient dob

The leaked hash to search for and match against:
*911d1fc5930fa5025dbc2d3953c94de9e4773584*To identify him we have to do a series of steps

- Structure a query involving at least two tables (billing and patients)

- Retrieve all the pieces of data above using *patient_id* as the ID to join the two tables

- Concatenate the all the data including the address data

- Run a SHA1 hash function on the result of the concatenated data

- Now we have all hashes, compare them to the leaked hash for a match

- Select the *first_name* and *last_name* of the patient that matches

Here is what the query looks like now

```
sSELECT
patients.first_name,
patients.last_name
FROM
billing
JOIN
patients ON billing.patient_id = patients.patient_id
WHERE
SHA1(
CONCAT(
billing.card_num,
billing.exp,
billing.ccv,
patients.patient_id,
patients.first_name,
patients.last_name,
patients.middle,
patients.sex,
patients.email,
CONCAT(patients.street, patients.city, patients.state, patients.zip),
patients.dob
)
) = '911d1fc5930fa5025dbc2d3953c94de9e4773584';
```

This returns the answer of:

```
+------------+-----------+
| first_name | last_name |
+------------+-----------+
| Berton | Luchetti |
+------------+-----------+
1 row in set (0.037 sec)
```

flag{Berton Luchetti}

---
