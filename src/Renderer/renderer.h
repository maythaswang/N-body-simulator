#pragma once
#include <GLCommon.h>
#include <Shader.h>
#include <Camera.h>
#include <Simulator.h>
#include <CallbackManager.h>

class Renderer
{
public:
    Renderer(CallbackManager *, GLFWwindow *, Shader *, Camera *, Simulator *, GLuint);
    void render();

private:
    GLFWwindow *window;
    Shader *shader_program;
    Camera *camera;
    Simulator *simulator;
    CallbackManager *callback_manager;
    GLuint VAO;
};