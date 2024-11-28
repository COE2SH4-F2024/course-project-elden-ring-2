#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    
    //Init player in centre of the board as an '*'.
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2,'*');
}


Player::~Player()
{
    // delete any heap members here
    
    //For now, nothing, since playerPos is being declared in stack.
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos array list
    return playerPos;
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
    switch(myDir)
    {
        case UP:
            playerPos.pos->x--;
            if (playerPos.pos->x<1)
                playerPos.pos->x = mainGameMechsRef->getBoardSizeX()-2;
            break;
        
        case DOWN:
            playerPos.pos->x++;
            if (playerPos.pos->x>mainGameMechsRef->getBoardSizeX()-2)
                playerPos.pos->x = 1;
            break;
        
        case LEFT:
            playerPos.pos->y--;
            if (playerPos.pos->y<1)
                playerPos.pos->y = mainGameMechsRef->getBoardSizeY()-2;
            break;

        case RIGHT:
            playerPos.pos->y++;
            if (playerPos.pos->y>mainGameMechsRef->getBoardSizeY()-2)
                playerPos.pos->y = 1;
            break;

        case STOP:
            //do nothing
            break;
        
        default:
            break;
    }
}

// More methods to be added