#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <tdpi/tdpi.h>

#include "shader.hpp"
#include "glsl_program.hpp"

ogld::glsl_program* ogld::glsl_program::current_instance = nullptr;

ogld::glsl_program::glsl_program(shader<shader_type::vertex> const& vs, shader<shader_type::fragment> const& fs, std::vector<std::string> const& attributes) : handle(glCreateProgram()) {
    glAttachShader(handle, vs);
    glAttachShader(handle, fs);

    for (auto const& attribute : attributes) { glBindAttribLocation(handle, &attribute - &attributes.front(), attribute.c_str()); }

    glLinkProgram(handle);

    glDetachShader(handle, vs);
    glDetachShader(handle, fs);

    GLint link_status = GL_FALSE;
    glGetProgramiv(handle, GL_LINK_STATUS, &link_status);

    if (link_status == GL_FALSE) {
        GLint info_log_length = 0;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &info_log_length);

        std::string info_log;
        info_log.resize(info_log_length);

        glGetProgramInfoLog(handle, info_log_length, &info_log_length, &info_log[0]);
        throw std::runtime_error(std::string("program linking failed.\n\tglGetProgramInfoLog(): ") + info_log);
    }
}

ogld::glsl_program::glsl_program(glsl_program&& other) noexcept { other.handle = 0; }
ogld::glsl_program::~glsl_program() { glDeleteProgram(handle); }

ogld::glsl_program::operator GLuint() const noexcept { return handle; }

void ogld::glsl_program::bind() noexcept {
    current_instance = this;
    glUseProgram(handle);
}
