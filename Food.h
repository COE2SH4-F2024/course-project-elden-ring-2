#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "GameMechs.h" // Required to access board dimensions   

class Food
{
    private:
        objPos food;

    public:
        Food();
        ~Food();
        void generateFood(objPos blockOff);
        objPos getFoodPos() const;


};

#endif