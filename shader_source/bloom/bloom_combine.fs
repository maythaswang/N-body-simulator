#version 430 core

in vec2 tex_coord; 

uniform sampler2D u_color_texture;
uniform sampler2D u_blur_texture;

uniform float u_exposure;
uniform float u_gamma;
uniform float u_blur_intensity;

out vec4 FragColor;

void main() {
    vec3 color = texture(u_color_texture, tex_coord).rgb;
    vec3 blur = texture(u_blur_texture, tex_coord).rgb;
    color += blur*u_blur_intensity;

    // Reinhard tone mapping
    // color = color/ (color + vec3(1.0));

    // Exposure tone mapping
    // float u_exposure = 2.0;
    color = vec3(1.0) - exp(-color * u_exposure);

    // Gamma correction
    // float u_gamma = 2.2;
    color = pow(color, vec3(1.0/u_gamma));
    
    FragColor = vec4(color,1.0f);
}