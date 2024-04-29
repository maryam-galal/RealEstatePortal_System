#include <map>
#include <string>
#include <list>
#include "Property.h"
#ifndef USER_H
#define USER_H
class User {
private:
    int id;
    static std::map<int, User> userMap; // Static userMap member

    std::string userName;
    std::string password;
    std::string email;
    std::string phone;
    std::list<Property> properties;

public:
    // Constructors
    User();
    User(const int id, const std::string& userName, const std::string& password, const std::string& email, const std::string& phone); // used to read from the file

    // Function to generate a unique ID
   static int generateUniqueID();

    // Function to check if ID is unique
   static bool isIDUnique(int newID);

    // Getters
    int getId() const;
    std::string getUserName() const;
    std::string getPassword() const;
    std::string getEmail() const;
    std::string getPhone() const;

    // Setters
    void setUserName(const std::string& userName);
    void setPassword(const std::string& password);
    void setEmail(const std::string& email);
    void setPhone(const std::string& phone);

    // Function to add a property to the user's list of properties
    void AddProperty(const Property& property) {
        properties.push_back(property); // Use push_back() to add to the end of the list
    }
};
#endif // USER_H