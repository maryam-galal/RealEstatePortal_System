#include "Register.h"
#include "RealEstatePortal_System.h"
#include "LogIn.h"
#include <QString>
#include <QLabel>
#include "User.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <warning.h>
#include <QMessageBox>
#include<QRegularExpression>

Register::Register(std::map<int, User>& userMap, QWidget *parent)
	: QMainWindow(parent), userMap(userMap)
{
	ui.setupUi(this);
	connect(ui.HomeButton, SIGNAL(clicked()), this, SLOT(on_Homebutton_clicked())); // Connect button click to slot
    connect(ui.RegisterButton, SIGNAL(clicked()), this, SLOT(on_Regbutton_clicked())); // Connect button click to slot
}

Register::~Register()
{}

bool Register::isUsernameExists(const QString& username) const
{
    for (const auto& pair : userMap) {
        if (QString::fromStdString(pair.second.getUserName()) == username) {
            return true; // Username exists
        }
    }
    return false; // Username does not exist
}
// Function to validate password
bool Register::isPasswordValid(const QString& password) const
{
    // Password must be at least 8 characters, contain at least one digit and one letter
    return password.length() >= 8 && password.contains(QRegularExpression("[0-9]")) && password.contains(QRegularExpression("[a-zA-Z]") );
}
// Function to validate email format
bool Register::isEmailValid(const QString& email) const
{
    // Use regular expression to check email format
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return regex.match(email).hasMatch();
}
// Function to validate phone number format
bool Register::isPhoneNumberValid(const QString& phone) const
{ // Phone number must be numeric and exactly 11 digits long
    return phone.length() == 11;  
}

void Register::on_Homebutton_clicked()
{
    // Create an instance of the Second window
    RealEstatePortal_System* homeWindow = new RealEstatePortal_System(userMap);
    homeWindow->show(); // Show the Second window
    this->hide();
}
void Register::on_Regbutton_clicked()
{
    
    QString userName = ui.Name->toPlainText();
    QString password = ui.pass->toPlainText();
    QString confpassword = ui.confirmpass->toPlainText();
    QString email = ui.email->toPlainText();
    QString phone = ui.phone->toPlainText();
    bool usernameExists = false;
    for (const auto& pair : userMap) {
        if (QString::fromStdString(pair.second.getUserName()) == userName) {
            usernameExists = true;
            break;
        }
    }

    if (isUsernameExists(userName)) {
        QMessageBox::warning(this, "Invalid Input", "The username is already in use. Please choose a different username.", QMessageBox::Ok);
    }
    else if (!isPasswordValid(password)) {
        QMessageBox::warning(this, "Invalid Input", "Password must be at least 8 characters long and contain at least one digit and one letter.", QMessageBox::Ok);
    }
    else if (password != confpassword) {
        QMessageBox::warning(this, "Invalid Input", "Passwords do not match. Please enter matching passwords.", QMessageBox::Ok);
    }
    else if (!isEmailValid(email)) {
        QMessageBox::warning(this, "Invalid Input", "Invalid email format. Please enter a valid email address.", QMessageBox::Ok);
    }
    else if (!isPhoneNumberValid(phone)) {
        QMessageBox::warning(this, "Invalid Input", "Phone number must be numeric and exactly 11 digits long.", QMessageBox::Ok);
    }
    else {
        // Username is unique, proceed with registration
        qDebug() << "userMap size: " << userMap.size();
        int newID =User:: generateUniqueID();
        User newUser(newID,userName.toStdString(), password.toStdString(), email.toStdString(), phone.toStdString());
        userMap[newID]=newUser;
        qDebug() << "userMap size: " << userMap.size();
        // Proceed with registration logic
        LogIn* logWindow = new LogIn(userMap);
        logWindow->show();
        this->hide();
    }

}