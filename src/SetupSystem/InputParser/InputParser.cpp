#include "InputParser.h"

int TESTCASE_CAP_CPU = 4;
int TESTCASE_CAP_GPU = 33;
GLfloat DEFAULT_TIMESTEP_SIZE = 0.001;
GLfloat DEFAULT_GRAVITATIONAL_CONSTANT = 0.8;

InputParser::InputParser(ParticleBuilder *particle_builder)
{
    this->particle_builder = particle_builder;
}

void InputParser::accept_input()
{
    this->timestep_size = DEFAULT_TIMESTEP_SIZE;
    this->gravitational_constant = DEFAULT_GRAVITATIONAL_CONSTANT;

    int default_cap = TESTCASE_CAP_CPU; // Maximum umber of CPU testers
    std::string input;

    std::cout << "You can now begin by setting up the simulator." << std::endl;

    // Use GPU check
    this->input_YN(this->use_GPU, "Would you like to use the GPU implementation. (Y/N).");
    if (this->use_GPU)
    {
        default_cap = TESTCASE_CAP_GPU; // Maximum number of GPU testers.
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
        load_default_test(this->particle_builder, input_test);
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
    bool integrator;
    std::string input;
    bool add_object;

    do
    {
        std::cout << "Please input the following information separated by spaces. integrator: {0: Euler, 1: Velocity-Verlet}" << std::endl;
        std::cout << "<gravitational constant> <timestep size> <integrator>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> gravitational_constant >> timestep_size >> integrator));

    this->gravitational_constant = gravitational_constant;
    this->timestep_size = timestep_size;
    this->use_velocity_verlet = integrator;

    std::cout << this->gravitational_constant << ' ' << this->timestep_size << std::endl;

    while (true)
    {
        this->input_YN(add_object, "Do you wish to add more particles? (Y/N)");
        if (!add_object)
        {
            break;
        }
        this->populate_simulator();
    }
}

void InputParser::populate_simulator()
{
    std::string input;
    int particle_type;
    while (true)
    {
        std::cout << "Please select the particle primitives." << std::endl;
        std::cout << "[0]: Disc, [1]: Random (x,y,z radius), [2]: Globular Cluster, [3]: Sphere Surface" << std::endl;
        getline(std::cin, input);
        if (std::stringstream(input) >> particle_type)
        {
            if ((particle_type >= 0 & particle_type < 4))
            {
                break;
            }
        }
    }

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
    GLfloat radius, width, min_mass, max_mass, min_velocity, max_velocity;
    glm::vec3 offset;
    bool is_spiral, dense_center;

    this->input_basic_information(&n_particle, &offset);

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
        std::cout << "Please set the characteristic of the disc. {0: disable, 1: enable} \n<spiral> <dense_center>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> is_spiral >> dense_center));
    particle_builder->spawn_disc(n_particle, offset, radius, width, min_mass, max_mass, min_velocity, max_velocity, is_spiral, dense_center);
}

void InputParser::populate_random()
{
    std::string input;
    GLuint n_particle;
    GLfloat radius, min_mass, max_mass, min_velocity, max_velocity;
    glm::vec3 offset;

    input_basic_information(&n_particle, &offset);

    do
    {
        std::cout << "Please input the radius of the particle cluster.\n<radius>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> radius));

    do
    {
        std::cout << "Please input the mass and velocity range.\n<min_mass> <max_mass> <min_velocity> <max_velocity>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> min_mass >> max_mass >> min_velocity >> max_velocity));

    particle_builder->spawn_random(n_particle, offset, radius, min_mass, max_mass, min_velocity, max_velocity);
}

void InputParser::populate_globular_cluster()
{
    std::string input;
    GLuint n_particle;
    GLfloat radius, center_radius, min_mass, max_mass, min_velocity, max_velocity;
    glm::vec3 offset;
    bool is_spiral, is_dense;

    this->input_basic_information(&n_particle, &offset);

    do
    {
        std::cout << "Please input the radius and center radius of the cluster.\n<radius> <center radius>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> radius >> center_radius));

    do
    {
        std::cout << "Please input the mass and velocity range.\n<min_mass> <max_mass> <min_velocity> <max_velocity>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> min_mass >> max_mass >> min_velocity >> max_velocity));

    do
    {
        std::cout << "Please set the characteristic of the cluster. {0: disable, 1: enable} \n<spiral>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> is_spiral));

    particle_builder->spawn_globular_cluster(n_particle, offset, radius, center_radius, min_mass, max_mass, min_velocity, max_velocity, is_spiral, 0);
}

void InputParser::populate_sphere_surface()
{
    std::string input;
    GLuint n_particle;
    GLfloat radius, min_mass, max_mass, min_velocity, max_velocity;
    glm::vec3 offset;
    bool is_spiral;

    this->input_basic_information(&n_particle, &offset);

    do
    {
        std::cout << "Please input the radius of the sphere.\n<radius>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> radius));

    do
    {
        std::cout << "Please input the mass and velocity range.\n<min_mass> <max_mass> <min_velocity> <max_velocity>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> min_mass >> max_mass >> min_velocity >> max_velocity));

    do
    {
        std::cout << "Please set the characteristic of the sphere. {0: disable, 1: enable} \n<spiral>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> is_spiral));

    particle_builder->spawn_sphere(n_particle, offset, radius, min_mass, max_mass, min_velocity, max_velocity, is_spiral);
}

bool InputParser::get_use_GPU()
{
    return this->use_GPU;
}

bool InputParser::get_use_velocity_verlet()
{
    return this->use_velocity_verlet;
}

GLfloat InputParser::get_timestep_size()
{
    return this->timestep_size;
}

GLfloat InputParser::get_gravitational_constant()
{
    return this->gravitational_constant;
}

std::string InputParser::get_summary()
{
    std::cout << std::boolalpha;
    std::string rtn = "";
    rtn.append("Using GPU: " + std::to_string(this->use_GPU) + "\n");
    rtn.append("Using default test: " + std::to_string(this->use_default_test));
    if (this->use_default_test)
    {
        rtn.append('[' + std::to_string(this->default_test) + ']');
    }
    rtn.append("\n");

    rtn.append("Gravitational Constant: " + std::to_string(this->gravitational_constant) + "\n");
    rtn.append("Timestep Size: " + std::to_string(this->timestep_size) + "\n");
    std::string integrator_name = (this->use_velocity_verlet) ? "Velocity-Verlet" : "Euler";
    rtn.append("Integrator: " + integrator_name + "\n\n");
    return rtn;
}

void InputParser::input_basic_information(GLuint *n_particle, glm::vec3 *offset)
{
    std::string input;
    GLfloat x_offset, y_offset, z_offset;
    do
    {
        std::cout << "Please input the amount of particles." << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> *n_particle));

    do
    {
        std::cout << "Please input the amount of offset from origin.\n<x> <y> <z>" << std::endl;
        std::cout << ":" << std::flush;
        getline(std::cin, input);
    } while (!(std::stringstream(input) >> x_offset >> y_offset >> z_offset));

    *offset = glm::vec3(x_offset, y_offset, z_offset);
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

void InputParser::clear_cin()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the remaining \n
}