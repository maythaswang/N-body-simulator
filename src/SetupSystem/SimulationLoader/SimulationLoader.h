#ifndef SIMULATION_LOADER_H
#define SIMULATION_LOADER_H
#include <GLCommon.h>
#include <SetupSystem/ParticleBuilder/ParticleBuilder.h>
#include <SetupSystem/InputParser/InputParser.h>
#include <SetupSystem/DefaultTestLoader/DefaultTestLoader.h>
#include <ParticleSystem/Simulator/Simulator.h>

#include <filesystem>
#include <iostream>
#include <fstream>

class SimulationLoader
{
public:
    SimulationLoader(ParticleBuilder *particle_builder);
    ~SimulationLoader();
    void cli_setup();
    void gui_setup();
    bool save_simulation(std::string file_name);
    void link_simulator(Simulator *simulator);
    void load_simulation(std::string file_name);

private:
    ParticleBuilder *particle_builder;
    InputParser input_parser;
    Simulator *simulator;

    std::filesystem::path folder_path = "simulation_saves";

    bool write_file(std::string filename);
    bool check_folder();
};

#endif