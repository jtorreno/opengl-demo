#include "window.hpp"

auto main() -> int {
    ogld::window window("opengl-demo", 640_px * 480_px);

    while (true) {
        window.refresh();
    }
}
