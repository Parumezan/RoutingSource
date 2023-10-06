#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include "Console.hpp"
#include "Includes.hpp"
#include "Settings.hpp"

namespace RoutingSource
{
    class Screen
    {
        private:
            std::shared_ptr<GLFWwindow> _window;
            std::shared_ptr<Console> _console;
            std::shared_ptr<Settings> _settings;
            std::string _imguiIniPath;
            bool _resetWidgets;

            std::map<std::string, bool> _widgetStatus;
            void loadConfig();
            void windowLoop();
            void saveWidgetsStatus();
            void resetWidgetsStatus();
            void mainMenuBar();

        public:
            Screen(std::shared_ptr<Console> console, std::shared_ptr<Settings> settings);
            ~Screen();
    };
} // namespace RoutingSource

#endif /* !SCREEN_HPP_ */