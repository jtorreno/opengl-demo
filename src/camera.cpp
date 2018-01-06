#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <tdpi/tdpi.h>

#include "camera.hpp"
#include "glsl_program.hpp"
#include "window.hpp"

ogld::camera::camera(glm::vec3 const& position, glm::vec3 const& target, float fov) {
    view = glm::lookAt(position, target, glm::vec3(0, 1, 0));
    projection = glm::perspective(glm::radians(fov), window::current_instance->aspect_ratio, 0.1f, 1000.f);
}

void ogld::camera::bind() const noexcept { 
    glUniformMatrix4fv(glGetUniformLocation(*(glsl_program::current_instance), "view"), 1, GL_FALSE, glm::value_ptr(view)); 
    glUniformMatrix4fv(glGetUniformLocation(*(glsl_program::current_instance), "projection"), 1, GL_FALSE, glm::value_ptr(projection)); 
}