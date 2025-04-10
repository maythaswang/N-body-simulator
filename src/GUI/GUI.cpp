#include "GUI.h"
#include <iostream>

GUI::GUI(GLFWwindow *window, InputProcessor *input_processor, ParticleBuilder *particle_builder)
{
    this->window = window;
    this->input_processor = input_processor;
    this->particle_builder = particle_builder;
    this->setup_data_panel_on = false;
    this->help_panel_on = true;
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
        if (this->setup_data_panel_on)
        {
            this->setup_data_panel();
        }
        if (this->help_panel_on)
        {
            this->help_panel();
        }
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
    std::string msg;

    // Information Section
    //-------------------------------------------
    ImGui::SeparatorText("N-BODY SIMULATOR");
    ImGui::Text("If you wish to disable GUI, press (N)");
    ImGui::TextColored(ImVec4(1.0, 0.9, 0.7, 1.0), "Performance: %.3f ms/frame (%.1f FPS)", 1000.0f / this->io->Framerate, this->io->Framerate);

    ImGui::Text("Current step %d", this->input_processor->imm_get_current_sim_step());
    ImGui::Text("Time elapsed (timestep) %f", this->input_processor->imm_get_current_sim_step() * this->particle_builder->head_setup_data.timestep_size);
    ImGui::Text("Time elapsed (program) %.2f", glfwGetTime());
    // Pause / Resume Status
    ImGui::Text("Simulator Status:");
    ImGui::SameLine();
    msg = (this->input_processor->get_simulator_running()) ? "Running." : "Paused.";
    ImGui::Text(msg.c_str());

    // Pause / Resume Button
    msg = (this->input_processor->get_simulator_running()) ? "PAUSE" : "RESUME";

    if (ImGui::Button(msg.c_str()))
    {
        this->input_processor->imm_handle_pause();
    }

    // Show other panels section
    //-------------------------------------------
    ImGui::Checkbox("Setup Information Panel", &this->setup_data_panel_on);
    ImGui::Checkbox("Help Panel", &this->help_panel_on);

    // Camera Section
    //-------------------------------------------
    ImGui::SeparatorText("CAMERA");
    msg = (this->input_processor->get_camera_is_orbiting()) ? "ORBIT" : "FREE-FLYING";
    ImGui::TextColored(ImVec4(1.0, 0.9, 0.7, 1.0), "CAMERA MODE:");
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0, 0.9, 0.7, 1.0), msg.c_str());

    glm::vec3 eye = this->input_processor->get_camera_eye();
    glm::vec3 center = this->input_processor->get_camera_center();
    glm::vec3 up = this->input_processor->get_camera_up();
    ImGui::Text("Eye: <%.3f, %.3f, %.3f>", eye.x, eye.y, eye.z);
    ImGui::Text("Center: <%.3f, %.3f, %.3f>", center.x, center.y, center.z);
    ImGui::Text("Up: <%.3f, %.3f, %.3f>", up.x, up.y, up.z);

    if (ImGui::Button("Reset camera position"))
    {
        this->input_processor->imm_handle_camera_reset();
    }
    ImGui::SameLine();

    if (ImGui::Button("Switch Mode"))
    {
        this->input_processor->imm_handle_camera_orbit_toggle();
    }

    // Visual Effects Section
    //-------------------------------------------
    ImGui::SeparatorText("VISUAL EFFECTS");
    ImGui::Columns(2, "VISUAL_EFFECT_CHECKBOX", true);

    ImGui::Checkbox("Instancing", &this->input_processor->instancing_on[0]);
    ImGui::Checkbox("Wireframe", &this->input_processor->wireframe_on[0]);
    ImGui::Checkbox("Bloom", &this->input_processor->bloom_on[0]);

    ImGui::NextColumn();

    ImGui::Checkbox("Mass-Size", &this->input_processor->msize_on[0]);
    ImGui::Checkbox("Mass-Color", &this->input_processor->mcolor_on[0]);

    ImGui::Columns(1);
    if (ImGui::SliderFloat("Bloom Intensity", &this->input_processor->bloom_blur_intensity, 0.0f, 1.0f))
    {
        this->input_processor->imm_update_bloom_blur_intensity();
    }

    ImGui::SeparatorText("COLOR CORRECTION");
    if (ImGui::SliderFloat("Renderer Gamma", &this->input_processor->renderer_gamma, 0.0f, 3.0f))
    {
        this->input_processor->imm_update_renderer_gamma();
    }
    if (ImGui::SliderFloat("Renderer Exposure", &this->input_processor->renderer_exposure, 0.0f, 5.0f))
    {
        this->input_processor->imm_update_renderer_exposure();
    }

    if (ImGui::SliderFloat("Bloom Gamma", &this->input_processor->bloom_gamma, 0.0f, 3.0f))
    {
        this->input_processor->imm_update_bloom_gamma();
    };
    if (ImGui::SliderFloat("Bloom Exposure", &this->input_processor->bloom_exposure, 0.0f, 5.0f))
    {
        this->input_processor->imm_update_bloom_exposure();
    };

    // Color correction Section
    //-------------------------------------------
    ImGui::Columns(2, "COLOR_CORRECTION_RESET", true);

    if (ImGui::Button("Reset Bloom Shader"))
    {
        this->input_processor->imm_reset_bloom();
    }

    ImGui::NextColumn();

    if (ImGui::Button("Reset Renderer Shader"))
    {
        this->input_processor->imm_reset_renderer();
    }

    ImGui::Columns(1);

    ImGui::End();
}

