#pragma once

#include <tdpi/tdpi.h>
#include <glm/glm.hpp>

namespace ogld {
    class camera {
    public:
        camera(glm::vec3 const& position, glm::vec3 const& target, float fov, float aspect_ratio);
        void bind(GLuint program_handle) const noexcept;
    private:
        glm::mat4 mvp;
    };
}