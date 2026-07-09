# TimeOff


Attachment: [challenge.zip](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Writeup

This website allows me to make a request for time off. It's a POST request that also allows me to upload a file. However, the file_name parameter is vulnerable to Path Traversal according to the [Snyk](https://docs.snyk.io/scm-ide-and-ci-cd-integrations/snyk-ide-plugins-and-extensions/visual-studio-code-extension) Extension for Visual Studio Code :wink::



So I just read the flag from the path indicated in the Dockerfile:  



The 302 redirect will lead me directly to the flag:  

flag{52948d88ee74b9bdab130c35c88bd406}
