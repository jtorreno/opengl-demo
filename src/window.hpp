#pragma once

#include <array>
#include <memory>
#include <string>

#include <GLFW/glfw3.h>

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
    private:
        std::unique_ptr<GLFWwindow, glfw_window_deleter> glfw_window;
    };
}

ogld::px operator""_px(unsigned long long x);
