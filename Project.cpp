#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *gamemechs; //ptr to gamemechs.
Player *player; //ptr to player object in global scope.


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

            else if (x == player->getPlayerPos().pos->x && y==player->getPlayerPos().pos->y)
            {
                MacUILib_printf("%c", player->getPlayerPos().getSymbol());
                printed = 1;
            }

            // Draw random ASCII object (for example purposes)
            else if (x == 6 && y == 8) { // Arbitrary position
                objPos randomObj(6, 8, 'X'); // Example objPos usage
                MacUILib_printf("%c", randomObj.getSymbol());
                printed = true;
            }

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
}
