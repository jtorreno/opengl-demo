#pragma once

#include <functional>

#include "mesh.hpp"
#include "material.hpp"

namespace ogld {
    struct renderable {
        operator std::reference_wrapper<renderable const>() const;

        mesh mesh_;
        material material_;
    };

    struct static_object : public renderable {};
}