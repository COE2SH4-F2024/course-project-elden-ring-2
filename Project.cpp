#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *gamemechs; //ptr to gamemechs.
Player *player; //ptr to player object in global scope.
Food* food; //ptr to food.


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    

    while(!gamemechs->getExitFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();       
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    gamemechs = new GameMechs(10, 20); // Initialize game mechanics
    player = new Player(gamemechs);       // Initialize player

    gamemechs->setInput(0);
    srand(time(NULL)); //Seed random generator to further randomize rand().

    food = new Food(gamemechs);

    food->generateFood(player->getPlayerPos()->getHeadElement()); //Random food position

    
}

void GetInput(void)
{
   if (MacUILib_hasChar())
        gamemechs->setInput(MacUILib_getChar());

    printf("%c", gamemechs->getInput());
}

void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();

    if(gamemechs->getInput() == ' ')
    {
        gamemechs->setExitTrue();
        gamemechs->setLoseFlag();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    // Iterate through each row
    for (int x = 0; x < gamemechs->getBoardSizeX(); x++) {
        for (int y = 0; y < gamemechs->getBoardSizeY(); y++) {
            bool printed = false;

            // Draw border
            if (x == 0 || y == 0 || x == gamemechs->getBoardSizeX() - 1 || y == gamemechs->getBoardSizeY() - 1) {
                MacUILib_printf("%c", '#');
                printed = true;
            }

            //If x and y coordinates are player coordinates, print player symbol.
            // Draw snake body
            objPosArrayList* body = player->getPlayerPos();
            for (int i = 0; i < body->getSize(); i++) {
                if (x == body->getElement(i).pos->x && y == body->getElement(i).pos->y) {
                    MacUILib_printf("*");
                    printed = true;
                    break;
                }
            }

            //If x and y coordinates are food coordinates, print food symbol.
            if (x == food->getFoodPos().pos->x && y == food->getFoodPos().pos->y) 
            {
                MacUILib_printf("%c", food->getFoodPos().getSymbol());
                printed = true;
            }

            // //Draw random ASCII object (for example purposes)
            // else if (x == 6 && y == 8) { // Arbitrary position
            //     objPos randomObj(6, 8, 'X'); // Example objPos usage
            //     MacUILib_printf("%c", randomObj.getSymbol());
            //     printed = true;
            // }

            if (!printed) {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    // MacUILib_clearScreen();    

    MacUILib_uninit();

    //Delete heap memory
    delete player;
    delete gamemechs;
    delete food;
}
