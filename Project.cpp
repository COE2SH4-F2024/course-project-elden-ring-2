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

char start = 'x';
int screen = 1;
char creators[] = "BY: Jyotiraditya Pendyala and Andrew Chai";
char press[] = "Press \'x\' to play";

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);
void Screen(int);


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
    
    while(screen == 1)
    {
        DrawScreen();
        LoopDelay();
    }

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

    if (screen == 1)
    {
        Screen(screen);

        if (start == MacUILib_getChar())
            screen++;
    }
    else
    { 
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
                        MacUILib_printf("🟣");
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
        MacUILib_printf("🌟: Very special food (Score +30, Length +3)\n");
        MacUILib_printf("\nUse AWSD keys to move the snake around!\n\n");
        MacUILib_printf("Score: %d\n", player->getScore());
        MacUILib_printf("Length: %d\n", player->getPlayerPos()->getSize());
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();
    if (gamemechs->getLoseFlagStatus())
    {
        Screen(screen);
    }
    else
    {
        Screen(++screen);
    }   

    MacUILib_uninit();

    //Delete heap memory
    player->~Player();
    delete gamemechs;
    food->~Food();
}

void Screen(int condition)
{
    if (condition == 1)
    {
        MacUILib_printf("TTTTT H   H EEEEE     SSSS N   N  AAA  K  K EEEEE    GGGGG   AAA  M     M EEEEE\n");
        MacUILib_printf("  T   H   H E        S     NN  N A   A K K  E        G      A   A M     M E    \n");
        MacUILib_printf("  T   HHHHH EEEE      SSS  N N N AAAAA KK   EEEE     G  GGG AAAAA MM   MM EEEE \n");
        MacUILib_printf("  T   H   H E            S N  NN A   A K K  E        G   G  A   A M M M M E    \n");
        MacUILib_printf("  T   H   H EEEEE    SSSS  N   N A   A K  K EEEEE    GGGGG  A   A M  M  M EEEEE\n");
        MacUILib_printf("\n");
        MacUILib_printf("\t%s\t%s", creators, press);
    }
    else if (condition == 2)
    {
        MacUILib_printf("                            Y     Y  OOO  U   U     L      OOO   SSSS EEEEE                         \n");
        MacUILib_printf("                             Y   Y  O   O U   U     L     O   O S     E                             \n");
        MacUILib_printf("                              YYY   O   O U   U     L     O   O  SSS  EEEE                          \n");
        MacUILib_printf("                               Y    O   O U   U     L     O   O     S E                             \n");
        MacUILib_printf("                              Y      OOO   UUU      LLLLL  OOO  SSSS  EEEEE                         \n");
        MacUILib_printf("\n\n");
        MacUILib_printf("YOUR SCORE: %d", player->getScore());
        MacUILib_printf("\n\n");
        MacUILib_printf("  ..                                                                                     --:-=..    \n");
        MacUILib_printf(":-..:=.                                                                                .=-:::.:-.   \n");
        MacUILib_printf("=.:::-=--..                                                                            .:=-:-===-   \n");
        MacUILib_printf("=:::=:..:-:       ..:--:.                                                                .==:::.:-..\n");
        MacUILib_printf(":-:=:.:::::      .=:..::=.                         ...        NOOOO...                    -=-:::::=.\n");
        MacUILib_printf(".:==::::-==-==:..-:::::-=.                  ..=:.  .+=.                       ...::..     :-=--:::-.\n");
        MacUILib_printf("  .=::-=::.....=--:::--=.                   .*=......+%-...                   :=::..=..   =:-----:-.\n");
        MacUILib_printf("  .=-:=:::::::::-::---:.                  .-#*=-::...:=*##+==:.               :-::::.-.  .--:...:=-.\n");
        MacUILib_printf("  .--=----::-==-::::-:.               ..=##*-:..::::::::::::::-==..           .:-::::-...-:-::::..-:\n");
        MacUILib_printf("    =+----=-:::::::--               .-=-:::::::::::::-++=-::::::--=-           ..=:::-..-::--::::::-\n");
        MacUILib_printf("    :+---:-::::::::-:             .-=--:=+=:-=---------=-:-++-------=:.          :-::-=-:::::==::::=\n");
        MacUILib_printf("     :=----::::::::-:           .:=---*=::--=-----------==--::*=------=.         ---::::::::=-------\n");
        MacUILib_printf("     .-----:::=::::--         ..=---*-::--=--------==------------------=:.     ..=---=-:::--------=.\n");
        MacUILib_printf("      :=---:::.:=----         .=------------=*%%%%%%%%%%%*--------------=-.      =--=.::::-------=  \n");
        MacUILib_printf("      .:=---:::..=-=.       ..=-----------+%%%%%%%%%%%%%%%%#=--------------.     :==-:::::-----=:.  \n");
        MacUILib_printf("        :=---:::.-:.        .-:---------=#%%%%%%%%%%%%%%%%%%%#=------------.     ..-=::::----=:..   \n");
        MacUILib_printf("         .:=----=-.        .:-:--------+%%%%%%%%%%%%%%%%%%%%%%%=----------:+.      ..=----=-.       \n");
        MacUILib_printf("           ......          .+:--------+%%%%%@@@@%%%%%%@@@%%%%%%%+---------::-        ......         \n");
        MacUILib_printf("                           :-:-------+%%%%%@@@@@@%%%%@@@@%%%%%%%%=--------:.-                       \n");
        MacUILib_printf("                          .-::------=%%%%%%@@@@@@@@@@@@@@@%%%%%%%#=-------::-                       \n");
        MacUILib_printf("                          .-.:------#%%%%%%@@@@@@@@@@@@@@@@%%%%%%%#-------::-                       \n");
        MacUILib_printf("                          .-::-----+%%%%%%%@@@@@@@@@@@@@@@@%%%%%%%%+------::-                       \n");
        MacUILib_printf("                          .-::----=%%%%%%%%@@@@@#*++*#%@@@@%%%%%%%%#=-----::-                       \n");
        MacUILib_printf("                           :-:----+%%%%%%%%@%*-::::::::-+%@%%%%%%%%%*------:-                       \n");
        MacUILib_printf("                           .+----=#%%%%%%%%*-:::::::::::::=#%%%%%%%%%=------:                       \n");
        MacUILib_printf("                           .:----+%%%%%%%#=::::::::::::::::-*%%%%%%%%+-----+.                       \n");
        MacUILib_printf("                            .-=--*%%%%%%*--:::::::::::::::::-=%%%%%%%#----=.                        \n");
        MacUILib_printf("                            ..+--#%%%%%+-------::::::::::::----#%%%%%#=-=--                         \n");
        MacUILib_printf("                              =--*%%%*--------------------------+%%%%*--=-.                         \n");
        MacUILib_printf("                              ------------------------------------=++----:.                         \n");
        MacUILib_printf("                              .-::::==---------------------------------:-..                         \n");
        MacUILib_printf("                              ..-==-=-----------------------------==-:::-.                          \n");
        MacUILib_printf("                                    .-=--------------------------=-..:-:                            \n");
        MacUILib_printf("                                      ..-==-------------------=-..                                  \n");
        MacUILib_printf("                                           .:====------====:                                        \n");
    }
    else if (condition == 3)
    {
        MacUILib_printf("Y     Y  OOO  U   U     QQQ   U   U IIIII TTTTT\n");
        MacUILib_printf(" Y   Y  O   O U   U    Q   Q  U   U   I     T  \n");
        MacUILib_printf("  YYY   O   O U   U    Q Q Q  U   U   I     T  \n");
        MacUILib_printf("   Y    O   O U   U    Q  QQ  U   U   I     T  \n");
        MacUILib_printf("  Y      OOO   UUU      QQQ Q  UUU  IIIII   T  \n");
        MacUILib_printf("\n\n");
        MacUILib_printf("YOUR SCORE: %d", player->getScore());
        MacUILib_printf("\n\n");
        MacUILib_printf("     __//\n");
        MacUILib_printf("    /.__.\\\n");
        MacUILib_printf("    \\ \\/ /   - chicken *Bak* *Bak*\n");
        MacUILib_printf(" '__/    \\\n");
        MacUILib_printf("  \\-      )\n");
        MacUILib_printf("   \\_____/\n");
        MacUILib_printf("_____|_|____\n");
        MacUILib_printf("     \" \"\n");
    }
}