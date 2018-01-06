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

    ogld::static_object cube({ogld::obj_mesh("../opengl-demo/res/models/cube.obj"), {ogld::texture()}, {0, 0, 0}});
    ogld::static_object suzanne({ogld::obj_mesh("../opengl-demo/res/models/suzanne.obj"), {ogld::texture("../opengl-demo/res/textures/white.png")}, {0, 3, 0}});
    
    renderer.render_list.push_back(cube);
    renderer.render_list.push_back(suzanne);

    ogld::camera camera({2, 4, 4}, {0, 2, 0}, 90);

    while (true) {
        renderer(camera);
        window.refresh();
    }
}
