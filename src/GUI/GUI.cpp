#include "GUI.h"
#include <iostream>

GUI::GUI(GLFWwindow *window)
{
    this->window = window;
    this->init();
}

GUI::~GUI()
{
}

void GUI::init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO *io = &ImGui::GetIO();
    this->io = io;
    (void)io;

    // Set io flags
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 430");
}

void GUI::render_gui()
{
    // Clean the back buffer and assign the new color to it
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Render Components
    this->control_panel();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiConfigFlags im = this->io->ConfigFlags;

    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    if (this->io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void GUI::control_panel(){
    ImGui::Begin("Test window");
    ImGui::Text("Test text!");
    // ImGui::Checkbox("do something", &do_something);

    if (ImGui::Button("Pause")){
        // Pause 
    }   
    ImGui::SameLine();
    ImGui::Text("pausing?");
    ImGui::End();
}

void GUI::terminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}