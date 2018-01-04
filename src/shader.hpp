#pragma once

#include <fstream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <utility>

#include <tdpi/tdpi.h>

#include "window.hpp"

namespace ogld {
    enum class shader_type : GLenum {
        vertex = GL_VERTEX_SHADER,
        fragment = GL_FRAGMENT_SHADER
    };

    template <shader_type S>
    class shader {
    public:
        shader(std::string const& source) : handle(0) {
            handle = glCreateShader(static_cast<GLenum>(S));
            
            const char* source_c_str = source.c_str();
            glShaderSource(handle, 1, &source_c_str, nullptr);

            glCompileShader(handle);

            GLint compile_status = GL_FALSE;
            glGetShaderiv(handle, GL_COMPILE_STATUS, &compile_status);

            if (compile_status == GL_FALSE) {
                GLint info_log_length = 0;
                glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &info_log_length);

                std::string info_log;
                info_log.reserve(info_log_length);

                glGetShaderInfoLog(handle, info_log_length, &info_log_length, info_log.data());
                throw std::runtime_error(std::string("shader compilation failed.\n\tglGetShaderInfoLog(): ") + info_log);
            }
        }

        shader(shader<S>&& other) noexcept : handle(other.handle) { other.handle = 0; }

        shader(shader const&) = delete;
        shader& operator=(shader const&) = delete;

        ~shader() { glDeleteShader(handle); }

        operator GLuint() const noexcept { return handle; }
    private:
        GLuint handle;
    };
}