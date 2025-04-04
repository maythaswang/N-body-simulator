#include "ProgramInit.h"
#include <iostream>

void ProgramInit::initialize_glfw()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize glfw.";
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(error_callback);
}
#ifdef __APPLE__
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

void ProgramInit::initialize_glad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

void ProgramInit::error_callback(int error, const char *description)
{
    fprintf(stderr, "Error %s\n", description);
}

void ProgramInit::get_max_workgroup_info(int max_compute_work_group_count[3], int max_compute_work_group_size[3], int *max_compute_work_group_invocations)
{
    for (int idx = 0; idx < 3; idx++)
    {
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, idx, &max_compute_work_group_count[idx]);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, idx, &max_compute_work_group_size[idx]);
    }
    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, max_compute_work_group_invocations);
}