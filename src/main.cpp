#include <utility>

#include "camera.hpp"
#include "glsl_program.hpp"
#include "mesh.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "window.hpp"

auto main() -> int {
    ogld::window window("opengl-demo", 640_px * 480_px);

    ogld::obj_mesh obj_mesh("../opengl-demo/res/cube.obj");
    
    ogld::renderer renderer;
    renderer.meshes.push_back(obj_mesh);

    ogld::camera camera({0, 0, 3}, {0, 0, 0}, 90);

    while (true) {
        renderer(camera);
        window.refresh();
    }
}
