# :link: A Comprehensive Approach For Testing For Sql Injection Vulnerabilities 23C8772Ff

---

This guide will take you through the step-by-step process of testing for SQL injection vulnerabilities.

- Select Parameters for Testing

Before diving into SQL injection testing, identify the parameters you want to test. These parameters can be found in various places within a HTTP request that is sent to an application server:

*URL query*

*POST bodyHeadersCookies*

Choose any parameter, but it’s common to start with integer parameters. These are often used in queries and can be more susceptible to SQL injection.

2. Perform Basic Math Tests

If the selected parameter is an integer, try performing basic math operations on it within the input:

Example: `user_id=1338-1`

If an SQL injection vulnerability exists, you might observe unexpected results or errors in the response.

3. Add Common Symbols

Next, add common SQL injection symbols to the parameter and monitor the response status. Some symbols to test include:

- Single quote (`'`)

- Double quote (`"`)

- Semicolon (`;`)

If you receive an error response, this could be a sign of an SQL injection vulnerability.

## Get Dhanesh Dodia - HeyDanny’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

4. Test for Multiple Symbols

Continue testing by adding more than one symbol to the parameter to see how the application responds. For SQL, the escape character for a single quote is another single quote, and for a double quote, it’s another double quote.

Examples:

- `login=admin` (status: 200)

- `login=admin'` (status: 500)

- `login=admin''` (status: 200)

5. Perform SQL Query Functions

Try injecting SQL query functions into the parameter. Depending on the type of parameter (integer or text), use appropriate functions:

Integer Parameter:

- `user_id=1337 AND 1=1` (status: 200)

- `user_id=1337 AND 2=1` (status: 500)

Text Parameter:

- `login=admin' AND 'A'='A` (status: 200)

- `login=admin' AND 'A'='B` (status: 500)

JSON Integer Parameter:

- `{"user_id":"1337 AND 1=1"}` (status: 200)

6. Combine SQL Query Functions with Comments

To hide your malicious payload, add comments at the end of the parameter:

Examples:

- Integer Parameter: `user_id=1337 AND 1=1 --` (status: 200)

- Text Parameter: `login=admin' AND 'A'='A' --` (status: 200)

- JSON Integer Parameter: `{"user_id":"1337 AND 1=1 --"}` (status: 200)

- JSON Text Parameter: `{"login":"admin' AND 'A'='A' --"}` (status: 200)

7. Use Specialized Tools for Further Testing

Once if the vulnerable parameter is identified, exploitation could be done with specialized tools like [SQLMap](https://github.com/sqlmapproject/sqlmap)or [Ghauri](https://github.com/r0oth3x49/ghauri). These tools can automate the testing process and provide detailed results.

After holding a proper understanding of what input fields needs to be tested, the process of crawling, collecting different HTTP requests and testing input fields could be done in a automated fashion. Several tools like [waybackurl](https://github.com/tomnomnom/waybackurls), [gau](https://github.com/lc/gau), [Burpsuite](https://portswigger.net/burp/communitydownload)(All requests from the History tab), [Nuclei](https://github.com/projectdiscovery/nucleihttps://github.com/projectdiscovery/nuclei), [SQLMap](https://github.com/sqlmapproject/sqlmap)or [Ghauri](https://github.com/r0oth3x49/ghauri).

---
