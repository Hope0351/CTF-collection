# :game_die: What are Props and Transforms in Splunk?

> **Original Source:** [What are Props and Transforms in Splunk?](https://infosecwriteups.com/what-are-props-and-transforms-in-splunk-49413b6b9e08)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# What are Props and Transforms in Splunk?


Splunk is a powerful tool for analyzing and visualizing machine-generated data. It uses various configurations to process and enrich data. Among these configurations, “props” and “transforms” play crucial roles. Understanding their functionalities and deployment locations within a Splunk environment is key to optimizing data management and search capabilities.


## What are Props and Transforms in Splunk?


### Props.conf


“Props” in Splunk are configurations defined in the “props.conf” file. This file contains settings that control how Splunk parses and displays incoming data. Key functionalities of “props.conf” include:


- **Data Parsing**: It defines how to break the incoming data into individual events.

- **Timestamp Extraction**: Configuring the correct timestamp for events.

- **Data Enrichment**: Setting event types and adding metadata like source type.

- **Field Extraction**: Identifying and extracting fields at index-time or search-time.

### Transforms.conf


“Transforms” are defined in the “transforms.conf” file. This file is primarily used for:


- **Field Transformations**: Creating new fields from existing data, often using regular expressions.

---

*Originally published on [Medium](https://infosecwriteups.com/what-are-props-and-transforms-in-splunk-49413b6b9e08). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
