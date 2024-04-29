#include "RealEstatePortal_System.h"
#include "LogIn.h"
#include "Register.h"
#include"User.h"
RealEstatePortal_System::RealEstatePortal_System(std::map<int, User>& userMap, QWidget* parent)
    : QMainWindow(parent), userMap(userMap)
{
    ui.setupUi(this);
    connect(ui.logInButton, SIGNAL(clicked()), this, SLOT(on_button_clicked())); // Connect button click to slot
    connect(ui.RegisterButton, SIGNAL(clicked()), this, SLOT(on_Regbutton_clicked())); // Connect button click to slot
}

RealEstatePortal_System::~RealEstatePortal_System()
{
}
void RealEstatePortal_System::on_Regbutton_clicked()
{
    Register* regWindow = new Register(userMap);
    regWindow->show(); // Show the Second window
    this->hide();

}
void RealEstatePortal_System::on_button_clicked()
{
    // Create an instance of the Second window
    LogIn* LogWindow = new LogIn(userMap);
    LogWindow->show(); // Show the Second window
    this->hide();
}
