#version 430 core

// Input
layout (location = 0) in vec3 v_pos;

// Uniform Variables
uniform mat4 modelview;
uniform mat4 projection;

void main(){
	gl_PointSize = 10.0f;
	gl_Position = projection * modelview * vec4(v_pos, 1.0);
}