#pragma once
#include "core.hpp"
#include "linuxSoundDevice.hpp"

namespace LTE
{
    class linuxInputSoundDevice: public linuxSoundDevice
    {
        private:
            
        public:
            linuxInputSoundDevice();
            virtual long capture_into_buffer(char* buffer, uint64_t frames_to_capture) override;
    };       
}