#include "baseActor.hpp"


namespace game 
{

    BaseActor::BaseActor(){}

    BaseActor::~BaseActor(){}


    void BaseActor::update()
    {
        //return true;
    }


    void BaseActor::draw()
    {
        DrawText("Base Actor",0,0,40,RED);
    }

    Rectangle BaseActor::getBoundingBox()
    {
        return Rectangle(position.x, position.y);
    }


     

}


