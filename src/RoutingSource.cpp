#include "Console.hpp"
#include "Includes.hpp"
#include "Maps.hpp"
#include "Screen.hpp"
#include "Settings.hpp"

using namespace RoutingSource;

int main(void)
{
    std::shared_ptr<Console> console = std::make_shared<Console>();
    std::shared_ptr<Settings> settings = std::make_shared<Settings>(console);
    std::shared_ptr<Maps> maps = std::make_shared<Maps>(console, settings);
    Screen screen(console, settings, maps);
    return 0;
}