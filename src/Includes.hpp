#ifndef INCLUDES_HPP_
#define INCLUDES_HPP_

#include <GLFW/glfw3.h>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <memory>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <vector>

// ImGui & OpenGL & GLFW
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// ImPlot
#include "implot.h"

// ImGuiFileDialog
#include "ImGuiFileDialog.h"

// Dirent
#ifdef _WIN32
    #include "dirent.h"
#endif

// curlpp
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>

// nlohmann/json
#include <nlohmann/json.hpp>

// sqlite3
#include <sqlite3.h>

namespace RoutingSource
{
    enum ConsoleType {
        INFO,
        WARN,
        ERROR
    };

    static const std::vector<std::string> WidgetNames = {"Console", "Settings"};

} // namespace RoutingSource

#endif /* !INCLUDES_HPP_ */