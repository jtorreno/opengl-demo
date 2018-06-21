#pragma once

#include <tdpi/tdpi.h>
#include <glm/glm.hpp>

template <typename T> class renderer;

namespace ogld {
    class camera {
    public:
        camera(glm::vec3 const& position, glm::vec3 const& target, float fov, glm::vec3 up);
        void update(glm::vec3 const& position, glm::vec3 const& target, float fov, glm::vec3 up);
    private:
        template <typename T> friend class renderer;
        void bind() const noexcept;

        glm::mat4 view;
        glm::mat4 projection;
    };
}
