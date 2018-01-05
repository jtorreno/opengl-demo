#pragma once

#include "mesh.hpp"
#include "material.hpp"

namespace ogld {
    struct renderable {
        mesh mesh_;
        material material_;
    };

    struct static_object : public renderable {};
}