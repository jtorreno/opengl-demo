#pragma once

#include <vector>
#include <tdpi/tdpi.h>

#include "mesh.hpp"

namespace ogld {
    class camera;

    class renderer {
    public:
        renderer() noexcept;
        ~renderer();

        void operator()(camera const& camera_) const noexcept;

        std::vector<mesh> meshes;
    private:
        GLuint vertex_buffer_object, vertex_array_object;
    };
}