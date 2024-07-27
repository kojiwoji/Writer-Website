import requests
import json

response = requests.post("https://api.github.com")
print(response.json())
