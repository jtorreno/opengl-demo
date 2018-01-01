#pragma once

#include <string>
#include <tuple>
#include <vector>

#include <tdpi/tdpi.h>

#include "shader.hpp"

namespace ogld {
    class glsl_program {
    public:
        glsl_program(std::tuple<shader<shader_type::vertex>, shader<shader_type::fragment>> const& shaders, std::vector<std::string> const& attributes);
        glsl_program(glsl_program&& other) noexcept;

        ~glsl_program();

        operator GLuint() const noexcept;

        void bind() noexcept;
    private:
        GLuint handle;
    };

    std::tuple<shader<shader_type::vertex>, shader<shader_type::fragment>> operator+(shader<shader_type::vertex> vs, shader<shader_type::fragment> fs);
}