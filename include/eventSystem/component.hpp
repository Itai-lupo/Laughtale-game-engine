#pragma once
#include <functional>
#include <vector>
#include <string>
#include <memory.h>

#include "core.hpp"

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

    class componentAbstractFactory
    {
        public:
            virtual ~componentAbstractFactory() = default;

            virtual std::shared_ptr<component> createComponent() = 0;
    };
}