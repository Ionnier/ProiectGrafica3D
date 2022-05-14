#pragma once
#include "ProcessLauncher.h"

class Radio {
private:
    static Radio* instance;
    ProcessLauncher proces_radio;
    bool initialize_radio() {
        proces_radio.stopProcess();
        proces_radio = *(new ProcessLauncher("", "python ./radio.py http://asculta.radiotaraf.ro:7100/"));
        proces_radio.launchProcess();
        printf("%d\n", proces_radio.isActive());
        return proces_radio.isActive();
    }

public:
    void schimba_canal(int canal) {
        switch (canal) {

        }
    }

    bool stop_radio() {
        return proces_radio.stopProcess();
    }

    virtual ~Radio() {
        stop_radio();
    }

    static Radio* getInstance() {
        if (!instance) {
            instance = new Radio();
            instance->initialize_radio();
        }
            
        return instance;
    }
};

Radio* Radio::instance = NULL;