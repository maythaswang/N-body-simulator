#include <Renderer.h>
#include <iostream>
#include <sstream>

Renderer::Renderer(CallbackManager *callback_manager, GLFWwindow *window, Shader *shader_program, Camera *camera, Simulator *simulator, GLuint VAO)
{
    this->window = window;
    this->shader_program = shader_program;
    this->camera = camera;
    this->simulator = simulator;
    this->callback_manager = callback_manager;
    this->VAO = VAO;

    this->frame_count = 0;
    this->start_time = glfwGetTime();
    this->previous_time = this->start_time;
}

void Renderer::render()
{
    this->callback_manager->process_input();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    this->shader_program->use();
    this->shader_program->set_mat4("modelview", this->camera->get_view_matrix() * this->camera->get_model_matrix());
    this->shader_program->set_mat4("projection", this->camera->get_projection_matrix());

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_POINTS, 0, this->simulator->get_n_particle());
    glfwSwapBuffers(window);

    glBindVertexArray(0);

    if (this->simulator->get_running_state())
    {
        this->simulator->next_step();
    }

    this->frame_count += 1;
    this->show_fps();
    glfwPollEvents();
}

// TODO: Change the way to calculate FPS
void Renderer::show_fps()
{
    double cur_time = glfwGetTime();
    double delta_time = cur_time - this->previous_time;
    this->previous_time = delta_time;
    if (delta_time >= 1.0)
    {
        std::stringstream ss;
        ss << "N-BODY SIMULATOR. FPS: " << (double)frame_count / delta_time << ". Time elapsed: " << cur_time;
        glfwSetWindowTitle(this->window, ss.str().c_str());
    }
}