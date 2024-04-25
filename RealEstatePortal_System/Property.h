#pragma once
#include <string>

using namespace std;

class Property
{
public:
    Property(string propertyName, string propertyLocation, float price, float propertySpace, int roomNumbers) //constructor
    {
        this->propertyName = propertyName;
        this->propertyLocation = propertyLocation;
        this->price = price;
        this->propertySpace = propertySpace;
        this->roomNumbers = roomNumbers;
    }

private:
    string propertyName; //String^ represents a managed string in C++/CLI
    string propertyLocation;
    float price;
    float propertySpace;
    int roomNumbers;
};