#include "LogIn.h"
#include "RealEstatePortal_System.h"
#include "UserHomePage.h"
#include <qmessagebox.h>
LogIn::LogIn(std::map<int, User>& userMap,QWidget *parent)
	: QMainWindow(parent),userMap(userMap)
{
	ui.setupUi(this);
	connect(ui.HomeButton, SIGNAL(clicked()), this, SLOT(on_Homebutton_clicked())); // Connect button click to slot
    connect(ui.Login, SIGNAL(clicked()), this, SLOT(on_Loginbutton_clicked())); // Connect button click to slot
}

LogIn::~LogIn()
{}
bool LogIn::isValidCredentials(const QString& username, const QString& password) const
{
    // Check if the username exists and the password matches
    for (auto pair: userMap) {
        if (QString::fromStdString(pair.second.getUserName()) == username && QString::fromStdString(pair.second.getPassword()) == password) {
            return true; // Username and password are correct
        }
    }
    return false; // Username or password is incorrect
}
void LogIn::on_Loginbutton_clicked()
{
    QString userName = ui.name->toPlainText();
    QString password = ui.pass->toPlainText();

    // Validate the credentials
    if (!isValidCredentials(userName, password)) {
        // Username or password is incorrect, show an alert
        QMessageBox::warning(this, "Invalid Credentials", "Invalid username or password. Please check your credentials and try again.", QMessageBox::Ok);
    }
    else {
        auto currentUserIter = std::find_if(userMap.begin(), userMap.end(), [&](const auto& pair) {
            return QString::fromStdString(pair.second.getUserName()) == userName && QString::fromStdString(pair.second.getPassword()) == password;
            });

        // Username and password are correct, proceed to user home page
        UserHomePage* user1Window = new UserHomePage(userMap, currentUserIter->second);
        user1Window->show();
        this->hide();
    }
}
void LogIn ::on_Homebutton_clicked()
{
    // Create an instance of the Second window
    RealEstatePortal_System* homeWindow = new RealEstatePortal_System(userMap);
    homeWindow->show(); // Show the Second window
    this->hide();
}