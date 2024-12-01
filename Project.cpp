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

    gamemechs = new GameMechs(); // Initialize game mechanics
    food = new Food(gamemechs);

    player = new Player(gamemechs, food);       // Initialize player

    gamemechs->setInput(0);
    srand(time(NULL)); //Seed random generator to further randomize rand().

    
    food->generateFood(player->getPlayerPos()); //Random food position

    
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
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    MacUILib_printf("Snake Game\n");
    MacUILib_printf("----------\n----------\n\n");
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
            if (x == food->getFoodPos().pos->x && y == food->getFoodPos().pos->y && !player->checkFoodConsumption()) 
            {
                MacUILib_printf("%c", food->getFoodPos().getSymbol());
                printed = true;
            }

            if (!printed) {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", player->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{

    if (gamemechs->getLoseFlagStatus())
    {
        MacUILib_printf("You lose! Better luck next time!\n");
    }
    else
    {
        MacUILib_printf("Game Over! Exiting...\n");
    }   

    MacUILib_uninit();

    //Delete heap memory
    delete player;
    delete gamemechs;
    delete food;
}
