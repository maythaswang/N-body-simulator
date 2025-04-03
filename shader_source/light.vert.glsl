#version 430 core

// Input
// Maybe implement instancing	
layout(location = 0) in vec3 v_pos;


// Position of item
layout (std430, binding = 0) buffer particle_position { 
	vec4 position[]; 
};

// layout (std430, binding = 3) buffer particle_mass { 
// 	vec4<float> mass[]; 
// };

// Uniform Variables
uniform mat4 modelview;
uniform mat4 projection;

void main() {
//   gl_PointSize = 10.0f;
  // gl_Position = projection * modelview * vec4(v_pos, 1.0);
  vec4 new_pos = position[gl_VertexID];
  new_pos.w=1;
	gl_Position = projection * modelview * new_pos;
}