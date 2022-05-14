import os
import requests
import pathlib

sendName = "serverSays.txt"

baseSite = "http://localhost:3000"

JWT = None

def sendData(data):
    print(data)
    if os.path.exists(sendName):
        pathlib.Path(sendName).unlink()
    with open(sendName, "w") as f:
        f.write(data)
        f.flush()
        f.close()
        return

def handleGet(data):
    try:
        response = requests.get(data.split(" ")[1])
        sendData(str(response.status_code))
    except:
        pass


def handleRegister(data):
    dictionary = {"userEmail": data.split(" ")[1], "userPassword": data.split(" ")[2]}
    try:
        r = requests.post(f"{baseSite}/api/v1/users/signup/curier", json=dictionary)
        print(r.text)
        dictionary = r.json()
        if(r.status_code == 200):
            prep_data=f"JWT {dictionary['token']}"
            JWT = dictionary['token']
            sendData(prep_data)
    except:
        pass

def handleLogin(data):
    dictionary = {"userEmail": data.split(" ")[1], "userPassword": data.split(" ")[2]}
    try:
        r = requests.post(f"{baseSite}/api/v1/users/login", json=dictionary)
        print(r.text)
        dictionary = r.json()
        if(r.status_code == 200):
            prep_data=f"JWT {dictionary['token']}"
            global JWT
            JWT = dictionary['token']
            print(JWT)
            sendData(prep_data)
    except Exception as e:
        print(e)
        pass

def sendOrder():
    if JWT is None:
        return
    try:
        r = requests.get(f"{baseSite}/api/v1/orders", headers={
            'Authorization': f'Bearer {JWT}'
        })
        print(r.text)
        dictionary = r.json()
        if(r.status_code == 200):
            prep_data=f"ORDER {dictionary['data']['order']['idOrder']} {dictionary['data']['product']['productName']} {dictionary['data']['order']['castig']}"
            sendData(prep_data)
    except Exception as e:
        print(e)
        pass

def handleDelivered(data):
    if JWT is None:
        return
    try:
        r = requests.post(f"{baseSite}/api/v1/orders/deliver/{data.split(' ')[1]}", headers={
            'Authorization': f'Bearer {JWT}'
        })
        print(r.text)
        dictionary = r.json()
        if(r.status_code == 200):
            prep_data=f"ORDER {dictionary['data']['order']['idOrder']} {dictionary['data']['product']['productName']} {dictionary['data']['order']['castig']}"
            sendData(prep_data)
    except Exception as e:
        print(e)
        pass

def handleChosen(data):
    if JWT is None:
        return
    try:
        r = requests.patch(f"{baseSite}/api/v1/orders/{data.split(' ')[1]}", headers={
            'Authorization': f'Bearer {JWT}'
        })
        print(r.text)
        dictionary = r.json()
        if(r.status_code == 200):
            prep_data=f"ORDER {dictionary['data']['order']['idOrder']} {dictionary['data']['product']['productName']} {dictionary['data']['order']['castig']}"
            sendData(prep_data)
    except Exception as e:
        print(e)
        pass

def handleCrashed(data):
    if JWT is None:
        return
    try:
        r = requests.delete(f"{baseSite}/api/v1/orders/{data.split(' ')[1]}", headers={
            'Authorization': f'Bearer {JWT}'
        })
        print(r.text)
        dictionary = r.json()
        if(r.status_code == 200):
            prep_data=f"ORDER {dictionary['data']['order']['idOrder']} {dictionary['data']['product']['productName']} {dictionary['data']['order']['castig']}"
            sendData(prep_data)
    except Exception as e:
        print(e)
        pass