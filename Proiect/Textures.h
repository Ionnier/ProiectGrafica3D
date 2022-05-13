#pragma once
#include <utility>
#include "SOIL.h"

class Texture {
private:
    unsigned char* image;
    int width, height;
    std::string name;
public:
    Texture(std::string name) :name(name) {
        image = SOIL_load_image(name.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    }

    void enableTexture() {
        glEnable(GL_TEXTURE_2D);
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	// Set texture wrapping to GL_REPEAT
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    }
};

class Textures {
private:
    std::map<std::string, Texture> textures;
    static Textures* instance;
    Textures() {

    }
public:
    static Textures* getInstance() {
        if (!instance)
            instance = new Textures();
        return instance;
    }
    void addTexture(std::string name) {
        Texture texture(name);
        textures.insert(std::make_pair(name, texture));
    }
    void enableTexture(std::string name) {
        auto iter = textures.begin();
        while (iter != textures.end()) {
            if (iter->first == name) {
                iter->second.enableTexture();
                return;
            }
            ++iter;
        }
        addTexture(name);
        enableTexture(name);
    }
};
Textures* Textures::instance = 0;
