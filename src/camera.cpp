#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <tdpi/tdpi.h>

#include "camera.hpp"

ogld::camera::camera(glm::vec3 const& position, glm::vec3 const& target, float fov, float aspect_ratio) {
    mvp = glm::perspective(fov, aspect_ratio, 0.1f, 1000.f) * glm::lookAt(position, target, glm::vec3(0, 1, 0)) * glm::mat4(1.0f);
}

void ogld::camera::bind(GLuint program_handle) const noexcept { 
    glUniformMatrix4fv(glGetUniformLocation(program_handle, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp)); 
}