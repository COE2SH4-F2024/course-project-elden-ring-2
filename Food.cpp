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

// //Generates a new random position on the board, avoiding the player's position.
// void Food::generateFood(objPos blockOff) 
// {
//     int xRange = mainGameMechsRef->getBoardSizeX(); // Get board dimensions
//     int yRange = mainGameMechsRef->getBoardSizeY();

//     int newX, newY;

//     // Generate a valid position
//     do {
//         newX = (rand() % (xRange - 2)) + 1;
//         newY = (rand() % (yRange - 2)) + 1;

//         // Ensure the position is not overlapping the player's position
//     } while (newX == blockOff.pos->x && newY == blockOff.pos->y);

//     // Update food position
//     food.setObjPos(newX, newY, 'X'); // 'X' represents the food symbol
// }

//NEW FOR FEATURE 2
void Food::generateFood(objPosArrayList* playerBody)
{
    int xRange = mainGameMechsRef->getBoardSizeX();
    int yRange = mainGameMechsRef->getBoardSizeY();
    int newX, newY;
    bool positionValid;

    do {
        // Generate random x and y positions
        newX = (rand() % (xRange - 2)) + 1; // Exclude the borders
        newY = (rand() % (yRange - 2)) + 1;

        positionValid = true;

        // Check for overlap with the snake body
        for (int i = 0; i < playerBody->getSize(); i++)
        {
            objPos segment = playerBody->getElement(i); // Get each snake segment
            if (segment.pos->x == newX && segment.pos->y == newY)
            {
                positionValid = false; // Overlapping detected
                break;
            }
        }
    } while (!positionValid); // Repeat until a valid position is found

    // Update the food position
    food.setObjPos(newX, newY, 'X'); // 'X' is the food symbol
}

// Getter for the food position
objPos Food::getFoodPos() const 
{
    return food.getObjPos();
}