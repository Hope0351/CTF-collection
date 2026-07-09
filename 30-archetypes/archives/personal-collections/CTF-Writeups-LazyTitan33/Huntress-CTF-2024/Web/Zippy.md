# Zippy



## My Solution

The about page of the provided website mentions it is using `Razor Pages` and most importantly, it is running with `runtime compilation` which means that Razor views can be edited on the server while the application is running, and changes take effect immediately without needing to redeploy the application.  



We also have the option to upload a ZIP file:  



When uploading a Zip file, I modified the path to the absolute path of the application:  



In the /Browse endpoint we can list the contents of arbitrary directories, including the one of the app and we can confirm that our file was uploaded:  



In this situation, we would need to replace a `.cshtml` file that is rendered by the application. These can be found in the /app/Pages directory:  



My target was the Privacy endpoint since it didn't contain any functionalities required for the application so I couldn't break anything.  

After a few attempts of trying to get RCE I went the simpler route and just read the flag into the page with the code below:  

```html
@page
@using System.IO
@{
    string fileContent = string.Empty;
    fileContent = System.IO.File.ReadAllText("/app/flag.txt");
}
<div>
    <h2>Flag Content:</h2>
    <p>@fileContent</p>
</div>
```

I base64 encoded this and uploaded it then reloaded the /Privacy endpoint.



`flag{a074eb7973c4c718790baefc096654dd}`
