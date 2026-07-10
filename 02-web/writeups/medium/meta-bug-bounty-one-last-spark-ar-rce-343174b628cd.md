# :globe_with_meridians: Meta bug bounty — One Last Spark AR RCE

---

# Meta bug bounty — One Last Spark AR RCE

[Free Link](https://blog.fadyothman.com/meta-bug-bounty-one-last-spark-ar-rce-343174b628cd?sk=a3113422649a82973e07de8dc4bcd767)

I highly recommend that you read my previous Spark AR write up, while the two bugs are not related, the other post contains more information about how spark AR works and the methodology I follow to analyze Spark AR for vulnerabilities, with that said let’s begin.

While looking at Spark AR studio, I noticed a feature that allows installing packages from AR library (an online library for spark AR packages), my first instinct was trying to publish a package and investigate how that works, however, it turns out only verified authors are allowed to publish packages, this is usually an indicator that some level of trust is given to those packages.

So instead of publishing my own package, I went to the second option, I installed one of the available packages and I saved the project as “.arexport” file, then I opened it using 7zip (.arexport files are just zip file containing the project files).

When I opened the file, something immediately caught my eye, there was a new folder added to the archive named “internal”, the name is very interesting, and inside that folder there was a zip file named “kitchensink.zip” which is also an interesting name.

I opened the “kitchensink.zip” file and found that it contains package.json which is usually a file used to describe node…

---
