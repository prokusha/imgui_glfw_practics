#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cmath>

const int w = 1000, h = 1000;

void DrawTriang(float color[]) {
    glBegin(GL_TRIANGLES);

    glColor3f(color[0], color[1], color[2]);

    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);

    glEnd();
}

void DrawS(float color[], float rad, float press, float width_line, float n) {
    glLineWidth(width_line);
    glBegin(GL_LINE_STRIP);
    glColor3f(color[0], color[1], color[2]);
    float pointX = -1.0;
    for (float i = 0.0f; i <= 720.0f; i++) {
        glVertex2f(pointX + i / 360, rad*sin(M_PI * (i - n) / press));
    }

    glEnd();
}

int main() {
    GLFWwindow* window = nullptr;
    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(w, h, "Heeey!", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    bool DrawTriangle = false, DrawSin = false, Wave = false;
    float rad = 0.0f, press = 180.0f, width_line = 1.0f, wave = 0.0f, wave_speed = 0.0f;
    float color[3] = {0.13f, 0.14f, 0.18f};
    float colorClear[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(colorClear[0], colorClear[1], colorClear[2], colorClear[3]);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (DrawTriangle) {
            DrawTriang(color);
        }
        if (DrawSin) {
            if (Wave) {
                if (wave < press + press) {
                    wave += press * wave_speed;
                } else {
                    wave -= press + press;
                }
            }
            DrawS(color, rad, press, width_line, wave);
        }

        ImGui::Begin("Hello the!");
        ImGui::Text("Hello again!)");
        ImGui::ColorEdit3("Color Clear", colorClear);
        ImGui::Checkbox("Draw Triable", &DrawTriangle);
        ImGui::Checkbox("Draw Sin", &DrawSin);
        ImGui::SliderFloat("Waves", &press, 360.0f, 0.0f);
        ImGui::SliderFloat("Radius", &rad, -1.0f, 1.0f);
        ImGui::SliderFloat("Width line", &width_line, 1.0f, 10.0f);
        ImGui::Checkbox("Wave", &Wave);
        ImGui::SliderFloat("Wave speed", &wave_speed, 0.0f, 0.2f);
        ImGui::SliderFloat("Wave pos", &wave, 0.0f, press + press);
        ImGui::ColorEdit3("Color", color);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
