import os
import pathlib
import requests

files = ["clientSays"]
sendName = "serverSays"

baseSite = "http://localhost:5000"

def sendData(data):
    if os.path.exists(sendName):
        return
    with open(sendName, "w") as f:
        f.write(data)
    return

print("Backend started")
while True:
    for file in files:
        try:
            if not os.path.exists(file):
                raise FileNotFoundError
            data = None
            with open(file, "r") as f:
                data = f.read()
            if data:
                method = data.split(" ")[0]
                print(data)

                if(method == "GET"):
                    response = requests.get(data.split(" ")[1])
                    sendData(str(response.status_code))
                if(method == "REGISTER"):
                    dictionary = {"userEmail": data.split(" ")[1], "userPassword": data.split(" ")[2]}
                    r = requests.post(f"{baseSite}/api/v1/users/signup", json=dictionary)
                    dictionary = r.json()
                    if(r.status_code == 200):
                        prep_data=f"JWT {dictionary['token']}"
                        sendData(prep_data)

                if(method == "LOGIN"):
                    dictionary = {"userEmail": data.split(" ")[1], "userPassword": data.split(" ")[2]}
                    r = requests.post(f"{baseSite}/api/v1/users/login", json=dictionary)
                    dictionary = r.json()
                    if(r.status_code == 200):
                        prep_data=f"JWT {dictionary['token']}"
                        sendData(prep_data)

            pathlib.Path(file).unlink()
        except FileNotFoundError:
            pass
        

    