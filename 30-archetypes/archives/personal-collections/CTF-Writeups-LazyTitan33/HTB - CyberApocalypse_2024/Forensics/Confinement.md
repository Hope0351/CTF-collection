# Confinement

## Solution

For this challenge, the description actually helps us a bit, giving us a starting point for the enumeration:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The received file is a `.ad1` file which can be opened with [FTK Imager](https://www.exterro.com/ftk-product-downloads/):  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In the indicated folder, we can see a .hta file and a .korp file which is a non-standard file extension.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The .hta is actually a ransomware note.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In this we can find an ID which we'll save for later.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

A ransomware should normally be detected by Windows Defender, there should be a way for it to have landed on the machine, maybe it was downloaded, maybe it was launched with powershell etc. We need to look at the Windows Event logs and see if they caught something, hopefully they weren't encrypted as well. The default location where the logs are saved is in `%systemroot%\system32\winevt\logs`. 

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Luckily the logs weren't encrypted and we can export them from the image:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Rather than opening these one by one and looking through them manually, we can use this evtx tool to convert them into an xml format that we can plainly read and grep through. I parsed each file and saved it in a different folder with this syntax:  

```bash
for file in logs/*.evtx;do ./evtx_dump-v0.8.0-x86_64-unknown-linux-gnu "$file" > logs_decoded/"${file%.evtx}.xml";done
```
Looking through the Powershell log to see what commands were executed, we notice a `./intel.exe` file being run which is non-standard.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This was run shortly after this browser password decrypter which is a known tool.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

So, they stole the target's browser passwords then encrypted the files. It makes sense for a ransomware attack. Grepping for `intel.exe` we can see that Defender seems to have caught it:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Windows Defender quarantines files in `c:\programdata\microsoft\windows\defender\quarantine`:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

However they are encrypted:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Googling how do decrypt these, we find a helpful github [gist](https://gist.githubusercontent.com/OALabs/30346d78a1fccf59d6bfafab42fbee5e/raw/b2464fc6a1e758f3bff122e10ae3e1cb48a5027c/windows_defender_unquarantine.py):  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)
After we export the quarantined files, we run the script and recover the executable that was ran.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It seems to be a `.Net` binary:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Running strings on it, we can confirm that this was the culprit as we can see the ransom note in it.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Decompiling the executable in dnSpy, we can see an Encrypter and Encrypter.Class:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The Program, uses a `PasswordHasher` and an `Alert` to pass arguments to a `CoreEncrypter`.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Further down we have some hardcoded static strings:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We need to figure out some parameter values in order to create a decryptor. We have `email1` and `email2` as they were hardcoded. Howeveer, Alert is created with the first argument being a `Program.UID`:   
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Which is generated randomly:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Good news is that according to the Alert code, we already have this information.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It's the ID we found already populated in the ransom note:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The `Program.UID` is also used as the first argument for the `passwordHasher` and the salt + alertName are hardcoded values. Email is blank:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Let's try to grab/steal some code and make a Decryptor. I've created a new project in Visual Studio and copied the Alert and PasswordHasher:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Then I wrote this Program do get a file as an argument and we can start decrypting files:  
```C#
using DecrypterApp;
using Encrypter.Class;
using System.Security.Cryptography;

if (args.Length != 1)
{
    Console.WriteLine("Usage: DecrypterApp <encrypted_file>");
    return;
}
Alert alert = new Alert("5K7X7E6X7V2D6F", "fraycrypter@korp.com", "fraydecryptsp@korp.com");
string encryptedFile = args[0];
PasswordHasher passwordHasher = new PasswordHasher();
string password = passwordHasher.GetHashCode("5K7X7E6X7V2D6F", "0f5264038205edfb1ac05fbb0e8c5e94"); 
string validatedAlert = alert.ValidateAlert(); 
string alertName = "ULTIMATUM"; 
string email = ""; 

CoreDecrypter decrypter = new CoreDecrypter(password, validatedAlert, alertName, email);
decrypter.DecryptFile(encryptedFile);

namespace DecrypterApp
{
    class CoreDecrypter
    {
        private string password;
        private string alert;
        private string alertName;
        private string email;

        public CoreDecrypter(string password, string validatedAlert, string alertName, string email)
        {
            this.password = password;
            this.alert = validatedAlert;
            this.alertName = alertName;
            this.email = email;
        }

        public void DecryptFile(string encryptedFile)
        {
            byte[] salt = new byte[]
            {
                0, 1, 1, 0, 1, 1, 0, 0
            };
            Rfc2898DeriveBytes rfc2898DeriveBytes = new Rfc2898DeriveBytes(password, salt, 4953);
            RijndaelManaged rijndaelManaged = new RijndaelManaged();
            rijndaelManaged.Key = rfc2898DeriveBytes.GetBytes(rijndaelManaged.KeySize / 8);
            rijndaelManaged.Mode = CipherMode.CBC;
            rijndaelManaged.Padding = PaddingMode.ISO10126;
            rijndaelManaged.IV = rfc2898DeriveBytes.GetBytes(rijndaelManaged.BlockSize / 8);

            string decryptedFilePath = encryptedFile.Substring(0, encryptedFile.Length - 5); // Remove ".korp" extension
            using (FileStream encryptedFileStream = new FileStream(encryptedFile, FileMode.Open))
            using (FileStream decryptedFileStream = new FileStream(decryptedFilePath, FileMode.Create))
            using (CryptoStream cryptoStream = new CryptoStream(encryptedFileStream, rijndaelManaged.CreateDecryptor(), CryptoStreamMode.Read))
            {
                cryptoStream.CopyTo(decryptedFileStream);
            }

            Console.WriteLine("File decrypted successfully.");
        }
    }
}
```
The directory specified by the challenge description contains only 1 .korp file so we can start with that one.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We successfully decrypted the file and got a functional Excel in return which we can open and actually get the flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This was a hard challenge worthy of the name. Once I thought of the quarantine, the name of the challenge made sense and I knew I was on the right track. Overall, it was a well designed challenge that made complete sense from start to finish, it was realistic and enjoyable to crack.

`HTB{2_f34r_1s_4_ch01ce_322720914448bf9831435690c5835634}`

