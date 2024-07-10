#include <InputParser.h>

InputParser::InputParser(ParticleBuilder *particle_builder)
{
    this->particle_builder = particle_builder;
}

void InputParser::accept_input()
{
    this->default_test = 1000;
    int default_cap = 4; // Maximum umber of CPU testers
    std::string input;

    std::cout << "You can now begin by setting up the simulator." << std::endl;

    // Use GPU check
    this->input_YN(this->use_GPU, "Would you like to use the GPU implementation. (Y/N).");
    if (this->use_GPU)
    {
        default_cap = 24; // Maximum number of GPU testers.
    }

    // Use default tests check.
    this->input_YN(this->use_default_test, "Would you like to load one of the default tests (Y/N).");

    // Select default test.
    if (this->use_default_test)
    {
        int input_test;
        while (true)
        {
            std::cout << "Please input the index of default test you wish to load. [0-" << default_cap << ']' << std::endl;
            std::cout << ":" << std::flush;
            getline(std::cin, input);

            if (std::stringstream(input) >> input_test)
            {
                if (input_test <= default_cap && input_test >= 0)
                    break;
            }
        }

        this->default_test = input_test;
        this->load_default_test();
    }
    // Manual Setup
    else
    {
        std::cout << "The manual setup will now begin..." << std::endl;
        this->manual_setup();
    }
}

