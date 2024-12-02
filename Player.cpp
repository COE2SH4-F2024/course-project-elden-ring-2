#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* food)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    this->food = food;

    // Create list to record snake body in heap.
    playerPosList = new objPosArrayList();

    //Initialize a new objPos with X,Y in the centre of the board. 
    objPos head(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2,'*');
    
    //Insert head to the snake body. 
    playerPosList->insertHead(head);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos array list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic

    char input = mainGameMechsRef->getInput();

    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            case ' ': // exit
                mainGameMechsRef->setExitTrue();
                break;
            

            // Add more key processing here
            case 'w':
            case 'W':
                if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
                {
                    myDir = UP;
                }
                break;

            // Add more key processing here
            case 'a':
            case 'A':
                if (myDir == UP || myDir == DOWN || myDir == STOP)
                {
                    myDir = LEFT;
                }
                break;

            // Add more key processing here    
            case 's':
            case 'S':
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
                {
                    myDir = DOWN;
                }
                break;

            case 'd':
            case 'D':
            if (myDir == UP || myDir == DOWN || myDir == STOP)
                {
                    myDir = RIGHT;
                }                
                break;

            default:
                break;
        }
       
        mainGameMechsRef->clearInput();
    }          
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    //Head position
    objPos head = playerPosList->getHeadElement(); 

    int x = head.pos->x, y = head.pos->y;

    switch(myDir)
    {
        case UP:
            x--;
            if (x<1)
                x = mainGameMechsRef->getBoardSizeX()-2;
            break;
        
        case DOWN:
            x++;
            if (x>mainGameMechsRef->getBoardSizeX()-2)
                x = 1;
            break;
        
        case LEFT:
            y--;
            if (y<1)
                y = mainGameMechsRef->getBoardSizeY()-2;
            break;

        case RIGHT:
            y++;
            if (y>mainGameMechsRef->getBoardSizeY()-2)
                y = 1;
            break;

        case STOP:
            //do nothing
            break;
        
        default:
            break;
    }

    objPos newhead(x,y,'*');

    if(checkSelfCollision(newhead))
    {
        mainGameMechsRef->setExitTrue();
        mainGameMechsRef->setLoseFlag();
        return;
    }

    char foodType;
    if (checkFoodConsumption(foodType))
    {
        handleFoodConsumption(foodType);
        return;
    }

    playerPosList->insertHead(newhead);
    playerPosList->removeTail();

    
}


// More methods to be added
bool Player::checkFoodConsumption(char& foodType)
{
    objPos head = playerPosList->getHeadElement();

    for (int i=0; i<food->getFoodPos()->getSize();i++)
    {
        objPos foodItem = food->getFoodPos()->getElement(i);
        int foodX = foodItem.pos->x, foodY = foodItem.pos->y;

        if (head.pos->x == foodX && head.pos->y == foodY)
        {
            foodType = foodItem.getSymbol();
            return true;
        }
   
    }  

    return false;
}

void Player::increasePlayerLength()
{
    // Get the current tail segment
    objPos tail = playerPosList->getTailElement();
    int tailX = tail.pos->x;
    int tailY = tail.pos->y;

    // Handle case where the snake has only one segment
    if (playerPosList->getSize() == 1) 
    {
        // Add a duplicate of the only segment (head)
        playerPosList->insertTail(objPos(tailX, tailY, '*'));
        return;
    }

    // Determine the direction of the segment before the tail
    objPos secondLastSegment = playerPosList->getElement(playerPosList->getSize() - 2);

    // Calculate new tail position based on the direction
    if (secondLastSegment.pos->x < tailX)
        tailX++; // The previous segment is above, grow down

    else if (secondLastSegment.pos->x > tailX)
        tailX--; // The previous segment is below, grow up

    else if (secondLastSegment.pos->y < tailY)
        tailY++; // The previous segment is left, grow right

    else if (secondLastSegment.pos->y > tailY)
        tailY--; // The previous segment is right, grow left
    

    // Apply wrap-around logic if the new tail position goes out of bounds
    if (tailX > mainGameMechsRef->getBoardSizeX()-2)
        tailX = 1;  

    else if (tailX < 1)
        tailX = mainGameMechsRef->getBoardSizeX() - 2;  
    

    if (tailY > mainGameMechsRef->getBoardSizeY()-2) 
        tailY = 1;  

    else if (tailY < 1)
        tailY = mainGameMechsRef->getBoardSizeY() - 2;  
    

    //In case we reach max array size, expand array.
    if(playerPosList->getSize()==playerPosList->getcap())
        playerPosList->expandArray();
    
    // Add the new segment at the calculated position    
    playerPosList->insertTail(objPos(tailX, tailY, '*'));
}

int Player::getScore()
{
    // Score is snake length minus 1 (head does not count towards score)
    return mainGameMechsRef->getScore();
}

bool Player::checkSelfCollision(objPos& newhead)
{
    /// Check the new head position against the body
    for (int i = 1; i < playerPosList->getSize(); i++) { // Start from 1 to exclude head
        objPos segment = playerPosList->getElement(i);
        if (segment.isPosEqual(&newhead)) {
            return true; // Collision detected
        }
    }
    return false;
}

void Player::handleFoodConsumption(char foodType)
{
    int growth = 0, scoreIncrement = 0;

    // Determine growth and score based on food type
    switch (foodType) {
        case 'X': growth = 1; scoreIncrement = 1; break;
        case 'Y': growth = 1; scoreIncrement = 10; break;
        case 'Z': growth = 10; scoreIncrement = 50; break;
    }

    // Grow snake from the tail
    for (int i = 0; i < growth; i++) {
        increasePlayerLength();
    }

    // Update score
    for (int i = 0; i < scoreIncrement; i++) {
        mainGameMechsRef->incrementScore();
    }

    // Generate new food
    food->generateFood(playerPosList);
}