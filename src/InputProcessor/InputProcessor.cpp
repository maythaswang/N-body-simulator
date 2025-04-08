#include "InputProcessor.h"

InputProcessor::InputProcessor(Simulator *simulator, Renderer *renderer, Bloom *bloom)
{
    this->simulator = simulator;
    this->renderer = renderer;
    this->bloom = bloom;


    this->renderer_gamma =  this->renderer->get_gamma();
    this->renderer_exposure =  this->renderer->get_exposure();
    this->bloom_gamma =  this->bloom->get_gamma();
    this->bloom_exposure =  this->bloom->get_exposure();
}
InputProcessor::~InputProcessor()
{
}

void InputProcessor::process_input()
{
    this->handle_instancing_toggle();
    this->handle_wireframe_toggle();
    this->handle_bloom_toggle();
    this->handle_msize_toggle();
    this->handle_mcolor_toggle();
}

void InputProcessor::imm_handle_pause()
{
    GLuint current_step = this->simulator->get_current_step();
    GLfloat timestep_size = this->simulator->get_timestep_size();
    if (this->simulator->get_running_state())
    {
        std::cout << "The simulation is now paused. Step: " << current_step << ", Time (timestep size): "
                  << current_step * timestep_size << "\nPress p to resume..." << std::endl;
    }
    else
    {
        std::cout << "Resuming simulation..." << std::endl;
    }

    this->simulator->set_running_state(!this->simulator->get_running_state());
    this->simulator_running = this->simulator->get_running_state();
}

void InputProcessor::handle_instancing_toggle()
{
    if (this->instancing_on[0] != this->instancing_on[1])
    {
        this->renderer->set_use_instancing(instancing_on[0]);
        std::string msg = (this->instancing_on[0]) ? "Instancing mode enabled." : "Instancing mode disabled.";
        std::cout << msg << std::endl;
        this->instancing_on[1] = this->instancing_on[0];
    }
}

void InputProcessor::handle_wireframe_toggle()
{
    if (this->wireframe_on[0] != this->wireframe_on[1])
    {
        this->renderer->set_use_wireframe(this->wireframe_on[0]);
        std::string msg = (this->wireframe_on[0]) ? "wireframe mode enabled." : "wireframe mode disabled.";
        std::cout << msg << std::endl;
        this->wireframe_on[1] = this->wireframe_on[0];
    }
}

void InputProcessor::handle_bloom_toggle()
{
    if (this->bloom_on[0] != this->bloom_on[1])
    {
        // bool bloom_state = this->bloom->get_enabled();
        this->bloom->set_enabled(bloom_on[0]);
        this->renderer->set_use_bloom(bloom_on[0]);
        std::string msg = (bloom_on[0]) ? "Bloom enabled." : "Bloom disabled.";
        std::cout << msg << std::endl;
        this->bloom_on[1] = this->bloom_on[0];
    }
}

void InputProcessor::handle_msize_toggle()
{
    if (this->msize_on[0] != this->msize_on[1])
    {
        this->renderer->set_use_msize(this->msize_on[0]);
        std::string msg = (this->msize_on[0]) ? "mass-size enabled." : "mass-size disabled.";
        std::cout << msg << std::endl;
        this->msize_on[1] = this->msize_on[0];
    }
}

void InputProcessor::handle_mcolor_toggle()
{
    if (this->mcolor_on[0] != this->mcolor_on[1])
    {
        this->renderer->set_use_mcolor(this->mcolor_on[0]);
        std::string msg = (this->mcolor_on[0]) ? "mass-color enabled." : "mass-color disabled.";
        std::cout << msg << std::endl;
        this->mcolor_on[1] = this->mcolor_on[0];
    }
}

void InputProcessor::imm_handle_show_setup_log()
{
    std::cout << this->simulator->get_setup_log() << std::endl;
}
void InputProcessor::imm_handle_show_help_msg()
{
    std::cout << g_controls_help << std::endl;
}

void InputProcessor::imm_handle_gui_toggle()
{
    this->gui_on = !this->gui_on;
    std::string msg = (this->gui_on) ? "GUI enabled. (press N to disable)" : "GUI disabled. (press N to enable)";
    std::cout << msg << std::endl;
}

bool InputProcessor::get_simulator_running()
{
    return this->simulator_running;
}

bool InputProcessor::get_gui_on()
{
    return this->gui_on;
}

void InputProcessor::imm_update_bloom_gamma()
{
    this->bloom->set_gamma(this->bloom_gamma);
}

void InputProcessor::imm_update_bloom_exposure()
{
    this->bloom->set_exposure(this->bloom_exposure);
}

void InputProcessor::imm_update_renderer_gamma()
{
    this->renderer->set_gamma(this->renderer_gamma);
}

void InputProcessor::imm_update_renderer_exposure()
{
    this->renderer->set_exposure(this->renderer_exposure);
}

void InputProcessor::imm_reset_renderer()
{
    this->renderer->reset_default();
    this->renderer_gamma =  this->renderer->get_gamma();
    this->renderer_exposure =  this->renderer->get_exposure();
}

void InputProcessor::imm_reset_bloom()
{
    this->bloom->reset_default();
    this->bloom_gamma =  this->bloom->get_gamma();
    this->bloom_exposure =  this->bloom->get_exposure();
}