#version 330 core

in vec2 texcoord_fs;
out vec4 color;

uniform sampler2D sampler;

void main() {
    color = texture(sampler, texcoord_fs);
}