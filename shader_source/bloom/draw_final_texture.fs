#version 430 core

in vec2 tex_coord; 

uniform sampler2D u_texture;

out vec4 FragColor;

void main() {
    // FragColor = texture(u_texture, tex_coord);
    FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
}