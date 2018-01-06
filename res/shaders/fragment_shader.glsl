#version 330 core

in vec2 texcoord_fs;
in vec3 normal_fs;

out vec4 color;

uniform sampler2D sampler;

void main() {
    color = (vec4(0.15, 0.15, 0.15, 0.15) * texture(sampler, texcoord_fs)) + texture(sampler, texcoord_fs) * clamp(dot(vec3(0, 0, 1), normal_fs), 0, 1);
}