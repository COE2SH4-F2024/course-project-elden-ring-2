#include "objPos.h"

objPos::objPos() //Default Constructor.
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

objPos::objPos(int xPos, int yPos, char sym) //Parametrized Constructor.
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule

objPos::~objPos() //Destructor.
{
    delete pos; //Deallocate memory for pos.
    pos = nullptr; //Prevented unwanted access to heap.
}

objPos::objPos(const objPos& other)
{
    pos = new Pos; //Allocate heap memory for variable of type Pos (struct).
    
    //Copy x and y into newly allocated memory from 'other' objpos.
    pos->x = other.pos->x;
    pos->y = other.pos->y;

    //Copy symbol of 'other' objpos.
    symbol = other.symbol;

}

objPos& objPos::operator=(const objPos& other)
{
    //No point in copying if same thing.
    if (this==&other)
        return *this;

    delete pos; //Get rid of existing memory access in heap to prevent memory leak.

    //Allocate new memory in Heap and assign x,y values of 'other' to pos.
    pos = new Pos;
    pos->x = other.pos->x;
    pos->y = other.pos->y;

    //Assign symbol of 'other' to symbol of this objpos.
    symbol = other.symbol;

    return *this; //Get reference to this objpos to allow for situations like a = b = c.
}


void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
