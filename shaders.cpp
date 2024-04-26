#include "shaders.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <iostream>
#include <fstream>
#include <sstream>

Shaders ParseShader(const std::string& filepath) {
    std::ifstream f(filepath);

    enum class Type {
        NONE = -1, Vertex = 0, Fragment = 1
    };

    std::string line;
    std::stringstream ss[2];
    Type type = Type::NONE;

    while (getline(f, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = Type::Vertex;
            } else if (line.find("fragment") != std::string::npos) {
                type = Type::Fragment;
            }
        } else {
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};
}

unsigned int CompileShader(const std::string& source, unsigned int type) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char* message = (char*)alloca(len * sizeof(char));
        glGetShaderInfoLog(id, len, &len, message);
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

int CreateShaders(const std::string& vShaders, const std::string& fShaders) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(vShaders, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fShaders, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
