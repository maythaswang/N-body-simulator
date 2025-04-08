#version 430 core

in vec2 tex_coord;

uniform sampler2D u_prev_texture;
uniform bool is_horizontal;

out vec4 FragColor;

const int BLUR_RADIUS = 7; // basically ceil(kernel/2)
const float sigma = 1.9;
float weight[BLUR_RADIUS];

void calc_gaussian_kernel(){
    for(int i = 0; i < BLUR_RADIUS; i++){
        weight[i] = exp(-0.5*(pow(i/sigma,2)))/ (sqrt(2*3.141592653589793)*sigma) ;
    }
}



void main() {
    calc_gaussian_kernel();

    vec2 tex_offset = 1.0 / textureSize(u_prev_texture, 0); //size of texel
    vec3 color = texture(u_prev_texture, tex_coord).rgb * weight[0];

    if(is_horizontal){
        for(int i = 1; i < BLUR_RADIUS; i++){
            color += texture(u_prev_texture, tex_coord + vec2(tex_offset.x * i,0)).rgb * weight[i];
            color += texture(u_prev_texture, tex_coord - vec2(tex_offset.x * i,0)).rgb * weight[i];
        }
    } else { // vertical
        for(int i = 1; i < BLUR_RADIUS; i++){
            color += texture(u_prev_texture, tex_coord + vec2(0, tex_offset.y * i)).rgb * weight[i];
            color += texture(u_prev_texture, tex_coord - vec2(0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    
    FragColor = vec4(color,1.0f);
}