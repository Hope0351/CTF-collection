import requests
from bs4 import BeautifulSoup
import os
import sys


def login_and_upload(username, password, file_path, login_url, upload_url):
    # Create a session to maintain cookies
    session = requests.Session()

    # Login to the website
    login_data = {
        'username': username,
        'password': password,
        # Add any other required login fields here
    }
    response = session.post(login_url, data=login_data)

    # Check if login was successful
    if response.status_code == 200:
        print(f"Login successful for user: {username}")
    else:
        print(f"Login failed for user: {username}")
        return

    # Prepare the file for upload
    files = {'file': open(file_path, 'rb')}

    # Upload the file
    upload_data = {
        # Add any additional data required for file upload
    }
    response = session.post(upload_url, files=files, data=upload_data)
    print(response)
    #print(response.text[:100])

    # Check if upload was successful
    if response.status_code == 200:
        print(f"File uploaded successfully: {file_path}")
    else:
        print(f"File upload failed: {file_path}")

    # Close the file
    files['file'].close()


def login_and_upload2(username, password, file_path, login_url, upload_url):
    from bs4 import BeautifulSoup
    import requests

    session = requests.Session()

    # Step 1: GET login page to get CSRF token
    login_page = session.get(login_url)
    soup = BeautifulSoup(login_page.text, "html.parser")
    csrf_token = soup.find("input", {"name": "csrf_token"})["value"]

    # Step 2: POST login
    login_data = {
        "username": username,
        "password": password,
        "csrf_token": csrf_token
    }
    response = session.post(login_url, data=login_data)

    if response.status_code != 200 or "Logout" not in response.text:
        print("Login failed")
        return

    print("Login successful")

    # Step 3: GET upload page to get CSRF for upload
    upload_page = session.get(upload_url)
    soup = BeautifulSoup(upload_page.text, "html.parser")
    csrf_token = soup.find("input", {"name": "csrf_token"})["value"]

    # Step 4: POST file upload with CSRF token
    with open(file_path, "rb") as f:
        files = {'file': f}
        data = {'csrf_token': csrf_token}
        response = session.post(upload_url, files=files, data=data)

    if response.status_code == 200 and "File uploaded successfully" in response.text:
        print("Upload successful")
    else:
        print("Upload failed")
        print("Response URL:", response.url)
        print(response.text[:500])


usernames = {
    "mmm": [1, ""],
    "friendly-maltese-citizens": [2, ""],
    "kalmarunionen": [3, ""],
    "repokemonedcollections": [4, ""],
    "blue-water": [5, ""],
    "superdicecode": [6, ""],
    "mhackeroni": [7, ""],
    "nu1l": [8, ""],
    "shellphish": [9, ""],
    "kuk-hofhackerei": [10, ""],
    "this-years-organizers": [11, ""],
    "cold-fusion": [12, ""]
}

user_data = []
for username, (userid, password) in usernames.items():
    file_path = sys.argv[1]+f"/{userid}.in"
    user_data.append({'username': username, 'userid': userid, 'password': password, 'file': file_path})

login_url = "http://"+sys.argv[2]+"/login"
upload_url = "http://"+sys.argv[2]+"/upload"

EMPTY_FNAME = "/tmp/empty.in"
with open(EMPTY_FNAME,"wb") as fp:
    pass

for user in user_data:
    print(user['file'])
    if not os.path.exists(user['file']):
        user['file'] = EMPTY_FNAME
    login_and_upload(user['username'], user['password'], user['file'], login_url, upload_url)

