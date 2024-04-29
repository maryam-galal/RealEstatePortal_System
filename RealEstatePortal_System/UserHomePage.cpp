#include "UserHomePage.h"
#include "RealEstatePortal_System.h"
#include "UserProfile.h"
UserHomePage::UserHomePage(std::map<int, User>& userMap, const User& user, QWidget* parent)
    : QMainWindow(parent), userMap(userMap), currentUser(user)
{
    ui.setupUi(this);
    connect(ui.LogOutButton, SIGNAL(clicked()), this, SLOT(on_Logoutbutton_clicked()));
    connect(ui.UserProfileButton, SIGNAL(clicked()), this, SLOT(on_Profilebutton_clicked()));
}


UserHomePage::~UserHomePage()
{}
void UserHomePage::on_Profilebutton_clicked()
{
    UserProfile* profileWindow = new UserProfile(userMap, currentUser, nullptr);
    profileWindow->show();
    this->hide();
}

void UserHomePage::on_Logoutbutton_clicked()
{
    // Create an instance of the Second window
    RealEstatePortal_System* homeWindow = new RealEstatePortal_System(userMap);
    homeWindow->show(); // Show the Second window
    this->hide();
}
