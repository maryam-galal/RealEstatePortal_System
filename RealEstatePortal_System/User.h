#pragma once
#include <list>
#include "Property.h"

class User
{
public:
    User(const std::string& username, const std::string& password)
        : username(username), password(password), properties(new std::list<Property>())
    {
    }

    // Add a property to the user's list of properties
    void AddProperty(const Property& property)
    {
        properties->push_back(property); // Use push_back() to add to the end of the list
    }

private:
    std::string username;
    std::string password;
    std::list<Property>* properties; // List of properties owned by the user
};
