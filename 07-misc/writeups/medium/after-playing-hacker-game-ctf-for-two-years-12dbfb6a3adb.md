# :game_die: 駭客的線上遊戲 CTF 遊玩兩年心得. CTF，全名為 Capture the…

> **Original Source:** [駭客的線上遊戲 CTF 遊玩兩年心得. CTF，全名為 Capture the…](https://hulitw.medium.com/after-playing-hacker-game-ctf-for-two-years-12dbfb6a3adb)
> **Platform:** hulitw.medium.com | **Category:** `MISC`

---

以前剛開始的時候其實都寫英文的，畢竟這個圈子是國際性的，英文還是能見度最高的語言：


*以前的英文 writeup，現在搞不好用 chatGPT 翻譯還比較快*


除了為了自我的成長跟學習寫心得以外，許多比賽會要求前幾名的戰隊提交解題心得，以此證明真的有把題目解開。而有些比賽甚至會舉辦心得會外賽，只要心得寫得好，一樣能拿獎金。


我去年有為了 Google CTF 認真寫了一篇心得去投稿：[Insecure Deserialization in JavaScript: GoogleCTF 2022 Web/HORKOS Writeup](https://blog.huli.tw/2022/07/11/en/googlectf-2022-horkos-writeup/)，最後拿到了 200 美金的獎金以及很有質感的紀念品：


*一個很像獎牌的東西，質量滿不錯的（是那個質量不是那個質量），沉沉的*


講到錢錢，CTF 的比賽是有獎金跟獎品的，越大的公司辦的比賽獎品越好。以 Google CTF 2022 來說，第一名有大約台幣 40 萬，第二名 20 萬，第三名 10 萬。


LINE CTF 2023 前三名也依序有台幣 15 萬、10 萬跟 6 萬。


不過這些錢雖然看起來很多，但戰隊人數也不少（少則 10 人起跳，多可以多到 30 人甚至是 50 人或更多），分下來也沒有多少錢。而且比起分下來，更多的做法是作為戰隊基金，贊助之後出國比賽的費用。


有些 CTF 比賽都是跟隨著資安研討會一起舉辦的，而這些比賽通常都會有預賽，取前幾名進入決賽，才是正式拿到了 on-site 參加比賽的門票。


講到出國比賽，就不得不提 CTF 圈中的重頭戲：DEF CON CTF。


DEF CON 是一個每年都會在美國舉辦的資安研討會，許多最新的攻擊手法都會在那邊發表，而 DEF CON CTF 是其中的一個活動，也可以視為是 CTF 比賽中的最高殿堂。


有聽過資訊奧林匹亞競賽或是數學奧林匹亞競賽嗎？把 DEF CON CTF 想成是每年一度的 CTF 奧林匹亞競賽就對了，差不多是那種感覺。


不過雖然聽起來很盛大，但主辦單位還是民間團體，所以只會贊助基本的住宿（而且有限人數，我記得是 8 個），機票要自己負責。


因此有些戰隊就會把打比賽拿來的獎金存著當作公積金，贊助戰隊成員出國比賽，或有些戰隊會找贊助商來贊助，例如說台灣每年都會有至少一隊出去比賽，由政府單位以及其他公司贊助（延伸閱讀：[DEF CON CTF資格賽，臺灣聯隊攜手獲得第二名，八月進軍賭城實體較勁](https://www.ithome.com.tw/news/151209)）


DEF CON CTF 的比賽方式也不是我開頭講的那種，而是另一種叫做 Attack & Defense 的玩法，除了攻擊別人以外，你也要修復自己的服務，把漏洞修掉。這個模式更有競賽的感覺而且戰況瞬息萬變，除了考驗找出漏洞的能力以外，也更考驗選手們自行準備的 infrastructure。


我去年有幸參加了 DEF CON CTF，有寫了幾篇心得，結論是我好像想的太盛大了，實際參與就覺得有點失望，更詳細的心得可以參考這篇：DEF CON 30 CTF final 遊記（中）


比起 CTF Time 的排行榜，各個戰隊最想拿到的應該還是 DEF CON CTF 的冠軍。


喔對了，因為 DEF CON CTF 決賽只取預賽的前十六名參加，機會很少，再加上每個隊伍都想要盡可能增加競爭力，所以最近一兩年 CTF 圈開始吹起了抱團的風氣。


下圖是 2022 年參賽隊伍的組成，紅色是最後的隊伍名稱，藍色跟綠色是隊伍的組成：

---

*Originally published on [Medium](https://hulitw.medium.com/after-playing-hacker-game-ctf-for-two-years-12dbfb6a3adb). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
