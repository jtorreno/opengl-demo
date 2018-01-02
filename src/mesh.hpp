#pragma once

#include <string>
#include <vector>

namespace ogld {
    class mesh {
    public:
        virtual ~mesh() = 0;
        std::vector<float> vertex_data;
    };

    inline mesh::~mesh() {}

    class obj_model : mesh {
    public: obj_model(std::string const& path);
    };
}