#pragma once

#include <string>
#include <vector>

namespace ogld {
    class mesh {
    public:
        std::vector<float> vertex_data;
        std::vector<unsigned int> indices;
    };

    class obj_mesh : public mesh {
    public: obj_mesh(std::string const& path);
    };
}
