CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
PROJECT(testing)

FIND_PACKAGE(glfw3 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)

SET(CMAKE_CXX_STANDARD 17)

SET(IMGUI_DIR ./imgui)
INCLUDE_DIRECTORIES(${IMGUI_DIR})

ADD_EXECUTABLE(testing main.cpp window.cpp gui.cpp shaders.cpp ${IMGUI_DIR}/imgui_impl_glfw.cpp ${IMGUI_DIR}/imgui_impl_opengl3.cpp ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp)

target_link_libraries(testing glfw GLEW OpenGL::GL)

file(COPY ./shaders/ DESTINATION shaders)
