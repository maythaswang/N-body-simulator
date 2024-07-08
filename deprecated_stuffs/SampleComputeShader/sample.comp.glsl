#version 430 core

layout (local_size_x = 64, local_size_y = 1, local_size_z = 1) in;

layout (std430, binding=0) buffer one{
	float s[];
};

layout (std430, binding=1) buffer two{
	float t[];
};

layout (std430, binding=2) buffer three{
	float x[];
};

uniform int test_num;

void main() {
	uint id = gl_GlobalInvocationID.x;
	if (id >= 64) return ;
	s[id] += test_num + t[id] + x[id];// + x[id];
}