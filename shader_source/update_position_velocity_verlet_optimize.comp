#version 430 core

layout (local_size_x = 64, local_size_y = 1, local_size_z = 1) in;

layout (std430, binding=0) buffer particle_position{
	vec4 position[];
};

layout (std430, binding=1) buffer particle_velocity{
	vec4 velocity[];
};

layout (std430, binding=2) buffer particle_acceleration{
	vec4 acceleration[];
};

layout (std430, binding=3) buffer particle_mass{
	float mass[];
};

uniform float gravitational_constant;
uniform float softening_factor; 
uniform float timestep_size; 
uniform int n_particle;

vec4 calculate_acceleration(uint id) {
    vec4 acc_tmp = vec4(0.0f);
    vec4 temp_distance;
    vec4 direction;
    float sq_distance;
    float sq_soften = pow(softening_factor, 2);

    for (int i = 0; i < n_particle; i++){
        temp_distance = position[id] - position[i];
        if(temp_distance != vec4(0.0f)){
            direction = -normalize(temp_distance);
            sq_distance = dot(temp_distance,temp_distance);
            acc_tmp += (mass[i]/sqrt(sq_distance+sq_soften)) * direction;
        }
    }
    return acc_tmp;
}


void main() {
	uint id = gl_GlobalInvocationID.x;   
	if (id >= n_particle) return ;
    velocity[id] += acceleration[id] * timestep_size * 0.5;
    position[id] += velocity[id] * timestep_size;

    memoryBarrier();
    barrier();

    acceleration[id] = calculate_acceleration(id) * gravitational_constant;
    
    memoryBarrier();
    barrier();

    velocity[id] += acceleration[id] * timestep_size * 0.5; 
}