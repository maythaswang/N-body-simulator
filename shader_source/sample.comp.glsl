#version 430 core

layout (local_size_x = 64, local_size_y = 10, local_size_z = 1) in;

layout (std430, binding=0) buffer f{
	float s[];
};

void main() {
	uint id = gl_GlobalInvocationID.x;
	if (id >= 64) return ;
	s[id] +=1;
}