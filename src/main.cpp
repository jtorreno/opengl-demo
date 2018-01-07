#include <array>
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <utility>

#include "camera.hpp"
#include "glsl_program.hpp"
#include "renderer.hpp"
#include "renderable.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "window.hpp"

#include <GLFW/glfw3.h>

std::array<double, 2> mouse_position(GLFWwindow* window) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    return {x, y};
}

auto main() -> int {
    ogld::window window("opengl-demo", 640_px * 480_px);
    
    ogld::renderer renderer;

    ogld::static_object cube{ogld::obj_mesh("../opengl-demo/res/models/cube.obj"), {ogld::texture()}, {0, 0, 0}};
    ogld::static_object suzanne{ogld::obj_mesh("../opengl-demo/res/models/suzanne.obj"), {ogld::texture("../opengl-demo/res/textures/white.png")}, {0, 3, 0}};
    
    renderer.render_list.push_back(cube);
    renderer.render_list.push_back(suzanne);

    glm::vec3 position{0, 4, 4};
    ogld::camera camera(position, {0, 2, 0}, 60, {0, 1, 0});

    float horizontal_angle = 3.14159;
    float vertical_angle = 0;

    while (true) {
        double start = glfwGetTime();
        glfwSetCursorPos(window, 640 / 2, 480 / 2);

        renderer(camera);
        window.refresh();

        float const elapsed_time = glfwGetTime() - start;
        auto const mouse_pos = mouse_position(window);

        horizontal_angle += 0.1 * elapsed_time * (640 / 2.0 - mouse_pos.at(0));
        vertical_angle += 0.1 * elapsed_time * (480 / 2.0 - mouse_pos.at(1));

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
