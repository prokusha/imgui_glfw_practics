#include "window.h"

int main() {
    Window window_;
    window_.CreateWindow("Hello", 1920, 1080);
    window_.MainLoop();
}
