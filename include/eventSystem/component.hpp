#pragma once
#include <functional>
#include <vector>
#include "core.hpp"
#include <string>

namespace LTE
{
    class gameObject;
    class component
    {
        public:
            component(){}
            virtual ~component() = default;

            virtual std::string getName() = 0;
            virtual void displayComponentProprties() = 0;
    };

}