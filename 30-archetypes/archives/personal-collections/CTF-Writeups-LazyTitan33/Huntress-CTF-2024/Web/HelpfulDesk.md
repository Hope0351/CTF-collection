# HelpfulDesk



## My Solution

When accessing the page, we get a login screen with a yellow banner saying that a Security Update is required:  



Looking at the security bulletin, we find a Critical Severity update in version 1.2. So we download the source code, as well as the source code for v1.1 so we can see the difference and check out what they patched:  



It's a .Net application and in the `SetupController` for version 1.1 we see it checking the `/Setup/SetupWizard` endpoint:  



However, in version 1.2, they are now trimming the `/` at the end of the URL, if there is one.  



We also notice where the flag is supposed to be, in one of the Clients of the service.  



Considering they are running the unpatched version, we can navigate to `/setup/setupwizard/` with a slash at the end, and we end up on the Setup Wizard where we can setup an administrator account:  



We access the client we noticed in the source code and download the flag.  



`flag{03a6f458b7483e93c37bd94b6dda462b}`
