# :sleuth_or_spy: Maveris OSINT CTF 2024 Writeup | JJ's Blog

---

*mile21.png - Image Provided in the question*

Using Google Images, I identified the young athlete as Parker Valby, who represents the U.S. in the 2024 Olympics. The task was to find the recorded time that earned her a spot in the Olympics, down to the thousandths of a second. After reviewing several articles, I initially found a time of 31:41:56.

*[https://www.letsrun.com/news/2024/06/womens-10k-weini-kelati-wins-olympic-trials-parker-valby-karissa-schweizer-looking-good-for-paris/](https://www.letsrun.com/news/2024/06/womens-10k-weini-kelati-wins-olympic-trials-parker-valby-karissa-schweizer-looking-good-for-paris/)*

*[https://www.upmatters.com/2024-olympics/tampa-native-parker-valby-super-grateful-to-reach-paris-olympics/](https://www.upmatters.com/2024-olympics/tampa-native-parker-valby-super-grateful-to-reach-paris-olympics/)*

The second image provided in the task was of Bremen Cathedral (St. Petri Dom) located in Bremen, Germany.

Additionally, I researched a German logistics company founded in 1890, Kuehne + Nagel.

Using Parker Valby’s time (314156) as a customer reference number on a [shipment tracking page](https://mykn.kuehne-nagel.com/public-tracking/), I received a volume of 0.940m³. However, when submitting the number as a flag, it was incorrect.

After multiple attempts, I again verified my search for Parker Valby’s recorded time. I came across a [YouTube video](https://www.youtube.com/watch?v=cQXsLco8v4o) that mentioned the time as 31:41.553. I used this time as a customer reference number (3141553), and finally, this led me to the correct flag.

*[https://www.youtube.com/watch?v=cQXsLco8v4o](https://www.youtube.com/watch?v=cQXsLco8v4o)*

Flag - 0.292

This experience taught me the importance of verifying information from multiple sources.

---
