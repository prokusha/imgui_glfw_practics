#pragma once

#include <string>

struct Shaders {
    std::string vShader;
    std::string fShader;
};

Shaders ParseShader(const std::string& filepath);
unsigned int CompileShader(const std::string& source, unsigned int type);
int CreateShaders(const std::string& vShaders, const std::string& fShaders);
