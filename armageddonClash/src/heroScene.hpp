#pragma once

#include "gameScene.hpp"
#include "hero.hpp"
#include <iostream>





namespace game 
{
    class HeroScene : public GameScene {
        public :
            HeroScene();

            virtual ~HeroScene();

            virtual void loadGameResources() ;
    };
}
