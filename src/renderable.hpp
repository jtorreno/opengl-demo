#pragma once

#include <functional>
#include <glm/glm.hpp>

#include "mesh.hpp"
#include "material.hpp"

namespace ogld {
    struct renderable {
        operator std::reference_wrapper<renderable const>() const;

        mesh mesh_;
        material material_;

        glm::vec3 location;
    };
}
