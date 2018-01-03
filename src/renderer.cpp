#include <vector>
#include <tdpi/tdpi.h>

#include "camera.hpp"
#include "mesh.hpp"
#include "renderer.hpp"

ogld::renderer::renderer() noexcept {
    glGenBuffers(1, &vertex_buffer_object);
    glGenVertexArrays(1, &vertex_array_object);

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

ogld::renderer::~renderer() {
    glDeleteBuffers(1, &vertex_buffer_object);
    glDeleteVertexArrays(1, &vertex_array_object);
}

void ogld::renderer::operator()(camera const& camera_) const noexcept {
    camera_.bind();
    
    std::vector<float> vertex_data;
    for (auto& mesh : meshes) {
        vertex_data.insert(vertex_data.end(), mesh.vertex_data.begin(), mesh.vertex_data.end());
    }

    glBindVertexArray(vertex_array_object);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), vertex_data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<void*>(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<void*>(6 * sizeof(float)));

    glDrawArrays(GL_TRIANGLES, 0, vertex_data.size() / 8);
}
