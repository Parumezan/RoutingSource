#ifndef MAPS_HPP_
#define MAPS_HPP_

#include "Console.hpp"
#include "Frame.hpp"
#include "Includes.hpp"
#include "Settings.hpp"

namespace RoutingSource
{
    class Maps : public Frame
    {
        private:
            std::shared_ptr<Console> _console;
            std::shared_ptr<Settings> _settings;

        public:
            Maps(std::shared_ptr<Console> console, std::shared_ptr<Settings> settings);
            ~Maps();
            void frameLoop() override;
    };
}

#endif /* !MAPS_HPP_ */