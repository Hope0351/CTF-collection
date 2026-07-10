# :locked_with_key: [ISITDTU CTF Final] Crypto Write-ups

---

# [ISITDTU CTF Final] Crypto Write-ups

Bây h mới viết WU thì hơi trễ, mình viết với mục đích chia sẻ cho các bạn về solutions của mình, về đề thì mình thấy rất hay trải đều các mảng chứ không nặng một mảng nào đó, điều có làm cho mình có Crypto để làm (nếu không có thì sure là nhìn đề rồi ra về =]]] ). Tiếc là 3 tiếng cuối mình vẫn không thể làm được bài babycrypto (cho đến bây h vẫn chưa làm ra). Đáng buồn là từ quals đến final mình thọt đúng bài cuối :< . Tự hứa với bản thân là sẽ học thêm nữa (try fucking hard =]]] ).

- X000R

task: [link](https://drive.google.com/file/d/1pI-SkLiBjAGcfw4RdkCl-T7B-db44LXr/view?usp=sharing)

Một bài warm up khá dễ cho tất cả các đội có thể có điểm, chỉ cần code xíu là có flag ngay ✌

*flag here*

2. RSA

task: [link](https://drive.google.com/file/d/1fS4LY-9nE2U_HiPSJhQ7OswFwnvRR91N/view?usp=sharing)

Vừa đọc đề phát thì thấy sao nó quen vãi =]]], nhớ lại ngày ấy tìm trong github của anh X thấy bài hay down về nhưng méo biết làm, một lúc sau chủ động ib và được X trợ giúp, từ đó dần dần X giúp mình nhiều hơn và những lần ăn chửi =]]] mà mình tiến bộ hơn.

*unforgettable memory :<*

Vì bài này mình làm rồi nên khá dễ cho mình =]]], tầm 10p mình first solve và có 1k point. X đã quăng cho mình cuốn chân kinh để làm bài này, bây h mình cũng xin phép chia sẽ với các bạn chân kinh từ X: [link](https://drive.google.com/file/d/1lr63xBKNom7CMaJhlngtmvg-3U9WvaRH/view?usp=sharing)

Đến đây thì biết rõ ai ra đề cmnr nha =]]]]. Ib nhẹ để confirm phát thì ...

Sory mình quên mất flag là gì rồi :(.

3. Archive

Tittle méo liên quan lắm gì đến bài này vì nó là RSA, một bài blackbox khá thú vị, mình mất khoản 4 tiếng để done (i'm so noob : ( ) . Mấy bạn có thể tìm source của tác giả đã public khi guess được X là ai =))), chỉ cần kéo về chạy file là có ngay bài blackbox. May mắn thay là không có timeout nên việc làm tay là phù hợp :>.

Stage 1:

ta thấy e=3 (rất nhỏ), c nhỏ rất nhiều so với n, thử lấy căn bậc 3 của c và ta có plaintext cần tìm

Stage 2:

ta thấy e rất lớn => có thể dùng wiener attack

Stage 3:

stage này khá là dị :( , ban đầu factor được n và cảm thấy chuẩn bị sang stage 4 =))), nhưng khi decrypt thì nhận ra rằng gcd(e,d) != 1 (từ lúc học crypto đến bây h toàn gcd(e,d) = 1 xem như là sgk luôn rồi :< ). Loay hoay mãi thì mình quyết định google xem. Sau một lúc thì mình tìm thấy: [link](https://github.com/ValarDragon/CTF-Crypto/blob/master/RSA/RSATool.py), với function (invalidPubExponent). Bingo coi như gặp được chân kinh lần 2 =)))

*explanation*

May mắn thay ta đã factor được n (close prime)

Việc còn lại là recover plaintext thôi

Stage 4:

N khá nhỏ, thử factordb và kết quả

Stage 5:

*Ý tưởng giống bài RSAbaby CodeGate 2018*

*Solution*

Note: p,q là 2 biến mình tự đặt, tính gcd(p*q-c,n) là tìm được p => q (đã factor xong) => plaintext

Và đây là kết quả cho 4 tiếng =))) (flag đã thay đổi)

Kết,cảm ơn ĐH Duy Tân đã đứng ra tổ chức 1 kỳ thi CTF mang lại nhiều cảm xúc cũng như các challenge hay đã thõa mãn được player =))), mong rằng năm sau mình sẽ tiếp tục có cơ hội đến với Đà Nẵng. Đà Nẵng thật đẹp, Hội An về đêm cũng thật đẹp, biển Mỹ Khê cũng đẹp, nói chung là Đà Nẵng là 1 địa điểm du lịch rất lý tưởng :>, đồ ăn cũng rất ngon giá cả lại ổn định, người dân rất thân thiện. Hẹn Đà Nẵng một ngày không xa ... ❤❤❤

*Da Nang in our eyes ❤*

---
