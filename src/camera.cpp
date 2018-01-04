#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <tdpi/tdpi.h>

#include "camera.hpp"
#include "glsl_program.hpp"

ogld::camera::camera(glm::vec3 const& position, glm::vec3 const& target, float fov) {
    mvp = glm::perspective(glm::radians(fov), window::current_instance->aspect_ratio, 0.1f, 1000.f) * glm::lookAt(position, target, glm::vec3(0, 1, 0)) * glm::mat4(1.0f);
}

void ogld::camera::bind() const noexcept { 
    glUniformMatrix4fv(glGetUniformLocation(*(glsl_program::current_instance), "mvp"), 1, GL_FALSE, glm::value_ptr(mvp)); 
}