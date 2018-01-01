#pragma once

#include <fstream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <utility>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

using namespace gl;

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

            GLint compile_status = 0;
            glGetShaderiv(handle, GL_COMPILE_STATUS, &compile_status)

            if (!compile_status) {
                GLint info_log_length = 0;
                glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &info_log_length);

                std::string info_log;
                info_log.reserve(info_log_length);

                glGetShaderInfoLog(handle, info_log_length, &info_log_length, info_log.c_str());
                throw std::runtime_error(std::string("shader compilation failed.\n\tglGetShaderInfoLog(): ") + std::string());
            }
        }

        shader(shader<S>&& other) noexcept : shader_handle(other.shader_handle) { other.shader_handle = 0; }
        ~shader() { glDeleteShader(handle); }

        operator GLuint() const noexcept { return handle; }
    private:
        GLuint handle;
    }
}