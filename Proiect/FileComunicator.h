#pragma once
#include <fstream>
#include "ProcessLauncher.h"
#include <string>
class FileComunicator {
private:
    static FileComunicator* instance;
    ProcessLauncher backend;
    std::string secretKey;

    bool initialise_backend() {
        backend.stopProcess();
        backend = *(new ProcessLauncher("", "python ./backend.py"));
        backend.launchProcess();
        printf("%d\n", backend.isActive());
        return backend.isActive();
    }

    bool stop_backend() {
        return backend.stopProcess();
    }

    FileComunicator() {
        secretKey = generateRandomString(100);
        initialise_backend();
    }

    bool checkFileOpen(std::string name) {
        std::ifstream f(name);
        return f.is_open();
    }

    void sendData(std::string data) {
        if (!backend.isActive())
            return;
        std::string fileName = "clientSays";
        if (checkFileOpen(fileName))
            return;
        std::ofstream f;
        f.open(fileName);
        f << data;
        f.close();
    }

public:

    virtual ~FileComunicator() {
        stop_backend();
    }

    static char randomChar() {
        char letter = rand() % 25 + 65;
        if (rand() % 2 == 1)
            letter += 32;
        return letter;
    }

    static std::string generateRandomString(int n = 10) {
        std::string aux;
        for (int i = 0; i < n; i++)
            aux.push_back(randomChar());
        return aux;
    }

    static FileComunicator* getInstance() {
        if (!instance)
            instance = new FileComunicator();
        return instance;
    }

    std::string recieveData() {
        std::string asd = "";
        if (!backend.isActive())
            return asd;
        std::ifstream f;
        f.open("serverSays.txt");
        if (!f.is_open()) {
            return "";
        }
        std::string data;
        f >> data;
        if (data == "JWT") {
            f >> data;
            GameState::getInstance()->setJWT(data);
            MainMenu::initialise();
        }
        if (data == "ORDER" && GameState::getInstance()->getState() == State::Started) {
            int id;
            f >> id;
            f >> data;
            int castig;
            f >> castig;
            GameState::getInstance()->addOrder(id, data, castig);
        }
        f.close();
        remove("serverSays.txt");
        return data;
    }

    void sendGetRequest() {
        std::string data = "GET https://www.google.ro";
        sendData(data);
    }

    void sendRegisterRequest(std::string username, std::string password) {
        std::string data = "REGISTER ";
        data += username;
        data += " ";
        data += password;
        sendData(data);
    }

    void sendLoginRequest(std::string username, std::string password) {
        std::string data = "LOGIN ";
        data += username;
        data += " ";
        data += password;
        sendData(data);
    }

    void sendOrderRequest() {
        std::string data = "GETORDER";
        sendData(data);
    }

    void sendCrashedOrder() {
        if (GameState::getInstance()->getState() == State::Delivering) {
            int id = GameState::getInstance()->getActiveOrderId();
            std::string data = "";
            data += "CRASHED ";
            data += std::to_string(id);
            sendData(data);
        }
    }

    void sendStartingDeliver() {
        if (GameState::getInstance()->getState() == State::Delivering) {
            int id = GameState::getInstance()->getActiveOrderId();
            std::string data = "";
            data += "CHOSEN ";
            data += std::to_string(id);
            sendData(data);
        }
    }


    void sendDelivered() {
        if (GameState::getInstance()->getState() == State::Delivering) {
            int id = GameState::getInstance()->getActiveOrderId();
            std::string data = "";
            data += "DELIVERED ";
            data += std::to_string(id);
            sendData(data);
        }
    }

};
FileComunicator* FileComunicator::instance = NULL;