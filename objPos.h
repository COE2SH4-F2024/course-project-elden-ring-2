#ifndef OBJPOS_H
#define OBJPOS_H

// Not really a C++ thing
typedef struct 
{
    int x;
    int y;
} Pos;

class objPos
{
    public:
        Pos* pos;
        char symbol;

        objPos(); //Default Constructor.
        objPos(int xPos, int yPos, char sym); //Constructor with parameters.
        
        // Respect the rule of six / minimum four
        // [TODO] Implement the missing special member functions to meet the minimum four rule

        //Destructor.
        ~objPos();

        //Copy Constructor.
        objPos(const objPos& other);

        //Copy assignement operator.
        objPos& operator=(const objPos& other);
        
        //Setters.
        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);  

        //Getters
        objPos getObjPos() const;
        char getSymbol() const;
        char getSymbolIfPosEqual(const objPos* refPos) const;
        
        bool isPosEqual(const objPos* refPos) const;
};

#endif