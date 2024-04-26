#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cmath>
#include <iostream>

const int w = 1920, h = 1080;

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

void ColorChange(float color[], float speed, float s, float v) {
    float r, g, b;
    r = color[0];
    g = color[1];
    b = color[2];

    float cmax = std::max(r, std::max(g, b)); // maximum of r, g, b
    float cmin = std::min(r, std::min(g, b)); // minimum of r, g, b
    float diff = cmax - cmin; // diff of cmax and cmin.
    float h = -1;

    if (cmax == cmin) {
        h = 0;
    } else if (cmax == r) {
        h = fmod(60 * ((g - b) / diff) + 360, 360);
    } else if (cmax == g) {
        h = fmod(60 * ((b - r) / diff) + 120, 360);
    } else if (cmax == b) {
        h = fmod(60 * ((r - g) / diff) + 240, 360);
    }

    h /= 360;
    h += speed;

    int i = floor(h * 6);
	float f = h * 6 - i;
	float p = v * (1 - s);
	float q = v * (1 - f * s);
	float t = v * (1 - (1 - f) * s);

	switch (i % 6) {
		case 0: r = v, g = t, b = p; break;
		case 1: r = q, g = v, b = p; break;
		case 2: r = p, g = v, b = t; break;
		case 3: r = p, g = q, b = v; break;
		case 4: r = t, g = p, b = v; break;
		case 5: r = v, g = p, b = q; break;
	}

	color[0] = r;
    color[1] = g;
    color[2] = b;
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

    bool DrawTriangle = false, DrawSin = false, Wave = false, ColorWave = false;
    float rad = 0.0f, press = 180.0f, width_line = 1.0f, wave = 0.0f, wave_speed = 0.0f, color_wave_speed = 0.0f, s = 1.0f, v = 1.0f;
    float color[3] = {0.0f, 0.0f, 0.0f};
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
        if (ColorWave) {
            ColorChange(color, color_wave_speed, s, v);
        }

        ImGui::Begin("Hello the!");
        ImGui::Text("Hello again!)");
        ImGui::ColorEdit4("Color Clear", colorClear);
        ImGui::Checkbox("Draw Triable", &DrawTriangle);
        ImGui::Checkbox("Draw Sin", &DrawSin);
        ImGui::SliderFloat("Waves", &press, 360.0f, 0.0f);
        ImGui::SliderFloat("Radius", &rad, -1.0f, 1.0f);
        ImGui::SliderFloat("Width line", &width_line, 1.0f, 10.0f);
        ImGui::Checkbox("Wave", &Wave);
        ImGui::SliderFloat("Wave speed", &wave_speed, 0.0f, 0.2f);
        ImGui::SliderFloat("Wave pos", &wave, 0.0f, press + press);
        ImGui::Checkbox("Color wave", &ColorWave);
        ImGui::SliderFloat("Color wave speed", &color_wave_speed, 0.0f, 0.1f);
        ImGui::SliderFloat("Color wave saturation", &s, 0.0f, 1.0f);
        ImGui::SliderFloat("Color wave value", &v, 0.0f, 1.0f);
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
