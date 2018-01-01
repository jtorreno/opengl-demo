#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include <tdpi/tdpi.h>

#include "shader.hpp"
#include "glsl_program.hpp"

ogld::glsl_program::glsl_program(std::tuple<shader<shader_type::vertex>, shader<shader_type::fragment>> const& shaders, std::vector<std::string> const& attributes) : handle(0) {
    glAttachShader(handle, std::get<0>(shaders));
    glAttachShader(handle, std::get<1>(shaders));

    for (auto const& attribute : attributes) { glBindAttribLocation(handle, &attribute - &attributes.front(), attribute.c_str()); }

    glLinkProgram(handle);

    glDetachShader(handle, std::get<0>(shaders));
    glDetachShader(handle, std::get<1>(shaders));

    GLint link_status = GL_FALSE;
    glGetProgramiv(handle, GL_LINK_STATUS, &link_status);

    if (link_status == GL_FALSE) {
        GLint info_log_length = 0;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &info_log_length);

        std::string info_log;
        info_log.reserve(info_log_length);

        glGetProgramInfoLog(handle, info_log_length, &info_log_length, info_log.data());
        throw std::runtime_error(std::string("program linking failed.\n\tglGetProgramInfoLog(): ") + info_log);
    }
}

ogld::glsl_program::glsl_program(ogld::glsl_program&& other) noexcept { other.handle = 0; }
ogld::glsl_program::~glsl_program() { glDeleteProgram(handle); }

ogld::glsl_program::operator GLuint() const noexcept { return handle; }

void ogld::glsl_program::bind() noexcept { glUseProgram(handle); }
