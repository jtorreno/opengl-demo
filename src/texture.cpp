#include <string>
#include <stdexcept>

#include <tdpi/tdpi.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "texture.hpp"

ogld::texture::texture(std::string const& image_path) {
    int width, height, component_count;
    unsigned char* image = stbi_load(image_path.c_str(), &width, &height, &component_count, 0);

    if (image == nullptr) throw std::runtime_error(std::string("failed to load image from ") + image_path + std::string("."));
    if (component_count < 4) throw std::runtime_error(std::string("image from ") + image_path + " not rgba.");

    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
}

ogld::texture::~texture() { glDeleteTextures(1, &handle); }
ogld::texture::texture(texture&& other) noexcept : handle(other.handle) { other.handle = 0; }

void ogld::texture::bind() noexcept { glBindTexture(GL_TEXTURE_2D, handle); }
