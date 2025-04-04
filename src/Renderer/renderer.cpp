#include <Renderer.h>
#include <iostream>
#include <sstream>

Renderer::Renderer(CallbackManager *callback_manager, GLFWwindow *window, Shader *shader_program, Camera *camera, Simulator *simulator, RenderComponents *render_components)
{
    this->window = window;
    this->shader_program = shader_program;
    this->camera = camera;
    this->simulator = simulator;
    this->callback_manager = callback_manager;
    this->render_components = render_components;

    this->frame_count = 0;
    this->start_time = glfwGetTime();
    this->previous_time = this->start_time;

    // Configuration
    this->use_instancing = true; // TODO: We have no handler for this yet
}

void Renderer::render()
{
    // Handle inputs
    glfwPollEvents();
    this->callback_manager->process_input();

    // Begin
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render
    this->shader_program->use();
    this->shader_program->set_mat4("modelview", this->camera->get_view_matrix() * this->camera->get_model_matrix());
    this->shader_program->set_mat4("projection", this->camera->get_projection_matrix());
    this->shader_program->set_bool("use_instancing", this->use_instancing);

    glBindVertexArray(this->render_components->VAO);
    if (!this->use_instancing)
    {
        glDrawArrays(GL_POINTS, 0, this->simulator->get_n_particle());
    }
    else
    {
        glDrawElementsInstanced(GL_TRIANGLES, 3 * this->render_components->n_inds, GL_UNSIGNED_INT, (void *)0, this->simulator->get_n_particle());
        // glDrawArraysInstanced(GL_TRIANGLES, 0, this->render_components->n_inds, this->simulator->get_n_particle()); // This created some insane stuff (I like it but it gotta go)
    }

    // Post processing
    this->post_processing();

    // End frame
    glfwSwapBuffers(window);
    glBindVertexArray(0);
    this->frame_count += 1;
    this->show_fps();

    // Prepare for next frame (we don't call this first so that the first frame will have the simulation set at the orignal position)
    if (this->simulator->get_running_state())
    {
        this->simulator->next_step();
    }
}

void Renderer::show_fps()
{
    double cur_time = glfwGetTime();
    double delta_time = cur_time - this->previous_time;
    this->previous_time = cur_time;
    std::stringstream ss;
    ss << std::fixed;
    ss.precision(2);

    ss << "N-BODY SIMULATOR. FPS: " << 1.0 / delta_time << ". Time elapsed: " << cur_time;
    glfwSetWindowTitle(this->window, ss.str().c_str());
}

// Post processing stage
void Renderer::post_processing()
{
    // TODO: do bloom or sth here
}

bool Renderer::get_use_instancing(){
    return this->use_instancing;
}

void Renderer::set_use_instancing(bool use_instancing){
    this->use_instancing = use_instancing;
}