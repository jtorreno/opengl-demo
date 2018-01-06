#include <utility>

#include "camera.hpp"
#include "glsl_program.hpp"
#include "renderer.hpp"
#include "renderable.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "window.hpp"

auto main() -> int {
    ogld::window window("opengl-demo", 640_px * 480_px);
    
    ogld::renderer renderer;
    renderer.render_list.push_back({ogld::obj_mesh("../opengl-demo/res/models/cube.obj"), {ogld::texture()}});

    ogld::camera camera({2, 2, 2}, {0, 0, 0}, 90);

    while (true) {
        renderer(camera);
        window.refresh();
    }
}
