#ifndef GUI_H
#define GUI_H
#pragma once

#include <GLcommon.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <InputProcessor/InputProcessor.h>
#include <SetupSystem/ParticleBuilder/ParticleBuilder.h>

class GUI
{
public:
    GUI(GLFWwindow * window, InputProcessor * input_processor, ParticleBuilder * particle_builder);
    ~GUI();
    
    void init();
    void render_gui();
    void terminate();

private:
    GLFWwindow * window;
    InputProcessor * input_processor;
    ParticleBuilder * particle_builder;
    ImGuiIO* io;

    bool setup_data_panel_on;

    void control_panel();
    void setup_data_panel();
};

#endif