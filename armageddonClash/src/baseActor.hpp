#pragma once

#include "raylib.hpp"
#include "rectangle.hpp"


namespace game {
    class BaseActor 
    {
        public:
            BaseActor();
            virtual ~BaseActor();

            virtual bool update(bool onGround);

            virtual void draw();

            virtual Rectangle getBoundingBox();

            Vector2 position{};

            Vector2 velocity{};

    };

}
