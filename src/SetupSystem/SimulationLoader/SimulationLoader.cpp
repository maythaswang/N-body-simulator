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
    if (this->simulator == NULL)
    {
        std::cerr << "File saving error: simulator not docked" << std::endl;
        return false;
    }

    return this->write_file(file_name);
}

bool SimulationLoader::write_file(std::string file_name)
{
    if (!this->check_folder())
    {
        return false;
    }

    std::filesystem::path file_path(this->folder_path / file_name);

    if (std::filesystem::exists(file_path))
    {
        std::cerr << "File saving error: file name '" << file_path << "' is already taken." <<  std::endl;
        return false;
    }

    std::ofstream output_file(file_path);

    if (!output_file)
    {
        std::cerr << "Failed to open the file for writing!" << std::endl;
        return false;
    }

    output_file << "Hello, this is a test message!" << std::endl;
    std::cout << "File written successfully!" << std::endl;

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
