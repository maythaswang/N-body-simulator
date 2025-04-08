#version 430 core

in float star_mass;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 FragColorThreshold;

uniform bool bloom_enabled;
uniform bool use_mass_color;

// Just fun stuffs (colour based on depth)
vec3 color_by_linearized_depth(float depth) 
{
    float near = 100; //real value is 0.1
    float far  = 20000.0;  // real value is pretty big number
    float z = depth * 2.0 - 1.0; // back to NDC 
    vec3 new_color = vec3(((2.0 * near * far) / (far + near - z * (far - near)))/far);	
    new_color.x = 1.0f;
    return new_color;
}

vec3 get_color(){
    float mass_clamp = min(star_mass, 100000);
    vec3 star_color;

    // Main sequence colours but the scale holds no significance
    // vec3 red = vec3(1.0f, 0.2f, 0.2f);
    vec3 red = vec3(7.0f, 0.55f, 0.24f);
    vec3 orange = vec3(1.0f, 0.4f, 0.1f);
    vec3 yellow =vec3(5.0f, 2.0f, 0.24f);
    vec3 white = vec3(3.0f, 3.0f, 3.0f);
    vec3 blue_white = vec3(0.9f, 1.2, 1.8f);
    vec3 blue = vec3(0.5f, 0.5f, 7.0f);

    if(star_mass > 1000000){ 
        star_color = blue;
    } else if (star_mass > 500000){
        star_color = blue_white;
    } else if (star_mass > 80000){
        star_color = white;
    } else if (star_mass > 40000){ 
        star_color = yellow;
    } else if (star_mass > 10000){
        star_color = orange;
    } else {
        star_color = red;
    }

    return star_color;
}

void main(){
    // FragColor = vec4(1.0f, 0.88f, 0.49f, 0.7f);
    vec3 color = vec3(5.0f, 2.0f, 0.6f);

    // Maybe we have enable/disable gradient
    if(use_mass_color){
        color = get_color();
    }
    FragColor = vec4(color,1.0f);
    
    // REC 709 Standard luminance
    float luminance = dot(vec3(0.2126,0.7152,0.0722), color);

    if(luminance > 0.2){
        FragColorThreshold = vec4(color,1.0f);
    } else {
        FragColorThreshold = vec4(0.0f);
    }

    if(!bloom_enabled){
        // Exposure tone mapping
        float u_exposure = 1.0;
        color = vec3(1.0) - exp(-color * u_exposure);

        // Gamma correction
        float u_gamma = 2.2;
        color = pow(color, vec3(1.0/u_gamma));
        FragColor = vec4(color,1.0f);
    }

}