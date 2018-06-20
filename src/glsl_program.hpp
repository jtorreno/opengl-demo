#pragma once

#include <string>
#include <vector>

#include <tdpi/tdpi.h>

#include "camera.hpp"
#include "renderer.hpp"
#include "shader.hpp"

namespace ogld {
    class glsl_program {
    public:
        glsl_program(shader<shader_type::vertex> const& vs, shader<shader_type::fragment> const& fs, std::vector<std::string> const& attributes);

        glsl_program(glsl_program&& other) noexcept;

        glsl_program(glsl_program const&) = delete;
        glsl_program& operator=(glsl_program const&) = delete;

        ~glsl_program();

        operator GLuint() const noexcept;

        void bind() noexcept;
    private:
        friend class camera;
        friend class renderer;
        static glsl_program* current_instance;

        GLuint handle;
    };
}
