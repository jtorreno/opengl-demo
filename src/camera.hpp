#pragma once

#include <tdpi/tdpi.h>
#include <glm/glm.hpp>

#include "renderer.hpp"

namespace ogld {
    class camera {
    public:
        camera(glm::vec3 const& position, glm::vec3 const& target, float fov, float aspect_ratio);
    private:
        friend class renderer;
        void bind() const noexcept;

        glm::mat4 mvp;
    };
}