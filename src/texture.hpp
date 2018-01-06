#pragma once

#include <string>

namespace ogld {
    class texture {
    public:
        texture(std::string const& image_path="../opengl-demo/res/textures/default.png");
        ~texture();

        texture(texture const&) = delete;
        texture& operator=(texture const&) = delete;

        texture(texture&& other) noexcept;

        void bind() noexcept;
    private:
        GLuint handle;
    };
}