#version 430 core

in float star_mass;

out vec4 FragColor;

// FIX THIS LATER
vec4 get_color(){
    vec4 star_color = vec4(1.0f, 0.88f, 0.49f, 0.7f);
    // if(star_mass > 10000){ 
    //     star_color = vec4(1.0f, 0.7f, 0.7f, 0.7f);
    // }

    return star_color;
}

void main(){
    // FragColor = vec4(1.0f, 0.88f, 0.49f, 0.7f);
    FragColor = get_color();
}