void InputParser::manual_setup()
{
    GLfloat gravitational_constant, timestep_size;
    std::string input;
    bool add_object;

    do
    {
        std::cout << "Please input the following information separated by spaces." << std::endl;
        std::cout << "<gravitational constant> <timestep size>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> gravitational_constant >> timestep_size));

    this->gravitational_constant = gravitational_constant;
    this->timestep_size = timestep_size;
    std::cout << this->gravitational_constant << ' ' << this->timestep_size << std::endl;

    do
    {
        this->input_YN(add_object, "Do you wish to add more particles? (Y/N)");
        this->populate_simulator();
    } while (add_object);
}

void InputParser::populate_simulator()
{
    clear_cin();
    int particle_type = 4;
    do
    {
        std::cout << "Please select the particle primitives." << std::endl;
        std::cout << "[0]: Disc, [1]: Random (x,y,z radius), [2]: Globular Cluster, [3]: Sphere Surface" << std::endl;
        std::cin >> particle_type;
    } while (particle_type > 4);

    clear_cin();

    switch (particle_type)
    {
    case 0:
        this->populate_disc();
        break;

    case 1:
        this->populate_random();
        break;

    case 2:
        this->populate_globular_cluster();
        break;

    case 3:
        this->populate_sphere_surface();
        break;

    default:
        break;
    }
}

void InputParser::populate_disc()
{
    std::string input;
    GLuint n_particle;
    GLfloat x_offset, y_offset, z_offset;
    GLfloat radius, width;
    GLfloat min_mass, max_mass, min_velocity, max_velocity;
    bool is_spiral;

    do
    {
        std::cout << "Please input the amount of particles." << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> n_particle));

    do
    {
        std::cout << "Please input the amount of offset from origin.\n<x> <y> <z>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> x_offset >> y_offset >> z_offset));

    do
    {
        std::cout << "Please input the radius and width of the disc.\n<radius> <width>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> radius >> width));

    do
    {
        std::cout << "Please input the mass and velocity range.\n<min_mass> <max_mass> <min_velocity> <max_velocity>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> min_mass >> max_mass >> min_velocity >> max_velocity));

    do
    {
        std::cout << "Please set the characteristic of the disc. {0: disable, 1: enable} \n<spiral>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> is_spiral));
    // std::cout << "Please input the following information separated by spaces." << std::endl;
    particle_builder->spawn_disc(n_particle, glm::vec3(x_offset, y_offset, z_offset), radius, width, min_mass, max_mass, min_velocity, max_velocity, is_spiral);
}

void InputParser::populate_random()
{
}

void InputParser::populate_globular_cluster()
{
}

void InputParser::populate_sphere_surface()
{
}

bool InputParser::get_use_GPU()
{
    return this->use_GPU;
}

void InputParser::input_YN(bool &output, std::string message)
{
    char status;
    std::string input;
    while (true)
    {
        std::cout << message << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
        if (std::stringstream(input) >> status)
        {
            if (status == 'Y' | status == 'N')
                break;
        }
    }
    output = (status == 'Y') ? true : false;
}

void InputParser::print_summary()
{
    std::cout << std::boolalpha;

    std::cout << "+-------------------------------------------+" << std::endl;
    std::cout << "| Setup Summary                             |" << std::endl;
    std::cout << "+-------------------------------------------+\n"
              << std::endl;

    std::cout << "  Using GPU: " << this->use_GPU << std::endl;
    std::cout << "  Using default test: " << this->use_default_test;
    if (this->use_default_test)
    {
        std::cout << '[' << this->default_test << ']';
    }
    std::cout << std::endl;

    std::cout << "\n--------------------------------------------" << std::endl;
}

void InputParser::clear_cin()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the remaining \n
}

// TODO: Make this one use the same format as user input (String). Use the parser instead so records can be tracked easily. Also if possible move it to another file...
void InputParser::load_default_test()
{
    switch (this->default_test)
    {
    case (0):
        this->particle_builder->spawn_globular_cluster(500, glm::vec3(-550, -700, 0), 200, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(500, glm::vec3(470, 650, 0), 200, 25, 1000, 100000, 10, 1000, false, true, false);
        break;

    case (1):
        this->particle_builder->spawn_globular_cluster(1000, glm::vec3(0, 0, 0), 200, 25, 1000, 100000, -1000, 1000, false, false, false);
        break;

    case (2):
        this->particle_builder->spawn_globular_cluster(1000, glm::vec3(0, 0, 0), 700, 50, 1000, 100000, -1000, 1000, false, true, false);
        break;

    case (3):
        this->particle_builder->spawn_globular_cluster(1000, glm::vec3(0, 0, 0), 500, 50, 1000, 100000, 0, 0, false, true, false);
        break;

    case (4):
        this->particle_builder->spawn_random(100, glm::vec3(0.0f), 500, 1000, 100000, 0, 1000);
        break;

    case (5):
        this->particle_builder->spawn_globular_cluster(10000, glm::vec3(0, 0, 0), 700, 50, 1000, 100000, -1000, 1000, false, true, false);
        break;

    case (6):
        this->particle_builder->spawn_globular_cluster(9999, glm::vec3(0, 0, 0), 10000, 50, 1000, 100000, -100, 100, false, true, false);
        break;

    case (7):
        this->particle_builder->spawn_globular_cluster(10000, glm::vec3(0, 0, 0), 100000, 50, 1000, 100000, -100, 100, false, true, false);
        break;

    case (8):
        this->particle_builder->spawn_globular_cluster(10000, glm::vec3(0, 0, 0), 50000, 50, 1000, 100000, -100, 100, false, false, true);
        break;

    case (9):
        this->particle_builder->spawn_globular_cluster(5000, glm::vec3(-550, -600, 0), 200, 25, 1000, 100000, 10, 1000, false, false, false);
        this->particle_builder->spawn_globular_cluster(5000, glm::vec3(470, 450, 0), 200, 25, 1000, 100000, 10, 1000, false, false, false);
        break;

    case (10):
        this->particle_builder->spawn_globular_cluster(2500, glm::vec3(-550, -600, 0), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(2500, glm::vec3(470, 450, 54), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(2500, glm::vec3(124, -2634, -156), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(2500, glm::vec3(-470, 440, -48), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        break;

    case (11):
        this->particle_builder->spawn_globular_cluster(1000, glm::vec3(470, 450, 54), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(1000, glm::vec3(-550, -600, 0), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(1000, glm::vec3(124, -2634, -156), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(1000, glm::vec3(-470, 440, -48), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(1000, glm::vec3(1470, 3440, -4238), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(1000, glm::vec3(-470, 41243, 248), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(1000, glm::vec3(-470, 150, -48), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(1000, glm::vec3(3170, 49, 4488), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(1000, glm::vec3(570, 330, -48), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(1000, glm::vec3(0, 0, 0), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        break;

    case (12):
        this->particle_builder->spawn_globular_cluster(1500, glm::vec3(470, 450, 54), 10000, 25, 1000, 100000, -1000, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(800, glm::vec3(-550, -600, 0), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(800, glm::vec3(124, -2634, -156), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(500, glm::vec3(-470, 440, -48), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(500, glm::vec3(1470, 3440, -4238), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(500, glm::vec3(-470, 41243, 248), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(500, glm::vec3(-470, 150, -48), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(600, glm::vec3(3170, 49, 4488), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(100, glm::vec3(570, 330, -48), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(200, glm::vec3(0, 0, 0), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(1000, glm::vec3(470, 450, 54), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(200, glm::vec3(250, -600, 887), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(200, glm::vec3(828, -2634, -827), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(200, glm::vec3(-8272, 551, -254), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(200, glm::vec3(52, 8, -4238), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(200, glm::vec3(-85, 5452, 248), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(500, glm::vec3(-425, 1550, -28), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(500, glm::vec3(340, 45, 52), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(500, glm::vec3(5702, 330, -548), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        this->particle_builder->spawn_globular_cluster(500, glm::vec3(5, 50, 750), 10000, 25, 1000, 100000, 10, 1000, false, true, false);
        break;

    case (13):
        this->particle_builder->spawn_globular_cluster(9000, glm::vec3(0, 0, 0), 10000, 25, 1000, 100000, 10, 1000, false, false, true);
        this->particle_builder->spawn_globular_cluster(1000, glm::vec3(0, 0, 0), 500, 25, 100000, 10000000, 10, 1000, false, true, false);
        break;

    case (14):
        this->particle_builder->spawn_globular_cluster(20000, glm::vec3(0, 0, 0), 10000, 25, 1000, 10000, 10, 1000, false, false, true);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(0, 0, 0), 1, 0, 10000000, 10000000, 0, 0, false, false, false);
        break;

    case (15):
        this->particle_builder->spawn_globular_cluster(29999, glm::vec3(0, 0, 0), 10, 25, 0, 0, -1000, 1000, false, false, true);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(500, 500, 500), 1, 0, 10000000, 10000000, -1000, 1000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(-500, 500, 500), 1, 0, 10000000, 10000000, -1000, 1000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(-500, -500, -500), 1, 0, 10000000, 10000000, -1000, 1000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(500, -500, -500), 1, 0, 10000000, 10000000, -1000, 1000, false, false, false);
        break;
    case (16):
        this->particle_builder->spawn_globular_cluster(20000, glm::vec3(0, 0, 0), 10, 25, 0, 0, -1000, 1000, false, false, true);
        this->particle_builder->spawn_globular_cluster(200, glm::vec3(5000, 5000, 5000), 1, 0, 10000000, 10000000, -1000, 1000, false, false, false);
        this->particle_builder->spawn_globular_cluster(200, glm::vec3(-5000, -5000, -5000), 1, 0, 10000000, 10000000, -1000, 1000, false, false, false);
        this->particle_builder->spawn_globular_cluster(200, glm::vec3(-5000, 5000, -5000), 1, 0, 10000000, 10000000, -1000, 1000, false, false, false);
        break;
    case (17):
        this->particle_builder->spawn_globular_cluster(20000, glm::vec3(0, 0, 0), 10, 25, 1, 1, -1000, 1000, false, false, true);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(5000, 5000, 5000), 10000, 0, 100000000, 100000000, -10000, 10000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(5000, 5000, -5000), 10000, 0, 100000000, 100000000, -10000, 10000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(5000, -5000, 5000), 10000, 0, 100000000, 100000000, -10000, 10000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(-5000, 5000, 5000), 10000, 0, 100000000, 100000000, -10000, 10000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(-5000, -5000, 5000), 10000, 0, 100000000, 100000000, -10000, 10000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(5000, -5000, -5000), 10000, 0, 100000000, 100000000, -10000, 10000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(-5000, -5000, -5000), 10000, 0, 100000000, 100000000, -10000, 10000, false, false, false);
        break;
    case (18):
        this->particle_builder->spawn_globular_cluster(20000, glm::vec3(0, 0, 0), 10, 5, 1, 1, -1000, 1000, false, false, true);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(5000, 5000, 5000), 10000, 0, 1000000000, 1000000000, -10000, -10000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(5000, 5000, -5000), 10000, 0, 1000000000, 1000000000, -10000, -10000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(5000, -5000, 5000), 10000, 0, 1000000000, 1000000000, -10000, 10000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(-5000, 5000, 5000), 10000, 0, 1000000000, 1000000000, -10000, 10000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(-5000, -5000, 5000), 10000, 0, 1000000000, 1000000000, 10000, -10000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(5000, -5000, -5000), 10000, 0, 1000000000, 1000000000, 10000, -10000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(-5000, 5000, -5000), 10000, 0, 1000000000, 1000000000, 10000, 10000, false, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(-5000, -5000, -5000), 10000, 0, 1000000000, 1000000000, 10000, 10000, false, false, false);
        break;

    case (19):

        this->particle_builder->spawn_globular_cluster(1, glm::vec3(0, 0, 0), 2, 2, 100000000, 100000000, 0, 0, false, false, true);
        this->particle_builder->spawn_globular_cluster(40000, glm::vec3(0, 0, 0), 2, 2, 1000000, 1000000, 0, 0, false, false, true);
        // this->particle_builder->spawn_globular_cluster(20000, glm::vec3(0, 0, 0), 1000000, 5, 1, 1, -1000, 1000, false, false, true);
        // this->particle_builder->spawn_globular_cluster(1, glm::vec3(0, 0, 0), 10,10, 10000000000, 10000000000, 0, 0, false, false, false);
        // this->particle_builder->spawn_globular_cluster(1, glm::vec3(5000, 5000, -5000), 10,10, 10000000000, 10000000000, 0, 0, false, false, false);
        // this->particle_builder->spawn_globular_cluster(1, glm::vec3(-5000, 5000, 5000), 10,10, 10000000000, 10000000000, 0, 0, false, false, false);
        break;
    case (20):
        this->particle_builder->spawn_globular_cluster(7000, glm::vec3(10000, 0, 0), 5, 5, 10000000, 10000000, 0, 0, false, false, true);
        this->particle_builder->spawn_globular_cluster(7000, glm::vec3(0, 10000, 0), 5, 5, 10000000, 10000000, 0, 0, false, false, true);
        this->particle_builder->spawn_globular_cluster(7000, glm::vec3(-10000, 0, 0), 5, 5, 10000000, 10000000, 0, 0, false, false, true);
        this->particle_builder->spawn_globular_cluster(7000, glm::vec3(0, -10000, 0), 5, 5, 10000000, 10000000, 0, 0, false, false, true);
        break;

    case (21):
        this->particle_builder->spawn_globular_cluster(20000, glm::vec3(0, 0, 0), 100, 1000, 10000, 100000, 10000, 100000, true, false, false);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(0, 0, 0), 1, 0, 10000000, 10000000, 10000, 10000, true, false, true);
        break;

    case (22):
        this->particle_builder->spawn_globular_cluster(20000, glm::vec3(0, 0, 0), 1000, 10000, 100000, 1000000, 10000, 100000, true, false, false);

        this->particle_builder->spawn_globular_cluster(1, glm::vec3(0, 0, 0), 1, 0, 10000000, 10000000, 0, 0, true, false, true);
        break;

    case (23):
        this->particle_builder->spawn_globular_cluster(10000, glm::vec3(1000, 0, 0), 1000, 10000, 1, 1, 1000, 10000, true, false, false);
        this->particle_builder->spawn_globular_cluster(10000, glm::vec3(-1000, 0, 0), 1000, 10000, 1, 1, 1000, 10000, true, false, false);
        this->particle_builder->spawn_globular_cluster(100, glm::vec3(0, 0, 0), 1, 0, 10000000, 10000000, 0, 0, true, false, true);
        break;

    case (24):
        this->particle_builder->spawn_disc(20000, glm::vec3(-10000, 0, 0), 1000, 20, 100000, 1000000, 10000, 100000, true);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(-10000, 0, 0), 1, 0, 1000000, 1000000, 0, 0, true, false, true);

        this->particle_builder->spawn_disc(20000, glm::vec3(10000, 0, 0), 1000, 20, 100000, 1000000, 10000, 100000, true);
        this->particle_builder->spawn_globular_cluster(1, glm::vec3(10000, 0, 0), 1, 0, 1000000, 1000000, 0, 0, true, false, true);
        break;

    default:
        break;
    }
}
