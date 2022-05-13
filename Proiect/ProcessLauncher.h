#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>
class ProcessLauncher {
private:
    PROCESS_INFORMATION pi;
    std::string pathToExecutable;
    std::string cmd;

public:
    ProcessLauncher(std::string pathToExecutable = "", std::string cmd = "", bool launch = false) {
        this->pathToExecutable = pathToExecutable;
        this->cmd = cmd;
        if (launch)
            launchProcess();
    }

    bool launchProcess() {
        STARTUPINFO si;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        std::string new_cmd;
        char* app;
        char* args;

        if (pathToExecutable.size() != 0) {
            new_cmd = pathToExecutable + " " + cmd;
            app = (char*)pathToExecutable.c_str();
        }
        else {
            new_cmd = cmd;
            app = NULL;
        }

        int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, new_cmd.c_str(), new_cmd.size(), NULL, 0);

        LPWSTR widestr = new WCHAR[bufferlen + 1];

        ::MultiByteToWideChar(CP_ACP, 0, new_cmd.c_str(), new_cmd.size(), widestr, bufferlen);

        widestr[bufferlen] = 0;

        // Do something with widestr

        if (!CreateProcess(NULL,   // No module name (use command line)
            widestr,        // Command line
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            FALSE,          // Set handle inheritance to FALSE
            0,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory
            &si,            // Pointer to STARTUPINFO structure
            &pi)           // Pointer to PROCESS_INFORMATION structure
            ) {
            printf("CreateProcess failed (%d).\n", GetLastError());
            delete[] widestr;
            return false;
        }
        delete[] widestr;
        return true;
    }

    bool isActive() {
        if (pi.hProcess == NULL) {
            return false;
        }
        DWORD exitCode;
        GetExitCodeProcess(pi.hProcess, &exitCode);
        if (exitCode == STILL_ACTIVE) {
            return true;
        }
        return false;
    }

    bool stopProcess() {
        try {
            TerminateProcess(pi.hProcess, 1);
            WaitForSingleObject(pi.hProcess, INFINITE);
        }
        catch (std::exception s) {
            return true;

        }
        return true;
    }
};
