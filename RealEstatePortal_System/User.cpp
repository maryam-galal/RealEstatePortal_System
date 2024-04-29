#include "User.h"
#include <random>

std::map<int, User> User::userMap;

User::User() :
    id(generateUniqueID()), userName(""), password(""), email(""), phone("") {}

User::User(const int id, const std::string& userName, const std::string& password, const std::string& email, const std::string& phone) :
    id(id), userName(userName), password(password), email(email), phone(phone) {}
bool User::isIDUnique(int newID) {
    // Logic to check if newID is unique compared to existing IDs
    return userMap.find(newID) == userMap.end();
}
int User::generateUniqueID() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> distribution(1000, 9999);
    int newID;
    do {
        newID = distribution(gen);
    } while (!isIDUnique(newID));
    return newID;
}



int User::getId() const { return id; }

std::string User::getUserName() const { return userName; }

std::string User::getPassword() const { return password; }

std::string User::getEmail() const { return email; }

std::string User::getPhone() const { return phone; }

void User::setUserName(const std::string& userName) { this->userName = userName; }

void User::setPassword(const std::string& password) { this->password = password; }

void User::setEmail(const std::string& email) { this->email = email; }

void User::setPhone(const std::string& phone) { this->phone = phone; }
