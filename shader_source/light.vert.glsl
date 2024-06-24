#version 330 core
layout (location = 0) in vec3 v_pos;
void main(){
	gl_PointSize = 10.0f;
	gl_Position = vec4(v_pos.x, v_pos.y, v_pos.z, 1.0);
}