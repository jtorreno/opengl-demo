#include <utility>

#include "camera.hpp"
#include "glsl_program.hpp"
#include "mesh.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "window.hpp"

auto main() -> int {
    ogld::window window("opengl-demo", 640_px * 480_px);

    ogld::shader<ogld::shader_type::vertex> vertex_shader("#version 330 core\n"
                                                           ""
                                                           "in vec3 position;"
                                                           "in vec3 normal;"
                                                           "in vec2 texcoord;"
                                                           ""
                                                           "uniform mat4 mvp;"
                                                           ""
                                                           "void main()"
                                                           "{"
                                                           "    vec4 v = vec4(position, 1);"
                                                           "    gl_Position = mvp * v;"
                                                           "}");

    ogld::shader<ogld::shader_type::fragment> fragment_shader("#version 330 core\n"
                                                               ""
                                                               "out vec4 color;"
                                                               ""
                                                               "void main()"
                                                               "{"
                                                               "    color = vec4(0.0, 1.0, 0.0, 0.5);"
                                                               "}");

    ogld::glsl_program glsl_program(vertex_shader, fragment_shader, {"position", "normal", "texcoord"});
    glsl_program.bind();

    ogld::camera camera({0, 0, 3}, {0, 0, 0}, 90);

    ogld::obj_model obj_model("../opengl-demo/res/cube.obj");
    
    ogld::renderer renderer;
    renderer.meshes.push_back(obj_model);

    while (true) {
        renderer(camera);
        window.refresh();
    }
}
