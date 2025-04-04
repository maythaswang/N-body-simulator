#ifndef DEFAULT_TEST_LOADER_H
#define DEFAULT_TEST_LOADER_H
#pragma once    

#include <GLCommon.h>
#include <ParticleSystem/ParticleBuilder/ParticleBuilder.h>

/**
 * @brief Load default test of choice to the particle builder
 * 
 * @param particle_builder particle_builder pointer
 * @param test_id id of the test selected. 
 */
void load_default_test(ParticleBuilder *, int);

#endif