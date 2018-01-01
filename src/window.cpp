#include <array>
#include <memory>
#include <string>
#include <stdexcept>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include <GLFW/glfw3.h>

#include "window.hpp"

using namespace gl;

ogld::px::px(unsigned int x_) noexcept : x(x_) {}

std::array<unsigned int, 2> ogld::px::operator*(ogld::px rh) { return {x, rh.x}; }
ogld::px operator""_px(unsigned long long x) { return x; }

void ogld::glfw_window_deleter::operator()(GLFWwindow* glfw_window) const noexcept { glfwDestroyWindow(glfw_window); }

ogld::window::window(std::string title, std::array<unsigned int, 2> size) : glfw_window(nullptr) {
    if (!glfwInit()) throw std::runtime_error("failed to initialize glfw.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glfw_window.reset(glfwCreateWindow(size[0], size[1], title.c_str(), nullptr, nullptr));
    if (!glfw_window.get()) throw std::runtime_error("failed to create window.");

    glfwMakeContextCurrent(glfw_window.get());
}

void ogld::window::make_current() noexcept { glfwMakeContextCurrent(glfw_window.get()); }

void ogld::window::refresh() noexcept {
    glfwPollEvents();
    glfwSwapBuffers(glfw_window.get());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}