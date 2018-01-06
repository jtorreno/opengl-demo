#version 330 core

in vec3 position;
in vec3 normal;
in vec2 texcoord;

out vec2 texcoord_fs;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    texcoord_fs = texcoord;

    vec4 v = vec4(position, 1);
    gl_Position = mat4(projection * view * model) * v;
}