#include "objPosArrayList.h"
#include <iostream>

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;

    // Explicitly initialize all elements
    for (int i = 0; i < arrayCapacity; ++i)
        aList[i] = objPos(); // Default constructor of objPos
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize >= ARRAY_MAX_CAP)
        throw std::overflow_error("ArrayList is full");

    //Shifting everything to the right.
    for(int i = listSize; i > 0; i--)
    {
        aList[i] = aList[i - 1];
    }

    //Set the first element to thisPos
    aList[0] = thisPos;
    
    //Increase list size.
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize >= ARRAY_MAX_CAP)
        throw std::overflow_error("ArrayList is full");


    aList[listSize++] = thisPos; //Add new element to tail of list and then, increment listsize.
}

void objPosArrayList::removeHead()
{
    if (listSize == 0)
        throw std::underflow_error("ArrayList is empty");

    //Overwrite head with next element and keep going until all elements shift left once.
    for(int i = 0; i < listSize - 1; i++)
        aList[i] = aList[i + 1];
    
    //Decrement listSize by 1.
    listSize--;

}

void objPosArrayList::removeTail()
{
    if (listSize == 0)
        throw std::underflow_error("Array is empty");

    //Decrement listSize by 1. Last element is ignored.
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    if (listSize == 0)
        throw std::underflow_error("Array is empty");
    
    //Return First element/Head.
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    if (listSize == 0)
        throw std::underflow_error("Array is empty");
    
    //Return Last element/Tail.
    return aList[listSize-1];
}

objPos objPosArrayList::getElement(int index) const
{
    if (index < 0 || index >= ARRAY_MAX_CAP)
        throw std::out_of_range("Index out of bounds");

    // Return element after accounting for illegal values.
    return aList[index];
}

//essentially clears the list.
void objPosArrayList::clear()
{
    for (int i = 0; i < listSize; ++i) 
    {
        aList[i] = objPos();//Reinitialize each element with the default constructor
    }

    listSize = 0; 
}


//Used to expand array size if max capacity is reached.
void objPosArrayList::expandArray()
{
    //Set unitsize to 200 and add it to original max capacity.
    int unitsize = arrayCapacity;
    arrayCapacity += unitsize;

    //Create a new list of double the size of the original.
    objPos* temp = new objPos[arrayCapacity];

    //Perform deep copy of important elements (Listsize)
    for (int i=0; i<listSize; i++)
        temp[i] = aList[i];

    //Delete old list.
    delete[] aList;

    //Assign pointer of new list (temp) to old.
    aList = temp;
}

int objPosArrayList::getcap()
{
    return arrayCapacity;
}