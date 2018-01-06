#include <functional>
#include <vector>

#include <tdpi/tdpi.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "camera.hpp"
#include "glsl_program.hpp"
#include "renderable.hpp"
#include "renderer.hpp"

ogld::renderer::renderer() noexcept {
    glGenBuffers(1, &vertex_buffer_object);
    glGenVertexArrays(1, &vertex_array_object);

    glClearColor(0.0, 1.0, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST);
}

ogld::renderer::~renderer() {
    glDeleteBuffers(1, &vertex_buffer_object);
    glDeleteVertexArrays(1, &vertex_array_object);
}

void ogld::renderer::operator()(camera const& camera_) noexcept {
    camera_.bind();

    glBindVertexArray(vertex_array_object);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for (auto const& renderable : render_list) {
        std::vector<float> vertex_data;
        vertex_data.insert(vertex_data.end(), renderable.get().mesh_.vertex_data.begin(), renderable.get().mesh_.vertex_data.end());

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), vertex_data.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, nullptr);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<void*>(3 * sizeof(float)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<void*>(6 * sizeof(float)));

        renderable.get().material_.texture_.bind();
        glUniformMatrix4fv(glGetUniformLocation(*(glsl_program::current_instance), "model"), 1, GL_FALSE, glm::value_ptr(glm::translate(glm::mat4(1.f), renderable.get().location))); 

        glDrawArrays(GL_TRIANGLES, 0, vertex_data.size() / 8);
    }
}

