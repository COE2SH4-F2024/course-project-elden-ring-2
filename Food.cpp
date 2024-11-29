#include "Food.h"

#include "objPos.h"
#include "objPosArrayList.h"
#include <cstdlib> 
#include <time.h>


//Constructor
Food::Food(GameMechs* thisGMRef) 
{
    //Initialize food of type objPos to some arbitrary position.
    food = objPos(3, 3, 'X');
    mainGameMechsRef = thisGMRef;
}

Food::~Food()
{
    
}

//Generates a new random position on the board, avoiding the player's position.
void Food::generateFood(objPos blockOff) 
{
    int xRange = mainGameMechsRef->getBoardSizeX(); // Get board dimensions
    int yRange = mainGameMechsRef->getBoardSizeY();

    int newX, newY;

    // Generate a valid position
    do {
        newX = (rand() % (xRange - 2)) + 1;
        newY = (rand() % (yRange - 2)) + 1;

        // Ensure the position is not overlapping the player's position
    } while (newX == blockOff.pos->x && newY == blockOff.pos->y);

    // Update food position
    food.setObjPos(newX, newY, 'X'); // 'X' represents the food symbol
}

// Getter for the food position
objPos Food::getFoodPos() const 
{
    return food.getObjPos();
}