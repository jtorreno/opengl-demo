#pragma once

#include <glm/glm.hpp>

#include "mesh.hpp"
#include "material.hpp"

namespace ogld {
    struct model {
        mesh mesh_;
        material material_;

        glm::vec3 location;
    };
}
