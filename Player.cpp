#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

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

    objPos newhead(head);

    playerPosList->insertHead(newhead);
    playerPosList->removeTail();
}

// More methods to be added