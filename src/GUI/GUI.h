#ifndef GUI_H
#define GUI_H
#pragma once

#include <GLcommon.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <InputProcessor/InputProcessor.h>

class GUI
{
public:
    GUI(GLFWwindow * window, InputProcessor * input_processor);
    ~GUI();
    
    void init();
    void render_gui();
    void terminate();

private:
    GLFWwindow * window;
    InputProcessor * input_processor;
    ImGuiIO* io;

    void control_panel();
};

#endif