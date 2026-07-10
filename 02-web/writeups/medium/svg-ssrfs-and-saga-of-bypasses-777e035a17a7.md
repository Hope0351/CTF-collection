# :globe_with_meridians: SVG SSRFs and saga of bypasses

---

# SVG SSRFs and saga of bypasses

## Hi all, hope you are keeping well and staying safe. This blog is about my recent experiences with SVG, HTML to PDF SSRF, and bypasses for the patches applied.

### Introduction

I was testing an app that was a web-based analytics solution that dealt with research institutions worldwide to analyze new, emerging research trends, and create reports.

As the application heavily deals with data analytics, the app had functionalities to show the research data as pie charts, graphs, tables, etc. Reports can also be prepared with the data and shared with co-researchers.

These pie charts, reports, and graphs could be exported to DOCX, PDF, and PNG. You see where I’m going right?

### Exploitation

As we learned earlier, the research data is shown in the form of charts. Below is a screenshot for the same.

To the right of the screenshot, we see the option to *“Export the chart as an image”*

Upon clicking the “Export chart as an image”, we see a POST request going to with the image content like in the below screenshot.

---
