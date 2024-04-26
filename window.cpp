#include "drawing.h"
#include "window.h"
#include "gui.h"

void Window::CreateWindow(std::string title, int width, int height) {
    if (!glfwInit()) {
        throw "Init window error!";
    }

    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window_) {
        glfwTerminate();
        throw "Window object not create!";
    }

    glfwMakeContextCurrent(window_);

    if (glewInit() != GLEW_OK) {
        throw "Init glew error!";
    }

    object_ = new Triangle();
    gui_ = new Gui(window_);
}

void Window::MainLoop() {
    while (!glfwWindowShouldClose(window_))
    {
        int width, height;
        glfwGetWindowSize(window_, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        gui_->NewFrame();

        object_->Draw();

        gui_->DrawGui(object_->GetSetting());
        gui_->Render();

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
    object_->DeleteShaders();
    gui_->Destroy();
    glfwTerminate();
}
