# :globe_with_meridians: Insecure Deserialization 😈🐝

---

# Insecure Deserialization 😈🐝

*Photo by [Stephen Radford](https://unsplash.com/@steve228uk?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

Serialization is the act of transforming objects from an internal representation to a stream of characters or bytes. The representation of the serialized object should be platform- and language-independent. Data is serialized and deserialized in applications to store or transport it. In web applications, JSON or XML is often used for data exchange by many APIs and protocols. File formats like PNG/GIF/JPEG/MPEG use XML to store metadata. YAML became extremely popular for configuration files, e.g. in [Cloudformation templates](https://docs.aws.amazon.com/AWSCloudFormation/latest/UserGuide/template-formats.html) or [GitlabCI configuration files](https://docs.gitlab.com/ee/ci/yaml/).

Some file formats allow you to do more than just (de)serializing basic data types. For example, imagine that you want to set up a CI pipeline. You might have one step for executing unit tests, one step for checking the types, one for linting. All of those steps might require installing the same set of dependencies. Instead of repeating yourself, you want to use references. You define a dictionary once and copy it in many places. References allow a human to read, write, and modify the file quickly while the machine simply has the same value(s) in multiple places.

Another powerful feature is to include external entities. In the simplest case, this means that you want to include another file. For example, you could have a logging configuration that you want to use in multiple places. In more extreme cases, the external…

---
