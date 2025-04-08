#version 430 core

// Input
// Maybe implement instancing	
layout(location = 0) in vec3 v_pos;


// Position of item
layout (std430, binding = 0) buffer particle_position { 
	vec4 position[]; 
};

layout (std430, binding = 3) buffer particle_mass { 
	float mass[]; 
};

// Uniform Variables
uniform mat4 modelview;
uniform mat4 projection;
uniform bool use_instancing;
uniform bool use_mass_size;

out float star_mass;

float calculate_mass_scaler(int id){
  float scale = mass[id] / 1000000;
  return min(scale, 15.0f);
}

void main() {
  vec4 new_pos = vec4(0.0);
  float mass_size = 1; 

  if(!use_instancing){
    new_pos = position[gl_VertexID];
    star_mass = mass[gl_VertexID];
  } else {
    if(use_mass_size){
      mass_size += calculate_mass_scaler(gl_InstanceID);
    }


    new_pos = position[gl_InstanceID] + vec4(mass_size * v_pos,1.0);
  
    star_mass = mass[gl_InstanceID];
  }
  new_pos.w=1;
	gl_Position = projection * modelview * new_pos;
}