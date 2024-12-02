#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "GameMechs.h" // Required to access board dimensions
#include "objPosArrayList.h"   

class Food
{
    private:
        objPosArrayList* foodBucket; //List of food items
        
        //Reference to gamemechs to get board size.
        GameMechs* mainGameMechsRef;

    public:
        Food(GameMechs* thisGMRef); //Constructor
        ~Food(); //Destructor
        void generateFood(objPosArrayList* playerBody); //Food generation
        objPosArrayList* getFoodPos() const; //Getter for list reference


};

#endif