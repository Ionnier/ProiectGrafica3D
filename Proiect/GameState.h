#pragma once
#include<gl/freeglut.h>
#include "Utils2.h"
#include "Comanda.h"
#include <string>
#include <fstream>

enum class Status { FREE_ROAM, WAITING_FOR_ORDER, DELIVERING_ORDER, NONE };
enum class State { Started, Game_Over, Main_Menu, Stats, Selecting_Order, Delivering, Entering_Text };
enum class Reason { Police, Crash, Cold, None };

class GameState {
private:
    static GameState* instance;
    State current_state;
    Reason game_over_reason;
    Status status;
    std::string userName;
    std::string password;
    std::vector<Comanda> comenzi;
    GameState() {
        this->setMainMenu();
        status = Status::FREE_ROAM;
        activeOrder = 0;
    }
    int activeOrder;
    bool enteringPassword = false;
    bool isLogin;
    std::string JWT;

    void drawOrder(int i) {
        float left_x = 0;
        float left_y = WINDOW_HEIGHT - 150 * (i + 1);
        float right_x = 0 + 150;
        float right_y = WINDOW_HEIGHT - 150 * i;
        RenderString(10, WINDOW_HEIGHT - 150 * (i + 1) + 40, comenzi[i].getNume(), Shade::White);
        RenderString(10, WINDOW_HEIGHT - 150 * (i + 1) + 10, std::to_string(comenzi[i].getCastig()), Shade::White);

        Textures::getInstance()->enableTexture(comenzi[i].getTextura());
        glBegin(GL_QUADS);
        glTexCoord2f(1.0, 1.0); glColor3f(1.0, 0.1, 0.1);  glVertex2f(left_x + 75, (left_y + right_y) / 2);
        glTexCoord2f(1.0, 0.0); glColor3f(0.1, 1.0, 0.1);  glVertex2f(left_x + 75, right_y);
        glTexCoord2f(0.0, 0.0); glColor3f(1.0, 1.0, 0.1); glVertex2f(right_x, right_y);
        glTexCoord2f(0.0, 1.0); glColor3f(0.0, 0.1, 1.0); glVertex2f(right_x, (left_y + right_y) / 2);
        glEnd();

        if (i != activeOrder || GameState::getInstance()->getState() != State::Selecting_Order) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
            glShadeModel(GL_FLAT);
        }

        Colors::getInstance()->setColor(Shade::Black);

        glBegin(GL_QUADS);
        glVertex2f(left_x, left_y);
        glVertex2f(right_x, left_y);
        glVertex2f(right_x, right_y);
        glVertex2f(left_x, right_y);
        glEnd();

        if (i != activeOrder || GameState::getInstance()->getState() != State::Selecting_Order) {
            glDisable(GL_BLEND);
        }
    }
