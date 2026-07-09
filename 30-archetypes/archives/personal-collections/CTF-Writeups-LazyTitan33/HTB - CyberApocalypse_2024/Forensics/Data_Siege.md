# Data Siege

## Enumeration
We get a wireshark capture and have a look at `Statistics` -> `Protocol Hierarchy` and see some data:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Following TCP stream, we see at stream 1 something about Java and springframework:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Continuing to follow the stream, we find a Powershell command having downloaded a weird executable file.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Luckily we've captured that file too so we can simply export it from the capture to look at later:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

TCP Stream 5 contains a lot of Base64 strings, some shorter, some longer. They can't be decoded to plaintext so they must be encrypted.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Further down we also find another powershell command with a Base64 encoded payload:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution
Decoding the Powershell command, we find the 3rd part of the flag. Interesting. We're starting from the end, sure.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The Executable file is thankfully a .Net binary which makes it easier to analyse.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We see the program having a Decrypt function which will be handy for decryptying the Base64 blobs, I'm sure:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can also find a hardcoded encryptKey.. nice:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Hippity-hoppity, your code is now my property. I don't want to run their code/executable so I made my own. I've grabbed their decryption code, modified it a little to be able to pass arguments to it and got this code which I compiled into an executable:  

```C#

using System.Security.Cryptography;
using System.Text;

namespace DecryptApp
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.WriteLine("Usage: DecryptApp <cipher_text>");
                return;
            }

            string cipherText = args[0];
            string decryptedText = Decrypt(cipherText);
            Console.WriteLine("Decrypted text: " + decryptedText);
        }

        public static string Decrypt(string cipherText)
        {
            string result;
            try
            {
                string encryptKey = "VYAemVeO3zUDTL6N62kVA";
                byte[] array = Convert.FromBase64String(cipherText);
                using (Aes aes = Aes.Create())
                {
                    Rfc2898DeriveBytes rfc2898DeriveBytes = new Rfc2898DeriveBytes(encryptKey, new byte[]
                    {
                        86,
                        101,
                        114,
                        121,
                        95,
                        83,
                        51,
                        99,
                        114,
                        51,
                        116,
                        95,
                        83
                    });
                    aes.Key = rfc2898DeriveBytes.GetBytes(32);
                    aes.IV = rfc2898DeriveBytes.GetBytes(16);
                    using (MemoryStream memoryStream = new MemoryStream())
                    {
                        using (CryptoStream cryptoStream = new CryptoStream(memoryStream, aes.CreateDecryptor(), CryptoStreamMode.Write))
                        {
                            cryptoStream.Write(array, 0, array.Length);
                            cryptoStream.Close();
                        }
                        cipherText = Encoding.Default.GetString(memoryStream.ToArray());
                    }
                }
                result = cipherText;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Console.WriteLine("Cipher Text: " + cipherText);
                result = "error";
            }
            return result;
        }
    }
}
```

I started passing those base64 strings to my program and soon enough, found the 1st part of the flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Some decrypted base64 strings later, I also find part 2:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{c0mmun1c4710n5_h45_b33n_r3570r3d_1n_7h3_h34dqu4r73r5}`
