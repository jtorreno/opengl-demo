#include "camera.hpp"
#include "glsl_program.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "static_object.hpp"
#include "texture.hpp"
#include "window.hpp"

#include <GLFW/glfw3.h>

struct point { double x, y; };

point operator-(point const& lhs, point const& rhs) {
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

point mouse_position(GLFWwindow* window) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    return {x, y};
}

point mouse_delta(GLFWwindow* window) {
    static point last_pos = mouse_position(window);
    point pos = mouse_position(window);

    point delta = last_pos - pos;
    last_pos = pos;

    return delta;
}

auto main() -> int {
    ogld::window window("opengl-demo", 1600_px * 900_px);
    ogld::renderer renderer;

    ogld::static_object cube{ogld::obj_mesh("../opengl-demo/res/models/cube.obj"), {ogld::texture()}, {0, 0, 0}};
    ogld::static_object suzanne{ogld::obj_mesh("../opengl-demo/res/models/suzanne.obj"), {ogld::texture("../opengl-demo/res/textures/white.png")}, {0, 3, 0}};

    renderer.render_list.push_back(cube);
    renderer.render_list.push_back(suzanne);

    glm::vec3 position{0, 4, 4};
    ogld::camera camera(position, {0, 2, 0}, 60, {0, 1, 0});

    float horizontal_angle = 3.14159;
    float vertical_angle = 0;

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        double start = glfwGetTime();

        renderer(camera);
        window.refresh();

        float elapsed_time = glfwGetTime() - start;
        auto delta = mouse_delta(window);

        horizontal_angle += 0.005 * delta.x;
        vertical_angle   += 0.005 * delta.y;

        glm::vec3 direction{std::cos(vertical_angle) * std::sin(horizontal_angle), std::sin(vertical_angle), std::cos(vertical_angle) * std::cos(horizontal_angle)};
        glm::vec3 right{std::sin(horizontal_angle - 3.14159 / 2.0), 0, std::cos(horizontal_angle - 3.14159 / 2.0)};
        glm::vec3 up = glm::cross(right, direction);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { position += direction * elapsed_time * 10.0f; }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { position -= direction * elapsed_time * 10.0f; }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { position += right * elapsed_time * 10.0f; }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { position -= right * elapsed_time * 10.0f; }

        camera.update(position, position + direction, 60, up);
    }
}
