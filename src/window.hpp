#pragma once

#include <array>
#include <memory>
#include <string>

#include <GLFW/glfw3.h>

#include "camera.hpp"
#include "glsl_program.hpp"

namespace ogld {
    class px {
    public:
        px(unsigned int _x) noexcept;
        std::array<unsigned int, 2> operator*(px rh);
    private:
        unsigned int x;
    };

    struct glfw_window_deleter {
        void operator()(GLFWwindow* glfw_window) const noexcept;
    };

    class window {
    public:
        window(std::string title_, std::array<unsigned int, 2> size);

        void make_current() noexcept;
        void refresh() noexcept;

        operator GLFWwindow*() const noexcept;
    private:
        std::unique_ptr<GLFWwindow, glfw_window_deleter> glfw_window;

        friend class camera;

        static window* current_instance;
        const float aspect_ratio;

        std::unique_ptr<glsl_program> glsl_program_;
    };
}

ogld::px operator""_px(unsigned long long x);
