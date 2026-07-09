 OSU CTF - Web Challenge 
 Challenge Overview  

- Challenge Name: Trivial  
- Category: Web  
- Difficulty: Moderate  
- Objective: Exploit a vulnerable web application to gain admin privileges and retrieve the flag.  

 Initial Steps
I started by attempting an SQL injection on the login page using the following payload:
```sql
Admin' or 1=1--
```
This allowed me to bypass authentication and gain access to the dashboard.

 Inspecting JavaScript Files
Next, I inspected the JavaScript files in the application by opening the browser’s Developer Tools. I looked for unlinked routes and hidden functionalities within the code.

One particular JavaScript file, `/assets/js/app.min.js`, caught my attention. It contained the following script:
```javascript
(function (s, objectName) {
  setupLinks = function () {
    if (s.admin) {
      var sl = document.getElementsByClassName('student-link');
      for (i = 0; i < sl.length; i++) {
        let name = sl[i].innerHTML;
        sl[i].style.cursor = 'pointer';
        sl[i].addEventListener('click', function () {
          window.location = '/update-' + objectName + '/' + this.dataset.id;
        });
      }
    }
  };
  updateForm = function () {
    var submitButton = document.getElementsByClassName('update-record');
    if (submitButton.length === 1) {
      submitButton[0].addEventListener('click', function () {
        var english = document.getElementById('english');
        english = english.options[english.selectedIndex].value;
        var science = document.getElementById('science');
        science = science.options[science.selectedIndex].value;
        var maths = document.getElementById('maths');
        maths = maths.options[maths.selectedIndex].value;
        var grades = new Set(['A', 'B', 'C', 'D', 'E', 'F']);
        if (grades.has(english) && grades.has(science) && grades.has(maths)) {
          document.getElementById('student-form').submit();
        } else {
          alert('Grades should only be between A - F');
        }
      });
    }
  };
  setupLinks();
  updateForm();
}) (staff, 'student');
```

 Exploiting the `s.admin` Variable
I noticed the variable `s.admin`, which seemed to control access to certain functionalities. By checking its value in the console:
```javascript
console.log(s.admin);
```
I found that it returned `false`. I then manually set it to `true`:
```javascript
console.log(window.staff.admin);
staff.admin = true;
setupLinks();
```
![Screenshot (5)](https://github.com/user-attachments/assets/26e6016e-3884-475a-b3d6-928d564a30b7)


Now, I was able to click on student names.

 Finding the Encoded String
Clicking on a student’s name (e.g., ‘Brett, Nancie’) redirected me to:
```
/update-student/TmFuY2llX0JyZXR0
```
The random string at the end looked suspicious. I used [hashes.com](https://hashes.com/en/tools/hash_identifier) to identify it and found that it was Base64 encoded. Decoding it revealed:
```
Nancie_Brett
```

 Modifying the Request
I replaced `Nancie_Brett` with `Natasha_Drew`, encoded it in Base64, and updated the URL to:
```
/update-student/TmF0YXNoYV9EcmV3
```
I then changed all scores to ‘A’ and clicked on `Update Record`.

 Capturing the Flag 
Flag : *FLAG^f91b0d22ed751f02a7ebd81acc0411163949204eaf6a786c9581f29d8a5ec41c$FLAGS 

After updating the record, the flag popped up, marking the successful completion of the challenge!

![Screenshot 2025-02-17 224635](https://github.com/user-attachments/assets/b892f777-94b1-465f-a0c6-06b24058696e)


