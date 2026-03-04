#pragma once

#include "gameScene.hpp"
#include "hero.hpp"
#include <memory>




namespace game 
{
    class HeroScene : public GameScene {
        public :
            HeroScene();

            virtual ~HeroScene();

            virtual void loadGameResources();
    };
}
