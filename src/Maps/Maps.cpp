#include "Maps.hpp"

using namespace RoutingSource;

Maps::Maps(std::shared_ptr<Console> console, std::shared_ptr<Settings> settings) : _console(console), _settings(settings)
{
    this->_console->info("Initializing Maps module...");
    this->_console->info("Maps module initialized.");
}

Maps::~Maps()
{
}

void Maps::frameLoop()
{
    ImGui::Begin("Maps", &this->state);

    ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_NoTickMarks | ImPlotAxisFlags_NoGridLines;
    ImVec2 plotSize = ImGui::GetContentRegionAvail();

    if (ImPlot::BeginPlot("Maps", plotSize, ImPlotFlags_CanvasOnly | ImPlotFlags_Equal)) {
        ImPlot::SetupAxes(0, 0, flags, flags);

        ImVec2 canvasSize = ImPlot::GetPlotPos();
        ImVec2 canvasMax = ImVec2(canvasSize.x + plotSize.x, canvasSize.y + plotSize.y);

        ImPlot::PushPlotClipRect();
        ImPlot::GetPlotDrawList()->AddRectFilled(canvasSize, canvasMax, IM_COL32_BLACK);
        ImPlot::PopPlotClipRect();

        // Tiles Time

        ImPlot::EndPlot();
    }

    ImGui::End();
}