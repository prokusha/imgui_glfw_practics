#include "gui.h"
#include "drawing.h"


void Gui::DrawGui(Settings& setting) {
    ImGui::Begin("Gui Title idk");
    ImGui::ColorEdit3("Color", setting.color_rgb);
    ImGui::End();
}

void Gui::NewFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Gui::Render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::Destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
