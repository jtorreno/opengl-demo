#pragma once

#include <vector>
#include <functional>

#include <tdpi/tdpi.h>

#include "renderable.hpp"

namespace ogld {
    class camera;

    class renderer {
    public:
        renderer() noexcept;
        ~renderer();

        void operator()(camera const& camera_) noexcept;

        std::vector<std::reference_wrapper<renderable const>> render_list;
    private:
        GLuint vertex_buffer_object, element_buffer_object, vertex_array_object;
    };
}