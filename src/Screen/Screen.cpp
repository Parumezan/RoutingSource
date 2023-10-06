#include "Screen.hpp"

using namespace RoutingSource;

Screen::Screen(std::shared_ptr<Console> console, std::shared_ptr<Settings> settings) : _console(console), _settings(settings)
{
    this->_console->info("Initializing Screen module...");
    try {
        // Initialize the window with GLFW
        if (!glfwInit())
            return;
        this->_window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(1600, 900, "RoutingSource", NULL, NULL), glfwDestroyWindow);
        if (!this->_window)
            return;
        glfwMakeContextCurrent(this->_window.get());

        // Initialize ImGui with GLFW & OpenGL && ImPlot
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImPlot::CreateContext();

        // Initialize Settings
        this->_imguiIniPath = this->_settings->getSettingsPath() + "/imgui.ini";

        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.IniFilename = this->_imguiIniPath.c_str();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(this->_window.get(), true);
        ImGui_ImplOpenGL3_Init("#version 330");

        // Initialize widgets
        this->_resetWidgets = false;
        this->_widgetStatus = this->_settings->getWidgetsStatus();
        this->_console->state = this->_widgetStatus["Console"];
        this->_settings->state = this->_widgetStatus["Settings"];

        // Initialize things after initializing GUI if needed (like images)
        // this->_moon.initFrame();
        // this->_cameraManager.initFrame();
        // this->_imgViewer->initFrame();

        // Load the settings
        this->loadConfig();
    } catch (const std::exception &error) {
        this->_console->throwException(error.what());
    }
    this->_console->info("Screen module initialized");
    this->windowLoop();
}

Screen::~Screen()
{
    // Save the settings
    this->_console->info("Closing save settings...");
    this->saveWidgetsStatus();
    this->_settings->saveSettings(this->_widgetStatus);

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwDestroyWindow(this->_window.get());
    glfwTerminate();
}

void Screen::loadConfig()
{
    ImPlot::GetStyle().UseLocalTime = this->_settings->getSettingsVar("IMPLOT_UseLocalTime") == "true" ? true : false;
    ImPlot::GetStyle().UseISO8601 = this->_settings->getSettingsVar("IMPLOT_UseISO8601") == "true" ? true : false;
    ImPlot::GetStyle().Use24HourClock = this->_settings->getSettingsVar("IMPLOT_Use24HourClock") == "true" ? true : false;
}

void Screen::windowLoop()
{
    this->_console->info("Starting window loop...");
    while (!glfwWindowShouldClose(this->_window.get())) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Dockspace
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        // Main menu bar
        this->mainMenuBar();

        // Render the window
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap the buffers
        glfwSwapBuffers(this->_window.get());
        glfwPollEvents();
    }
}

void Screen::saveWidgetsStatus()
{
    this->_widgetStatus["Console"] = this->_console->state;
    this->_widgetStatus["Settings"] = this->_settings->state;
}

void Screen::resetWidgetsStatus()
{
    if (this->_resetWidgets) {
        this->_console->state = false;
        this->_settings->state = false;

        // update the reset status
        this->_resetWidgets = false;
    }
}

void Screen::mainMenuBar()
{
    if (this->_console->state)
        this->_console->frameLoop();
    if (this->_settings->state)
        this->_settings->frameLoop();

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit", "Ctrl+Q"))
                glfwSetWindowShouldClose(this->_window.get(), true);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Settings")) {
            ImGui::MenuItem("Preferences", "Ctrl+P", &this->_settings->state);
            ImGui::MenuItem("Reset Widgets", "Ctrl+R", &this->_resetWidgets);
            // ImGui::Separator();
            // ImGui::MenuItem("Save Config", "Ctrl+Shift+S", &);
            // TODO Themes choices
            ImGui::Separator();
            ImGui::MenuItem("Console", "Ctrl+O", &this->_console->state);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    this->resetWidgetsStatus();
}