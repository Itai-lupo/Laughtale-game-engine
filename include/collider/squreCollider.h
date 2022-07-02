#pragma once
#include "component.h"
#include "core.h"
#include "gameobject.h"
#include <vector>

namespace LTE
{
    class squreCollider: public component
    {
        private:
            std::vector<squreCollider *> InCollisionWith = std::vector<squreCollider *>(0);
            int a = 5;
        public:
            squreCollider();
            ~squreCollider();

            virtual void init(std::shared_ptr< LTE::gameObject>) override;
            virtual void end() override;
            transform *getBonds() const;

            bool operator == (squreCollider& s);

    };
}  