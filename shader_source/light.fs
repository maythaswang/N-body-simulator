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

// FIX THIS LATER
vec3 get_color(){
    vec3 star_color = vec3(1.0f, 0.88f, 0.49f);
    // vec4 star_color = color_by_linearized_depth(gl_FragCoord.z);
    // if(star_mass > 10000){ 
    //     star_color = vec4(1.0f, 0.7f, 0.7f, 0.7f);
    // }

    return star_color;
}

void main(){
    // FragColor = vec4(1.0f, 0.88f, 0.49f, 0.7f);
    vec3 color = get_color();
    FragColor = vec4(color,1.0f);
    
    // REC 709 Standard luminance
    // Technically this should not be necessary for our case
    float luminance = dot(vec3(0.2126,0.7152,0.0722), color);
    // FragColorThreshold = vec4(1.0,1.0,1.0,1.0);
    if(luminance > 1){
        FragColorThreshold = vec4(color,1.0f);
    } else {
        FragColorThreshold = vec4(color,1.0f);
        // FragColorThreshold = vec4(0.0f);
    }

}