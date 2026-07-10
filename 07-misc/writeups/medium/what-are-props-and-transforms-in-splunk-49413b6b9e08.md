# :game_die: What are Props and Transforms in Splunk?

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
