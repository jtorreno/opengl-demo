#pragma once

#include <string>
#include <vector>

namespace ogld {
    class mesh {
    public:
        std::vector<float> vertex_data;
    };

    class obj_model : public mesh {
    public: obj_model(std::string const& path);
    };
}