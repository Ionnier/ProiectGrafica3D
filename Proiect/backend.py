import os
import pathlib
import requests
from butilsBackend import *

files = ["clientSays"]

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
                    handleGet(data)
                if(method == "REGISTER"):
                   handleRegister(data)
                if(method == "LOGIN"):
                    handleLogin(data)
                if(method == "DELIVERED"):
                    handleDelivered(data)
                if(method == "CHOSEN"):
                    handleChosen(data)
                if(method == "CRASHED"):
                    handleCrashed(data)
                if(method == "GETORDER"):
                    sendOrder()
            pathlib.Path(file).unlink()
        except FileNotFoundError:
            pass

    