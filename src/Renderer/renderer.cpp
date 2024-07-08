#include <Renderer.h>
#include <iostream>

Renderer::Renderer(CallbackManager* callback_manager,GLFWwindow *window, Shader *shader_program, Camera *camera, Simulator *simulator, GLuint VAO)
{
    this->window = window;
    this->shader_program = shader_program;
    this->camera = camera;
    this->simulator = simulator;
    this->callback_manager = callback_manager;
    this->VAO = VAO;
}

void Renderer::render()
{
    this->callback_manager->process_input();
    this->shader_program->set_mat4("modelview", this->camera->get_view_matrix() * this->camera->get_model_matrix());
    this->shader_program->set_mat4("projection", this->camera->get_projection_matrix());
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    this->shader_program->use();
    
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_POINTS, 0, this->simulator->get_n_particle());
    glfwSwapBuffers(window);

    glBindVertexArray(0);
    
    if (this->simulator->get_running_state())
    {
        this->simulator->next_step();
    }
    glfwPollEvents();
}
