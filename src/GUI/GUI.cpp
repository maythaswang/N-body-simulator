#include "GUI.h"
#include <iostream>

GUI::GUI(GLFWwindow *window, InputProcessor *input_processor)
{
    this->window = window;
    this->input_processor = input_processor;
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
    if (this->input_processor->get_gui_on())
    {
        this->control_panel();
    }

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

void GUI::control_panel()
{
    ImGui::Begin("Control Panel");
    
    // Information Section
    ImGui::SeparatorText("N-BODY SIMULATOR");
    ImGui::Text("If you wish to disable GUI, press (N)");
    ImGui::TextColored(ImVec4(1.0, 0.9, 0.7, 1.0), "Performance: %.3f ms/frame (%.1f FPS)", 1000.0f / this->io->Framerate, this->io->Framerate);

    // Pause / Resume Button
    std::string msg = (this->input_processor->get_simulator_running()) ? "PAUSE" : "RESUME";

    if (ImGui::Button(msg.c_str()))
    {
        this->input_processor->imm_handle_pause();
    }

    // Pause / Resume Status
    ImGui::Text("Simulator Status:");
    ImGui::SameLine();
    msg = (this->input_processor->get_simulator_running()) ? "Running." : "Paused.";
    ImGui::Text(msg.c_str());


    ImGui::SeparatorText("EFFECTS");
    
    // 2 Columns for effects
    ImGui::Columns(2, "Buttons", true);

    ImGui::Checkbox("Instancing", &this->input_processor->instancing_on[0]);
    ImGui::Checkbox("Wireframe", &this->input_processor->wireframe_on[0]);
    ImGui::Checkbox("Bloom", &this->input_processor->bloom_on[0]);

    ImGui::NextColumn();

    ImGui::Checkbox("Mass-Size", &this->input_processor->msize_on[0]);
    ImGui::Checkbox("Mass-Color", &this->input_processor->mcolor_on[0]);

    ImGui::Columns(1); 


    ImGui::End();
}

void GUI::terminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}