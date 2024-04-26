#pragma once

#include "shaders.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <string>
#include <iostream>

struct Settings {
    float color_rgb[3] = {1.0f, 1.0f, 1.0f};
    float color_rgba[4] = {1.0f, 1.0f, 1.0f, 1.0f};
};

class Drawing {
public:
    Drawing() = default;
    virtual ~Drawing() = default;

    virtual void Draw() = 0;
    virtual void DeleteShaders() = 0;
    Settings& GetSetting() {
        return setting_;
    }

protected:
    Settings setting_;
};

class Triangle : public Drawing {
public:
    Triangle() : Drawing() {
        bindBuff();
        createShader();
    }

    void Draw() override {
        float r = setting_.color_rgb[0];
        float g = setting_.color_rgb[1];
        float b = setting_.color_rgb[2];

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void DeleteShaders() override {
        glDeleteProgram(shader);
    };

private:
    float pos[8] = {
       -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f,  0.5f,
       -0.5f,  0.5f
    };

    unsigned int index[8] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int buf;
    unsigned int shader;

    void bindBuff() {
        glGenBuffers(1, &buf);
        glBindBuffer(GL_ARRAY_BUFFER, buf);
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), pos, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

        // glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void createShader() {
        Shaders shaders = ParseShader("shaders/base.shader");
        shader = CreateShaders(shaders.vShader, shaders.fShader);
        glUseProgram(shader);
    }
};
