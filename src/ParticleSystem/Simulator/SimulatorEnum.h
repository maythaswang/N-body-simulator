#ifndef SIMULATOR_ENUM_H
#define SIMULATOR_ENUM_H
#pragma once

enum SimulatorIntegrator
{
    INTEGRATOR_EULER,
    INTEGRATOR_VELOCITY_VERLET,
};

enum SimulatorImplementation
{
    PP_CPU_NAIVE,
    PP_GPU_NAIVE,
    PP_GPU_OPTIMIZE,
};

#endif 