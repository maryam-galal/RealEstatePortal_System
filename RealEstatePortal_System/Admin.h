#pragma once
#include <string>

using namespace std;

class Admin
{
public:
    // Static constant fields for admin name and password
    static const string ADMIN_NAME;
    static const string ADMIN_PASSWORD;
};

// Initialization of static members outside the class definition
const string Admin::ADMIN_NAME = "admin";
const string Admin::ADMIN_PASSWORD = "Admin123";
