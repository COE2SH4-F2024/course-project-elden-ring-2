#include "Food.h"

#include "objPos.h"
#include "objPosArrayList.h"
#include <cstdlib> 
#include <time.h>


//Constructor
Food::Food() 
{
    //Initialize food of type objPos to some arbitrary position.
    food = objPos(3, 3, 'X');
}

//Generates a new random position on the board, avoiding the player's position.
void Food::generateFood(objPos blockOff) 
{
    
}

// Getter for the food position
objPos Food::getFoodPos() const 
{
    return food.getObjPos();
}