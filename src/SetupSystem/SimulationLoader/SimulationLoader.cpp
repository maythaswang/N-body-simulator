#include "SimulationLoader.h"

SimulationLoader::SimulationLoader(ParticleBuilder *particle_builder)
{
    this->particle_builder = particle_builder;
    this->input_parser = NULL;
    this->simulator = NULL;
}

SimulationLoader::~SimulationLoader()
{
}

void SimulationLoader::cli_setup()
{
    this->input_parser = InputParser(this->particle_builder);
    this->input_parser.accept_input();
}

void SimulationLoader::gui_setup()
{
    // Do something
}

bool SimulationLoader::save_simulation(std::string file_name)
{
    if (this->simulator != NULL)
    {
        this->write_file(file_name);
        return true;
    }

    return false;
}

bool SimulationLoader::write_file(std::string file_name)
{
    if (!this->check_folder())
    {
        return false;
    }
    
    std::filesystem::path file_path(file_name);
    std::ofstream output_file(file_path);
    if ((output_file).is_open())
    {
        output_file << "Hello, this is a test message!" << std::endl;
        output_file.close();
        std::cout << "File written successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Failed to open the file for writing!" << std::endl;
        return false; 
    }

    return true;
}

bool SimulationLoader::check_folder()
{
    if (!std::filesystem::exists(this->folder_path))
    {
        std::cerr << "Directory does not exist. Creating " << this->folder_path << "..." << std::endl;
        if (!std::filesystem::create_directories(this->folder_path))
        {
            std::cerr << "Failed to create directory " << this->folder_path << std::endl;
            return false;
        }
    }
    return true;
}

void SimulationLoader::link_simulator(Simulator *simulator)
{
    this->simulator = simulator;
}
