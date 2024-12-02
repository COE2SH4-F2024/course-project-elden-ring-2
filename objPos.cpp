#include "objPos.h"

//Default constructor.
objPos::objPos() 
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

//Parametrized constructor.
objPos::objPos(int xPos, int yPos, char sym) 
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule

//Destructor.
objPos::~objPos() 
{
    delete pos; //Deallocate memory for pos.
    pos = nullptr; //Prevented unwanted access to heap.
}

//Copy constructor.
objPos::objPos(const objPos& other)
{
    pos = new Pos; //Allocate heap memory for variable of type Pos (struct).
    
    //Copy x and y into newly allocated memory from 'other' objpos.
    pos->x = other.pos->x;
    pos->y = other.pos->y;

    //Copy symbol of 'other' objpos.
    symbol = other.symbol;

}

//Copy assignement operator.
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


//Setter for objPos. Similar to copy constructor.
void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

//Setter for objPos. Takes x, y, and symbol parameters seperately.
void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

//Returns objPos.
objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

//Returns symbol
char objPos::getSymbol() const
{
    return symbol;
}

//Checks if two objPos are equal (takes reference to objPos as parameter)
bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

//Returns symbol if objPos = parameter objPos reference.
char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
