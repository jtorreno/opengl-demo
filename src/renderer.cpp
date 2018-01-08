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
    glGenBuffers(1, &element_buffer_object);

    glGenVertexArrays(1, &vertex_array_object);

    glClearColor(1.0, 0.6, 0.75, 1.0);
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
        glBufferData(GL_ARRAY_BUFFER, renderable.get().mesh_.vertex_data.size() * sizeof(float), renderable.get().mesh_.vertex_data.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, nullptr);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<void*>(3 * sizeof(float)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<void*>(6 * sizeof(float)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, renderable.get().mesh_.indices.size() * sizeof(float), renderable.get().mesh_.indices.data(), GL_STATIC_DRAW);

        renderable.get().material_.texture_.bind();
        glUniformMatrix4fv(glGetUniformLocation(*(glsl_program::current_instance), "model"), 1, GL_FALSE, glm::value_ptr(glm::translate(glm::mat4(1.f), renderable.get().location))); 

        glDrawElements(GL_TRIANGLES, renderable.get().mesh_.indices.size(), GL_UNSIGNED_INT, reinterpret_cast<void*>(0));
    }
}