void GUI::setup_data_panel()
{
    HeadSetupData setup_data = this->particle_builder->head_setup_data;

    ImGui::Begin("Setup Information Panel", &this->setup_data_panel_on);

    // General Details Section
    //-------------------------------------------
    ImGui::SeparatorText("GENERAL DETAILS");

    ImGui::Text("GPU Implementation: %s", (setup_data.use_GPU) ? "ON" : "OFF");
    ImGui::Text("Integrator: %s", (setup_data.integrator) ? "Velocity-Verlet" : "Euler");
    ImGui::Text("Particle Setup: %s", (setup_data.use_default) ? "Default Setup" : "Manual Setup");
    if (setup_data.use_default)
    {
        ImGui::SameLine();
        ImGui::Text("ID: %d", setup_data.default_test_number);
    }
    ImGui::Text("Gravitational Constant: %f", setup_data.gravitational_constant);
    ImGui::Text("Timestep Size: %f", setup_data.timestep_size);
    ImGui::Text("Total Particles: %d", setup_data.num_particle);

    ImGui::SeparatorText("PARTICLE SETUP");
    ImGui::Text("The following data is the list of cluster spawned for the current setup.");

    // Tmp variables
    glm::vec3 offset;

    // Disc
    if (this->particle_builder->particle_disc_log.size() > 0)
    {
        ImGui::SeparatorText("Disc Cluster");
        if (ImGui::BeginTable("Disc Cluster", 10))
        {
            // Headers
            ImGui::TableSetupColumn("num particles");
            ImGui::TableSetupColumn("offset");
            ImGui::TableSetupColumn("radius");
            ImGui::TableSetupColumn("width");
            ImGui::TableSetupColumn("min-mass");
            ImGui::TableSetupColumn("max-mass");
            ImGui::TableSetupColumn("min-velocity");
            ImGui::TableSetupColumn("max-velocity");
            ImGui::TableSetupColumn("spiral");
            ImGui::TableSetupColumn("dense center");
            ImGui::TableHeadersRow();

            // Row content
            for (int i = 0; i < this->particle_builder->particle_disc_log.size(); i++) // Let's say we want 5 rows
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%d", this->particle_builder->particle_disc_log[i].num_particles);
                ImGui::TableNextColumn();
                offset = this->particle_builder->particle_disc_log[i].offset;
                ImGui::Text("<%.3f, %.3f, %.3f>", offset.x, offset.y, offset.z);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_disc_log[i].radius);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_disc_log[i].width);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_disc_log[i].min_mass);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_disc_log[i].max_mass);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_disc_log[i].min_velocity);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_disc_log[i].max_velocity);
                ImGui::TableNextColumn();
                ImGui::Text("%d", this->particle_builder->particle_disc_log[i].is_spiral);
                ImGui::TableNextColumn();
                ImGui::Text("%d", this->particle_builder->particle_disc_log[i].is_dense_center);
            }
            ImGui::EndTable();
        }
    }

    // Random
    if (this->particle_builder->particle_random_log.size() > 0)
    {
        ImGui::SeparatorText("Random Cluster");
        if (ImGui::BeginTable("Random Cluster", 7))
        {
            // Headers
            ImGui::TableSetupColumn("num particles");
            ImGui::TableSetupColumn("offset");
            ImGui::TableSetupColumn("radius");
            ImGui::TableSetupColumn("min-mass");
            ImGui::TableSetupColumn("max-mass");
            ImGui::TableSetupColumn("min-velocity");
            ImGui::TableSetupColumn("max-velocity");
            ImGui::TableHeadersRow();

            // Row content
            for (int i = 0; i < this->particle_builder->particle_random_log.size(); i++) // Let's say we want 5 rows
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%d", this->particle_builder->particle_random_log[i].num_particles);
                ImGui::TableNextColumn();
                offset = this->particle_builder->particle_random_log[i].offset;
                ImGui::Text("<%.3f, %.3f, %.3f>", offset.x, offset.y, offset.z);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_random_log[i].radius);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_random_log[i].min_mass);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_random_log[i].max_mass);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_random_log[i].min_velocity);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_random_log[i].max_velocity);
            }
            ImGui::EndTable();
        }
    }

    // Globular Cluster
    if (this->particle_builder->particle_globular_cluster_log.size() > 0)
    {
        ImGui::SeparatorText("Globular Cluster");
        if (ImGui::BeginTable("Globular Cluster", 9))
        {
            // Headers
            ImGui::TableSetupColumn("num particles");
            ImGui::TableSetupColumn("offset");
            ImGui::TableSetupColumn("radius");
            ImGui::TableSetupColumn("center-radius");
            ImGui::TableSetupColumn("min-mass");
            ImGui::TableSetupColumn("max-mass");
            ImGui::TableSetupColumn("min-velocity");
            ImGui::TableSetupColumn("max-velocity");
            ImGui::TableSetupColumn("spiral");
            ImGui::TableHeadersRow();

            // Row content
            for (int i = 0; i < this->particle_builder->particle_globular_cluster_log.size(); i++) // Let's say we want 5 rows
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%d", this->particle_builder->particle_globular_cluster_log[i].num_particles);
                ImGui::TableNextColumn();
                offset = this->particle_builder->particle_globular_cluster_log[i].offset;
                ImGui::Text("<%.3f, %.3f, %.3f>", offset.x, offset.y, offset.z);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_globular_cluster_log[i].radius);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_globular_cluster_log[i].center_radius);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_globular_cluster_log[i].min_mass);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_globular_cluster_log[i].max_mass);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_globular_cluster_log[i].min_velocity);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_globular_cluster_log[i].max_velocity);
                ImGui::TableNextColumn();
                ImGui::Text("%d", this->particle_builder->particle_globular_cluster_log[i].is_spiral);
            }
            ImGui::EndTable();
        }
    }

    // Spherical Cluster
    if (this->particle_builder->particle_sphere_surface_log.size() > 0)
    {
        ImGui::SeparatorText("Spherical Surface Cluster");
        if (ImGui::BeginTable("Spherical Cluster", 9))
        {
            // Headers
            ImGui::TableSetupColumn("num particles");
            ImGui::TableSetupColumn("offset");
            ImGui::TableSetupColumn("radius");
            ImGui::TableSetupColumn("min-mass");
            ImGui::TableSetupColumn("max-mass");
            ImGui::TableSetupColumn("min-velocity");
            ImGui::TableSetupColumn("max-velocity");
            ImGui::TableSetupColumn("spiral");
            ImGui::TableHeadersRow();

            // Row content
            for (int i = 0; i < this->particle_builder->particle_sphere_surface_log.size(); i++) // Let's say we want 5 rows
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%d", this->particle_builder->particle_sphere_surface_log[i].num_particles);
                ImGui::TableNextColumn();
                offset = this->particle_builder->particle_sphere_surface_log[i].offset;
                ImGui::Text("<%.3f, %.3f, %.3f>", offset.x, offset.y, offset.z);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_sphere_surface_log[i].radius);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_sphere_surface_log[i].min_mass);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_sphere_surface_log[i].max_mass);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_sphere_surface_log[i].min_velocity);
                ImGui::TableNextColumn();
                ImGui::Text("%.3f", this->particle_builder->particle_sphere_surface_log[i].max_velocity);
                ImGui::TableNextColumn();
                ImGui::Text("%d", this->particle_builder->particle_sphere_surface_log[i].is_spiral);
            }
            ImGui::EndTable();
        }
    }
    ImGui::End();
}

