# :globe_with_meridians: Create Firefox options object

> **Original Source:** [Create Firefox options object](https://infosecwriteups.com/dark-web-scraping-101-tools-techniques-and-challenges-be73bbdccc58)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

*Coding In The Zone GIF by nounish*


Now that we’ve completed all the necessary configurations, let’s jump into the Code. We’ll use [Selenium](https://selenium-python.readthedocs.io/)with Python to automate the Scraping process and interact with the web browser seamlessly.

>

Selenium is a tool for automating web browsers, enabling script-based interaction with web pages across all major browsers and operating systems. It supports multiple programming languages, including Python, allowing us to control browsers and perform automation tasks just as a human would.


Ensure that Python is already installed on your computer, and then to install Selenium, simply run the following command:


```
pip install selenium
```


To kick things off, we’ll begin by importing the necessary modules and Classes that will help us on this mission. First, we’ll import `Options` from `selenium.webdriver.firefox`, which will allow us to create our Firefox options object and manage various settings, such as using a specific profile. Next, we'll import `webdriver` from Selenium, which serves as our browser driver. With these imports, we're ready to start our journey.


```
from selenium import webdriver
from selenium.webdriver.firefox.options import Options
```


So let’s create a Firefox options object


```
options = Options()
```


Next, copy the path to the Firefox profile you want to use .


## Get zerOiQ’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


To find your existing Firefox profile, especially if you’re already logged in, go to the Firefox search bar, type `about:profiles`, and select the path to your Firefox profile.


In my case


```
options.profile = r"C:\Users\AZM\AppData\Roaming\Mozilla\Firefox\Profiles\qmwngl3n.default-release-5431908913213"
```


Now we’ll set up the Firefox WebDriver with our desired options


```
driver = webdriver.Firefox(options=options)
```


Finally, we need to choose our desired website to explore.”


```
driver.get("https://Website.com")
```


Now, the time has come to navigate into the dark web , and here is the complete code .


```
from selenium import webdriver
from selenium.webdriver.firefox.options import Options

# Create Firefox options object
options = Options()

#Firefox profile you want to use
options.profile = r"C:\Users\AZM\AppData\Roaming\Mozilla\Firefox\Profiles\qmwngl3n.default-release-5431908913213"

# Initialize the Firefox driver with the specified options
driver = webdriver.Firefox(options=options)

try:
# Navigate to the desired website
driver.get("https://duckduckgogg42xjoc72x3sjasowoarfbgcmvfimaftt6twagswzczad.onion/")
except Exception as e:
print(f"An error occurred: {str(e)}")
```


Here’s an additional code snippet example using GeckoDriver :


```
from selenium import webdriver
from selenium.webdriver.firefox.service import Service
from selenium.webdriver.firefox.options import Options

# Create Firefox options object
options = Options()

#Firefox profile you want to use
options.profile = r"C:\Users\AZM\AppData\Roaming\Mozilla\Firefox\Profiles\qmwngl3n.default-release-5431908913213"

#Geckodriver Path
geckodriver_path = r'C:\Projects\scraping\geckodriver.exe'

# Create a Service object with the path to Geckodriver
service = Service(executable_path=geckodriver_path)

# Initialize the Firefox driver with the specified Service and options
driver = webdriver.Firefox(service=service, options=options)

try :
# Navigate to the desired website
driver.get("https://duckduckgogg42xjoc72x3sjasowoarfbgcmvfimaftt6twagswzczad.onion/")
except Exception as e:
print(f"An error occurred: {str(e)}")
```


>

An important thing to note:


Both snippets ultimately perform the same task because they both end up using Geckodriver to interact with Firefox. The only difference is whether you specify the Geckodriver’s path manually or let Selenium handle it automatically .


Now that we’ve automated Firefox to visit DuckDuckGo, it’s a great start. But there’s still a long way to go . Let’s dive into a dark web forum .


Once we’ve navigated to the `XSS.is` as an *Example site*, it’s important to wait for the element we want to interact with , like a button or link , to load. Here’s how you can do that:


```
#Waiting the presence of the element needed
search_box = WebDriverWait(driver, 10).until(
EC.presence_of_element_located((By.CLASS_NAME, "element_NAME"))
)
```


To click on a specific button or fill in particular inputs, you’ll need to identify its CLASS_NAME, ID, CSS_SELECTOR, NAME ,TAG_NAME OR any other unique indicator. This allows us to target the element precisely and perform the desired action on it .


Remember to import the essential modules or Classes:


```
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
```


These will help ensure everything runs smoothly before we start clicking around .


Now, let’s automate the Login process. I’ll assume you already have an account; if not, you can create one. We’ll use the identified names to fill in the login details .


Once the element is present, the first action is to Locate it using its NAME and then send data to the input field. Here’s how you can do it


```
# Locate the email input field using its NAME
Email_input = driver.find_element(By.NAME, 'login')

# Send the email to the input field
Email_input.send_keys('user@user.com')

# Locate the Password input field using its NAME
Password_input = driver.find_element(By.NAME, 'password')

# Send a password to the input field
Password_input.send_keys('P@$$w0rd')

# Locate the Login Button using its CLASS_NAME
Login_Button = driver.find_element(By.CLASS_NAME, 'button')

#Click On it
Login_Button.click()
```


Once logged in, we’ll identify the data we need to extract, including the specific room, category, and other details. Then, we’ll search for the relevant elements and follow the same process we used earlier.


To keep it simple, we’ll use an example to demonstrate the essential classes and modules. You can then customize this approach to suit your needs.


```
from bs4 import BeautifulSoup
import time

while True:
# Get the page source and parse it with BeautifulSoup
page_source = driver.page_source
soup = BeautifulSoup(page_source, 'html.parser')

# Find all table rows with class "inline_row"
rows = soup.find_all('tr', class_='inline_row')
for row in rows:
# Find all table data cells in the row
columns = row.find_all('td')
if len(columns) > 3:
# Extract the fourth cell (index 3) and find all links
fourth_td = columns[3]
link_elements = fourth_td.find_all('a')
for link_element in link_elements:
# Check if any link text contains target words
if any(word in link_element.text for word in target_words):
# Extract the link URL from the third cell (index 2)
third_td = columns[2]
div_tag = third_td.find('div')
span_tag = div_tag.find('span')
link = span_tag.find('a')['href']

# Open the link in a new browser tab
driver.execute_script(f"window.open('{link}', '_blank');")
driver.switch_to.window(driver.window_handles[-1])

try:
# Wait for the post content to load and get its HTML
post_content_html = WebDriverWait(driver, 10).until(
EC.presence_of_element_located((By.CLASS_NAME, 'post_whole'))
).get_attribute('outerHTML')

# Parse the content with BeautifulSoup and extract text
soup = BeautifulSoup(post_content_html, 'html.parser')
post_content = soup.get_text(separator="\n")

except Exception as e:
# Handle errors during content extraction
print(f"An error occurred while scraping content: {str(e)}")
post_content = ""

# Append the extracted content to a text file
with open("scraped_data.txt", "a", encoding="utf-8") as file:
file.write(post_content + "\n\n" + "="*50 + "\n\n")

# Close the current tab and switch back to the original tab
driver.close()
driver.switch_to.window(driver.window_handles[0])

# Handle pagination and click on the "Next" button
try:
next_button = WebDriverWait(driver, 10).until(
EC.element_to_be_clickable((By.CLASS_NAME, 'pagination_next'))
)
next_button.click()
time.sleep(3) # Wait for the next page to load
except Exception as e:
# Handle errors or end of pagination
print(f"No more pages or an error occurred: {str(e)}")
break

```


The code performs automated web scraping with pagination using *Selenium *and *BeautifulSoup*. It continuously retrieves the page source and parses it with BeautifulSoup to locate table rows with the class `inline_row`. For each row, it checks if the fourth column contains links with text matching any target words. If a match is found, it extracts the URL from the third column and opens it in a new browser tab. After waiting for a specific element (`post_whole`) to load, it extracts the page content, saves it to a text file, and then closes the tab, returning to the main page. The script then looks for a Next button to navigate to the subsequent page. If no such button is found or an error occurs, it breaks the loop and terminates the scraping process.


This approach enables the collection of data across multiple pages by managing browser tabs and handling pagination.

>

we’ve covered the essentials of configuring Firefox for dark web scraping, setting up Selenium with GeckoDriver, and automating the login process. We demonstrated how to locate and interact with elements, extract data, and navigate the dark web effectively. With these tools and techniques, you can now adapt and expand your scraping tasks to fit your specific needs.


But here’s where the challenge intensifies: many dark web forums employ multiple layers of protection and anti-scraping mechanisms, including *CAPTCHAs*, which can make scraping tasks extremely difficult or even nearly impossible. While there are existing solutions to bypass some CAPTCHAs, such as [ZENROWS](https://www.zenrows.com/captcha/)and [CAPSOLVER](https://www.capsolver.com/)* .*


Some are so complex that automatic solutions fall short. In my opinion, the best approach might involve developing an *AI model* specifically designed to bypass these challenges. However, this remains a formidable task.


Adding to the difficulty, forum admins frequently update their CAPTCHAs with new, creative designs, making it an exciting and ongoing challenge to devise innovative methods for overcoming these barriers.

---

*Originally published on [Medium](https://infosecwriteups.com/dark-web-scraping-101-tools-techniques-and-challenges-be73bbdccc58). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
