#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "Food.h"
#include "windows.h"

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


//Professor Chen Mentioned that its fine if I borrowed this logic from Youssef. 
//It hides the cursor to prevent too much flashing during refresh. (Does not impact the game).
void HideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    CONSOLE_CURSOR_INFO cursorInfo;

    // Get the current cursor info
    if (GetConsoleCursorInfo(hConsole, &cursorInfo)) {
        cursorInfo.bVisible = FALSE; 
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    } else {
        printf("Failed to get console cursor info.\n");
    }
}

int main(void)
{

    SetConsoleOutputCP(CP_UTF8);
    HideCursor();
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
    MacUILib_printf("----------\n----------\n");
    // Iterate through each row
    for (int x = 0; x < gamemechs->getBoardSizeX(); x++) {
        for (int y = 0; y < gamemechs->getBoardSizeY(); y++) {
            bool printed = false;

            //Draw border.
            if (x == 0 || y == 0 || x == gamemechs->getBoardSizeX() - 1 || y == gamemechs->getBoardSizeY() - 1) {
                MacUILib_printf("🟫");
                printed = true;
            }

            //Draw snake body.
            objPosArrayList* body = player->getPlayerPos();
            for (int i = 0; i < body->getSize(); i++) 
            {
                if (x == body->getElement(i).pos->x && y == body->getElement(i).pos->y) 
                {
                    MacUILib_printf("🥹");
                    printed = true;
                    break;
                }
            }

            
            char temp;
            //Print foods.
            objPosArrayList* foodList = food->getFoodPos();
            for (int i = 0; i < foodList->getSize(); i++) 
            {
                objPos foodItem = foodList->getElement(i);
                if (x == foodItem.pos->x && y == foodItem.pos->y && !player->checkFoodConsumption(temp))
                {
                    if(foodItem.getSymbol() == 'X')
                    {
                        MacUILib_printf("🍎");
                    }

                    else if (foodItem.getSymbol() == 'Y')
                    {
                        MacUILib_printf("⭐");
                    }

                    else if (foodItem.getSymbol() == 'Z')
                    {
                        MacUILib_printf("🌟");
                    }
                
                    printed = true;
                    break;
                }
            }

            if (!printed) {
                MacUILib_printf("%2c", ' ');
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Food Guide:\n----------\n");
    MacUILib_printf("🍎: Regular Food (Score +1, Length +1)\n");
    MacUILib_printf("⭐: Special Food (Score +10, Length +1)\n");
    MacUILib_printf("🌟: Very special food (Score +50, Length +10)\n");
    MacUILib_printf("\nUse AWSD keys to move the snake around!\n\n");
    MacUILib_printf("Score: %d\n", player->getScore());
    MacUILib_printf("Length: %d\n", player->getPlayerPos()->getSize());

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
    player->~Player();
    delete gamemechs;
    food->~Food();
}
