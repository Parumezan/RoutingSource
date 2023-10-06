#ifndef FRAME_HPP_
#define FRAME_HPP_

#include "Includes.hpp"

namespace RoutingSource
{
    class Frame
    {
        public:
            Frame();
            ~Frame();
            bool state = false;
            virtual void frameLoop();
            virtual void initFrame();
            virtual void saveSettings();
    };
} // namespace RoutingSource

#endif /* !FRAME_HPP_ */