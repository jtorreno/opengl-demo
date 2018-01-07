#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <tdpi/tdpi.h>

#include "camera.hpp"
#include "glsl_program.hpp"
#include "window.hpp"

ogld::camera::camera(glm::vec3 const& position, glm::vec3 const& target, float fov, glm::vec3 up) {
    update(position, target, fov, up);
}

void ogld::camera::update(glm::vec3 const& position, glm::vec3 const& target, float fov, glm::vec3 up) {
    view = glm::lookAt(position, target, up);
    projection = glm::perspective(glm::radians(fov), window::current_instance->aspect_ratio, 0.1f, 1000.f);
}

void ogld::camera::bind() const noexcept { 
    glUniformMatrix4fv(glGetUniformLocation(*(glsl_program::current_instance), "view"), 1, GL_FALSE, glm::value_ptr(view)); 
    glUniformMatrix4fv(glGetUniformLocation(*(glsl_program::current_instance), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}