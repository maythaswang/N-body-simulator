#version 430 core

in float star_mass;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 FragColorThreshold;

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

vec3 parabola_interpolate(vec3 color_1, vec3 color_2, float mass) {
    float step_para = 1 + 2*(mass-0.5);
    return mix(color_1, color_2, step_para);
}

// FIX THIS LATER
vec3 get_color(){
    float mass_clamp = min(star_mass, 100000);


    vec3 star_color;

    // Main sequence colours but the scale holds no significance
    vec3 red = vec3(1.0f, 0.3f, 0.3f);
    vec3 orange = vec3(0.9f, 0.8f, 0.4f);
    vec3 yellow = vec3(0.9f, 0.5f, 0.2f);
    vec3 white = vec3(1.0f, 1.0f, 1.0f);
    vec3 blue_white = vec3(0.5f, 0.5f, 0.9f);
    vec3 blue = vec3(0.2f, 0.2f, 0.7f);

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

    vec3 color = vec3(1.0f, 0.88f, 0.49f);

    // Maybe we have enable/disable gradient
    color = get_color();
    FragColor = vec4(color,1.0f);
    
    // REC 709 Standard luminance
    // Technically this should not be necessary for our case
    float luminance = dot(vec3(0.2126,0.7152,0.0722), color);
    // FragColorThreshold = vec4(1.0,1.0,1.0,1.0);

    if(luminance > 0.2){
        FragColorThreshold = vec4(color,1.0f);
    } else {
        FragColorThreshold = vec4(0.0f);
        // FragColorThreshold = vec4(0.0f);
    }

}