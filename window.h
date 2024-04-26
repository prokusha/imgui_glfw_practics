#pragma once

#include "drawing.h"
#include "gui.h"
#include "imgui/imgui_impl_glfw.h"

#include <string>
#include <GLFW/glfw3.h>


class Window {
public:
    void CreateWindow(std::string title, int width, int height);
    void MainLoop();
    void Destroy();

private:
    GLFWwindow* window_ = nullptr;
    Drawing* object_ = nullptr;
    Gui* gui_ = nullptr;
};
