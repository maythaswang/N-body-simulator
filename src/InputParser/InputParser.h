#pragma once
#include <GLcommon.h>
#include <ParticleBuilder.h>

#include <iostream>
#include <string>

class InputParser
{
public:
    InputParser(ParticleBuilder *);

    void accept_input();
    void print_summary();
    bool get_use_GPU();

private:
    ParticleBuilder *particle_builder;
    GLuint default_test, n_particle;
    bool use_GPU, use_default_test;

    void input_YN(bool &output, std::string message);
    void load_default_test();

};