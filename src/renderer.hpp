#pragma once

#include <vector>
#include <tdpi/tdpi.h>

#include "camera.hpp"
#include "mesh.hpp"

namespace ogld {
    class renderer {
    public:
        renderer() noexcept;
        ~renderer();

        operator()(camera const& camera_) const noexcept;

        std::vector<mesh> meshes;
    private:
        GLuint vertex_buffer_object, vertex_array_object;
    };
}