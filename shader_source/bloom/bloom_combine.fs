#version 430 core

in vec2 tex_coord; 

uniform sampler2D u_color_texture;
uniform sampler2D u_blur_texture;

out vec4 FragColor;

void main() {
    vec3 color = texture(u_color_texture, tex_coord).rgb;
    vec3 blur = texture(u_blur_texture, tex_coord).rgb;
    color += blur*0.8;

    FragColor = vec4(color,1.0f);
    
    // FragColor = vec4(tex_coord.x,tex_coord.y,1.0f,1.0f);
}