void GUI::help_panel()
{
    ImGui::Begin("Help and Instructions", &this->help_panel_on);
    ImGui::SeparatorText("WELCOME TO SIMPLE REAL-TIME N-BODY SIMULATOR!");
    ImGui::Text(
        "For this application, we perform real time n-body gravitational simulation\n"
        "where every bodies interact with each other gravitationally.\n"
        "The method currently used is particle-particle. \\(^0^)/\n"
    );
    ImGui::SeparatorText("HOW TO USE");
    ImGui::BulletText("The GUI screen can be toggled at any time with the key (N)");
    ImGui::BulletText("To physicists out there, I really am sorry about the units lol..(;w;)");
    ImGui::BulletText(
        "To use the windows controls, please click on the simulation\n"
        "screen before pressing the keys.");
    ImGui::BulletText("The simulation setup can be viewed by pressing the 'Setup Information Panel'\n"
                      "on the control panel");
    ImGui::BulletText("To close this page, click the x button in the corner");
    ImGui::BulletText("The state logs of the application can be viewed on your terminal");
    ImGui::BulletText("The mass-size/color mode scales the bodies' components based on mass");
    ImGui::SeparatorText("WINDOWS CONTROLS");
    ImGui::Text("   esc                             : exit simulation.\n"
                "   h                               : display controls on the terminal.\n"
                "   p                               : pause / continue the simulation.\n"
                "   o                               : toggle orbit / free-flying mode.\n"
                "   r                               : reset camera to origin.\n"
                "   k                               : toggle instancing.\n"
                "   f                               : toggle wireframe mode.\n"
                "   b                               : toggle bloom.\n"
                "   m                               : toggle mass-size.\n"
                "   c                               : toggle mass-color.\n"
                "   n                               : toggle GUI.\n"
                "\nps. mass-size and wireframe mode only shows when instancing is on\n");
    ImGui::SeparatorText("CAMERA CONTROLS");
    ImGui::Text("   middle mouse drag + left shift  : pan the camera in the mouse drag direction.\n"
                "   middle mouse drag + left ctrl   : zoom in/out by dragging mouse forward and vice \n"
                "                                     versa. (free-flying mode: move forward / backwards.)\n"
                "   middle mouse drag               : orbit the camera about the center in the mouse drag \n"
                "                                     direction. (free-flying mode: rotate the center.)");
    ImGui::End();
}

void GUI::terminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}