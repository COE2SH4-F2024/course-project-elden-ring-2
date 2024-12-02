#include "GameMechs.h"

//Default Constructor
GameMechs::GameMechs()
{
    input = 0;          // Initialize input to null
    score = 0;          // Initialize score to zero.
    exitFlag = false;   // Initialize exit flag
    loseFlag = false;   // Initialize lose flag
    boardSizeX = 15;
    boardSizeY = 30;
}

//Parameterized Constructor
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;          // Initialize input to null
    score = 0;          // Initialize score to zero.
    exitFlag = false;   // Initialize exit flag
    loseFlag = false;   // Initialize lost falg
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// Not needed for now.
GameMechs::~GameMechs()
{
    
}

//Returns exit flag.
bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

//Returns lose flag.
bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    
//Returns input.
char GameMechs::getInput() const
{
    return input;
}

//Returns user score.
int GameMechs::getScore() const
{
    return score;
}

//Increments score.
void GameMechs::incrementScore()
{
    score++;
}

//Returns horizontal size of board.
int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

//Returns vertical size of board.
int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

//Sets exitflag to true.
void GameMechs::setExitTrue()
{
    exitFlag = true;
}

//Sets lose flag to true.
void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

//Sets user input to given parameter.
void GameMechs::setInput(char this_input)
{
    input = this_input;
}

//Clears user input.
void GameMechs::clearInput()
{
    input = '\0';
}

// More methods should be added here