public:
    double total_drum = 10000;
    double progres = 0;
    double temperatura_mancare = 100;

    static float WINDOW_HEIGHT;
    static float WINDOW_WIDTH;
    static GameState* getInstance() {
        if (!instance)
            instance = new GameState;
        return instance;
    }
    int getActiveOrderId() {
        return comenzi[0].getId();
    }
    State getState() {
        return this->current_state;
    }
    Reason getGameOverReason() {
        return this->game_over_reason;
    }
    void setEnteringText(bool isLogin) {
        this->isLogin = isLogin;
        current_state = State::Entering_Text;
    }

    void toggleOrders() {
        switch (current_state) {
        case State::Started: current_state = State::Selecting_Order; break;
        case State::Selecting_Order: current_state = State::Started; break;
        }
    }

    void setStatsScreen() {
        resetGameState();
        this->current_state = State::Stats;
    }
    void setGameOver(Reason reason) {
        //GameState::getInstance()->save_time_spent_in_game();
        resetGameState();
        this->game_over_reason = reason;
        this->current_state = State::Game_Over;
        //mciSendString(L"open \".\\sunete\\game_over.mp3\" type mpegvideo alias game_over", NULL, 0, NULL);
        //mciSendString(L"play game_over repeat", NULL, 0, NULL);
    }
    void setMainMenu() {
        //PlaySound(NULL, NULL, SND_ASYNC | SND_FILENAME);
        //mciSendString(L"close radio", NULL, 0, NULL);
        //mciSendString(L"close game_over", NULL, 0, NULL);
        this->current_state = State::Main_Menu;
        //PlaySound(L".\\sunete\\glovo.wav", NULL, SND_ASYNC | SND_FILENAME);
    }
    void setStartGame() {
        //PlaySound(NULL, NULL, SND_ASYNC | SND_FILENAME);
        //mciSendString(L"close game_over", NULL, 0, NULL);
        //mciSendString(L"open \".\\sunete\\trafic.mp3\" type mpegvideo alias sunet_ambient", NULL, 0, NULL);
        //mciSendString(L"play sunet_ambient repeat", NULL, 0, NULL);
        //schimba_muzica();
        //rsj = 0; rdj = 0; rss = 0; rds = 0.0; j = 0.0; ok = 1; progres = 0; temp_mancare = 100;
        resetGame();
        this->game_over_reason = Reason::None;
        this->current_state = State::Started;
        this->status = Status::FREE_ROAM;
        clearOrders();
        //GameState::getInstance()->prepare_time_start();
    }

    void setDelivering() {
        this->current_state = State::Delivering;
        status = Status::DELIVERING_ORDER;
    }

    void resetGameState() {
        //PlaySound(NULL, NULL, SND_ASYNC | SND_FILENAME);
        //mciSendString(L"close sunet_ambient", NULL, 0, NULL);
        //mciSendString(L"close radio", NULL, 0, NULL);
        //rsj = 0; rdj = 0; rss = 0; rds = 0.0; j = 0.0; ok = 1; progres = 0; temp_mancare = 100;
        //oprit_de_politie = false;
    }

    static void quitGame() {
        //GameState::getInstance()->save_data();
        glutLeaveMainLoop();
    }

    Status getStatus() { return status; }
    void setStatus(Status status) { this->status = status; }
    void drawOrders() {
        for (int i = 0; i < comenzi.size(); i++) {
            drawOrder(i);
        }
    }
    void addOrder(int id, std::string nume, int castig) {
        Comanda aux(id, nume, castig);
        comenzi.push_back(aux);
    }
    void clearOrders(int id = -1) {
        if (id != -1) {
            Comanda aux(comenzi[id]);
            comenzi.clear();
            comenzi.push_back(aux);
            activeOrder = 0;
            GameState::getInstance()->setDelivering();
        }
        else {
            comenzi.clear();
            activeOrder = 0;
        }
    }
    int removeOrder() {
        int id = comenzi[activeOrder].getId();
        decreaseSelectedOrder();
        comenzi.erase(comenzi.begin() + activeOrder);
        return id;
    }
    void increaseSelectedOrder() {
        activeOrder = (activeOrder + 1) % comenzi.size();
    }
    void decreaseSelectedOrder() {
        if (activeOrder == 0)
            activeOrder = comenzi.size() - 1;
        else
            activeOrder--;
    }
    void chooseOrder() {
        clearOrders(activeOrder);
    }
    void drawText() {
        std::string asd = "";
        for (int i = 0; i < password.size(); i++)
            asd.push_back('*');
        RenderString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "Username: " + userName, Shade::Black);
        RenderString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 15, "Password: " + asd, Shade::Black);

    }
    void commText(std::string type) {
        std::string fileName = "clientSays";
        std::ofstream f;
        f.open(fileName);
        std::string data = type;
        data += userName;
        data += " ";
        data += password;
        f << data;
        f.close();
    }
    void handleEnter() {
        if (password.size() == 0){
            enteringPassword = true;
            return;
        }
        enteringPassword = false;
        if (isLogin) {
            commText("LOGIN ");
        }
        else {
            commText("REGISTER ");
        }
        userName.clear();
        password.clear();
        setMainMenu();
    }

    void enterCharacter(char c) {
        if (enteringPassword) {
            if (c == 8) 
                return password.pop_back();
            password.push_back(c);
        }
        else {
            if (c == 8)
                return userName.pop_back();
            userName.push_back(c);
        }
    }
    
    bool isLoggedIn() { return JWT.size() > 0; }
    void setJWT(std::string JWT) { this->JWT = JWT; }
};
GameState* GameState::instance = 0;
float GameState::WINDOW_HEIGHT = 720.0f;
float GameState::WINDOW_WIDTH = 1280.0f;