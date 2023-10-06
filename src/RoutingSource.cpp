#include "Console.hpp"
#include "Includes.hpp"
#include "Screen.hpp"
#include "Settings.hpp"

using namespace RoutingSource;

int main(void)
{
    std::shared_ptr<Console> console = std::make_shared<Console>();
    std::shared_ptr<Settings> settings = std::make_shared<Settings>(console);
    Screen screen(console, settings);
    return 0;
}