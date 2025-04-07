#version 430 core

in vec2 tex_coord;

uniform sampler2D u_prev_texture;
uniform bool is_horizontal;

out vec4 FragColor;


// Just use gaussian function to pre-compute this
const int BLUR_RADIUS = 5;
const float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);


void main() {
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