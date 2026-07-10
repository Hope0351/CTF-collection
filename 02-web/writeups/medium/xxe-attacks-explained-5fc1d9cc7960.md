# :globe_with_meridians: XXE Attacks Explained. Out of the many attacks that threaten…

---

## Introduction to XML

XML ( eXtensible Markup Language) is a tag-based language that applications use for transferring data. Contrary to other tag-based languages (like HTML), XML does not have pre-defined tags. Instead, these are defined by the user.

Here is an example of an XML code:

```
<email>
<sender>John</sender>
<recipient>Peter</recipient>
<subject>Hi</subject>
<message>Hi Peter, How are you doing?</message>
</email>
```

In the above code, the *email* tag contains 4 child tags: *sender*, *recipient*, *subject*, and *message*. Each of these tags encloses a string of characters, referred to in XML as parsed character data (or PCDATA).

### XML File Declaration

An XML file should start with an XML declaration. This should include at least the *version* of XML that the file uses. It can also include the *encoding* and *standalone* as options. These two are optional, but the *version* attribute is mandatory.

Here is how an XML file declaration should look like:

```
<?xml version="1.1" encoding="UTF-8" standalone"yes"?>
```

As you can see, there are three different attributes:

- version : This can either be 1.0 or 1.1. If you do not write an XML declaration, then the version defaults to XML 1.0.

- encoding : In most cases, you will be using UTF-8. However, depending on the characters used, you can specify UTF-16 for this attribute.

- standalone : This attribute can have either yes or no values. It indicates whether the XML file depends on any other files to work properly or not.

### Document Type Definition (DTD)

DTD ( Document Type Definition) defines the structure of an XML document so that different people can agree on the same elements and attributes to use.

There are two different types of DTDs:

1- Internal DTD

When an XML document includes the definition of its own structure, that definition is what we refer to as an internal DTD. It is contained in the tag `<!DOCTYPE>` that is written at the beginning of the file, just after the XML declaration.

Here is an example of an internal DTD:

```
<!DOCTYPE email [
<!ELEMENT email (sender,recipient,subject,message)>
<!ELEMENT sender (#PCDATA)>
<!ELEMENT recipient (#PCDATA)>
<!ELEMENT subject (#PCDATA)>
<!ELEMENT message (#PCDATA)>
]>
```

With `!DOCTYPE email`, we define *email* as the root element of the XML document.

The second line specifies that the *email* element should contain four child elements: *sender*, *recipient*, *subject*, and *message*.

After that, we specify that each of these child elements should contain parsed character data (PCDATA).

You have probably noticed that this DTD defines the same structure that we’ve seen in the previous XML code example.

2- External DTD

Now for this second type, we define the XML structure in an external file. In this case, the `<!DOCTYPE>` tag should contain the URL to the DTD file using the SYSTEM keyword.

We need to add the following line to the beginning of our XML document, just after the XML declaration line.

```
<!DOCTYPE email SYSTEM "email.dtd">
```

And here is what the external DTD file “email.dtd” contains:

```
<!ELEMENT email (sender,recipient,subject,message)>
<!ELEMENT sender (#PCDATA)>
<!ELEMENT recipient (#PCDATA)>
<!ELEMENT subject (#PCDATA)>
<!ELEMENT message (#PCDATA)>
```

Here again, DTD defines the same structure as in the examples we’ve seen before.

### XML Entity

An XML entity is a string of characters that the XML parser replaces with another value when encountered in the document. This is similar to what variables are in programming languages.

An entity is written in the form: Ampersand (&) + name of entity + semi-colon (;).

In addition to user-defined entities, there are many built-in entities. Such examples are `&lt;` and `&gt;`, which get replaced with the lower than (<) and greater than (>) characters respectively.

Similar to DTDs, there are two types of entities: Internal and external.

## Get A. Boukar’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

1- Internal Entities

An internal entity is defined in the following form :

```
<!ENTITY name "value">
```

Whenever there is a `&name;` in the file, the XML parser replaces it with *value*.

2- External Entities

On the other hand, instead of providing a value, an external entity refers to a URL using the SYSTEM keyword.

```
<!ENTITY name SYSTEM "URL">
```

Similar to an internal entity, whenever a parser encounters a `&name;` in the XML file, it replaces it with the content of the URL that the external entity declaration refers to.

---
