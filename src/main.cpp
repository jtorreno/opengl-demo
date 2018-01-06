#include <utility>
#include <functional>

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
    ogld::static_object cube{ogld::obj_mesh("../opengl-demo/res/models/cube.obj"), {ogld::texture()}, {0, 0, 0}};
    
    renderer.render_list.push_back(cube);

    ogld::camera camera({2, 2, 2}, {0, 0, 0}, 90);

    while (true) {
        renderer(camera);
        window.refresh();
    }
}
