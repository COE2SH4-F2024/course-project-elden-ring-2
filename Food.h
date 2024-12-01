#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "GameMechs.h" // Required to access board dimensions
#include "objPosArrayList.h"   

class Food
{
    private:
        objPos food;
        
        //Reference to gamemechs to get board size.
        GameMechs* mainGameMechsRef;

    public:
        Food(GameMechs* thisGMRef);
        ~Food();
        void generateFood(objPosArrayList* blockOff);
        objPos getFoodPos() const;


};

#endif