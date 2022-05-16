#pragma once
#include "ProcessLauncher.h"

class Radio {
private:
    static Radio* instance;
    ProcessLauncher *proces_radio;
    int canal_curent;
    void initialize_radio() {
        proces_radio = NULL;
        canal_curent = 0;
    }

public:
    void schimba_canal() {
        if (proces_radio != NULL) {
            proces_radio->stopProcess();
            delete proces_radio;
            proces_radio = NULL;
        }

        canal_curent += 1;
        canal_curent = canal_curent % 4;
        switch (canal_curent) {
        case 1:
            proces_radio = new ProcessLauncher("", "python ./radio.py http://asculta.radiotaraf.ro:7100/");
            proces_radio->launchProcess();
            break;
        case 2:
            proces_radio = new ProcessLauncher("", "python ./radio.py https://live.kissfm.ro/kissfm.aacp");
            proces_radio->launchProcess();
            break;
        case 3:
            proces_radio = new ProcessLauncher("", "python ./radio.py http://petrecere.fmradiomanele.ro:8123/");
            proces_radio->launchProcess();
            break;
        }
    }

    bool stop_radio() {
        return proces_radio->stopProcess();
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

    int getStation() {
        return canal_curent;
    }
};

Radio* Radio::instance = NULL;