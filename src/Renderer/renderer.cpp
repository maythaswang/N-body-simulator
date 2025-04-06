#include "Renderer.h"
#include <iostream>
#include <sstream>

Renderer::Renderer(GLFWwindow *window, Shader *shader_program, Camera *camera, Simulator *simulator, RenderComponents *render_components)
{
    this->window = window;
    this->shader_program = shader_program;
    this->camera = camera;
    this->simulator = simulator;
    this->render_components = render_components;

    this->frame_count = 0;
    this->start_time = glfwGetTime();
    this->previous_time = this->start_time;

    // Configuration
    this->use_instancing = false;
    this->use_wireframe = false;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearColor(0.05f, 0.05f, 0.07f, 1.0f);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwSwapInterval(1);
}

void Renderer::render()
{
    // Begin
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    }

    // Post processing
    this->post_processing();

    // End frame
    // glfwSwapBuffers(window);
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

bool Renderer::get_use_instancing()
{
    return this->use_instancing;
}

void Renderer::set_use_instancing(bool use_instancing)
{
    this->use_instancing = use_instancing;
}

bool Renderer::get_use_wireframe()
{
    return this->use_wireframe;
}

void Renderer::set_use_wireframe(bool use_wireframe)
{
    this->use_wireframe = use_wireframe;

    if (use_wireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
