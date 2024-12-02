#include "Food.h"

#include "objPos.h"
#include "objPosArrayList.h"
#include <cstdlib> 
#include <time.h>


//Constructor
Food::Food(GameMechs* thisGMRef) 
{
    //Initialize food of type objPos to some arbitrary position.
    foodBucket = new objPosArrayList();
    mainGameMechsRef = thisGMRef;

    //Note: Initialization is unecessary here since the values are overwritten anyways, but we did it just to be safe.
    for (int i = 0; i < 5; i++) //Assuming an initial size of 5
    { 
        //Random X and Y coordinates. 
        int randomX = (rand() % (mainGameMechsRef->getBoardSizeX() - 2)) + 1;
        int randomY = (rand() % (mainGameMechsRef->getBoardSizeY() - 2)) + 1;
        foodBucket->insertTail(objPos(randomX, randomY, 'X'));
    }
}

//Destructor
Food::~Food()
{
    delete[] foodBucket; 
}

//Bonus
void Food::generateFood(objPosArrayList* playerBody)
{
    //Get boardsize from gameMechs class reference.
    int xRange = mainGameMechsRef->getBoardSizeX();
    int yRange = mainGameMechsRef->getBoardSizeY();

    //Clear old foodbucket contents.
    foodBucket->clear();
    
    //Iterate 5 times (assuming 5 items generated at a time).
    for (int i = 0; i < 5; i++) 
    {
        //Create new x,y values for storing position and flag for checking if said position is valid.
        int newX, newY;
        bool positionValid;

        //Iterate until a valid position.
        do 
        {
            //Generate new x,y coordinates for fooditem.
            newX = (rand() % (xRange - 2)) + 1; // Exclude the borders
            newY = (rand() % (yRange - 2)) + 1;

            //Set flag to true.
            positionValid = true;

            //Check for overlap with the player's body
            for (int j = 0; j < playerBody->getSize(); j++) {
                objPos segment = playerBody->getElement(j);
                if (segment.pos->x == newX && segment.pos->y == newY) {
                    positionValid = false;
                    break;
                }
            }

            //Check for overlap with already generated food in the bucket
            for (int k = 0; k < foodBucket->getSize(); k++) {
                objPos foodItem = foodBucket->getElement(k);
                if (foodItem.pos->x == newX && foodItem.pos->y == newY) {
                    positionValid = false;
                    break;
                }
            }
        } while (!positionValid);

        //Assign symbols: 'X' (default), 'Y' (special), or 'Z' (very special)
        char symbol;
        
        //First symbol in food bucket will be Z
        if (i == 0)         
            symbol = 'Z';

        //Second will be Y
        else if (i == 1)  
            symbol = 'Y';
        
        //The remaining three will be X
        else                 
            symbol = 'X';
    

        //Insert the new random food item into foodBucket.
        objPos newFood(newX, newY, symbol);
        foodBucket->insertHead(newFood);
    }
}

//Returns a reference to the foodBucket list.
objPosArrayList* Food::getFoodPos() const 
{
    return foodBucket;
}
