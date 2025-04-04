#version 430 core

in float star_mass;

out vec4 FragColor;

// Just fun stuffs (colour based on depth)
vec4 color_by_linearized_depth(float depth) 
{
    float near = 100; //real value is 0.1
    float far  = 20000.0;  // real value is pretty big number
    float z = depth * 2.0 - 1.0; // back to NDC 
    vec4 new_color = vec4(vec3(((2.0 * near * far) / (far + near - z * (far - near)))/far),0.7f);	
    new_color.x = 1.0f;
    return new_color;
}

// FIX THIS LATER
vec4 get_color(){
    vec4 star_color = vec4(1.0f, 0.88f, 0.49f, 0.7f);
    // vec4 star_color = color_by_linearized_depth(gl_FragCoord.z);
    // if(star_mass > 10000){ 
    //     star_color = vec4(1.0f, 0.7f, 0.7f, 0.7f);
    // }

    return star_color;
}

void main(){
    // FragColor = vec4(1.0f, 0.88f, 0.49f, 0.7f);
    FragColor = get_color();
}