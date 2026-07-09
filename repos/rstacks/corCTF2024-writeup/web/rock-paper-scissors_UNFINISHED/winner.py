import requests

url = "https://rock-paper-scissors-4ef4fbb1cb6adc7c.be.ax/play"

headers = {
  "Cookie": "session=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6Im5vcGUiLCJnYW1lIjoiNTIyOTM1NjhiZWQxY2VhYyIsImlhdCI6MTcyMjExODMyOH0.7rXan534U0ZmeTMzaKgBpisi28Rpy94ryK7yvEH2Mg8",
  "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.5790.171 Safari/537.36",
  "Content-Type": "application/json"
}

move = "🪨"
data = {"position": move}
while True:
  requests.post(url, headers=headers, json=data)
