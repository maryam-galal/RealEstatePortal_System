#include "UserProfile.h"
#include "UserHomePage.h"
#include <QString>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>

UserProfile::UserProfile(std::map<int, User>& userMap, const User& user, QWidget* parent)
    : QMainWindow(parent), userMap(userMap), currentUser(user), r(new Register(userMap))
{
    ui.setupUi(this);
    ui.NameText->setPlainText(QString::fromStdString(currentUser.getUserName()));
    ui.PasswordText->setPlainText(QString::fromStdString(currentUser.getPassword()));
    ui.EmailText->setPlainText(QString::fromStdString(currentUser.getEmail()));
    ui.PhoneText->setPlainText(QString::fromStdString(currentUser.getPhone()));
    connect(ui.HomeButton, SIGNAL(clicked()), this, SLOT(on_Homebutton_clicked()));
    connect(ui.editButton, SIGNAL(clicked()), this, SLOT(on_Editbutton_clicked()));
}

UserProfile::~UserProfile()
{
    delete r; // Release the memory allocated for the Register instance
}

bool UserProfile::validateUserInput(const QString& newUserName, const QString& newPassword, const QString& newEmail, const QString& newPhone) const
{
    // Check if username is unique
    if (newUserName.isEmpty() || (newUserName != QString::fromStdString(currentUser.getUserName()) && r->isUsernameExists(newUserName))) {
        QMessageBox::warning(parentWidget(), QString("Username Error"), QString("This username is already taken. Please choose a different one."));
        return false;
    }

    // Check if password is at least 8 characters, contains numbers and letters, and matches confirmation password
    if (!newPassword.isEmpty() && newPassword != QString::fromStdString(currentUser.getPassword()) && (newPassword.length() < 8 || !newPassword.contains(QRegularExpression("[0-9]")) || !newPassword.contains(QRegularExpression("[a-zA-Z]")))) {
        QMessageBox::warning(parentWidget(), QString("Password Error"), QString("Password must be at least 8 characters long, contain at least one letter and one digit, and match the confirmation password."));
        return false;
    }

    // Check if email is in appropriate format
    if (!newEmail.isEmpty() && !r->isEmailValid(newEmail)) {
        QMessageBox::warning(parentWidget(), QString("Email Error"), QString("Please enter a valid email address."));
        return false;
    }

    // Check if phone number is numeric and 11 digits long
    if (!newPhone.isEmpty() && !r->isPhoneNumberValid(newPhone)) {
        QMessageBox::warning(parentWidget(), QString("Phone Number Error"), QString("Please enter a valid phone number (11 digits)."));
        return false;
    }

    return true; // All validation checks passed
}

void UserProfile::on_Editbutton_clicked()
{
    QString newUserName = ui.NameText->toPlainText();
    QString newPassword = ui.PasswordText->toPlainText();
    QString newEmail = ui.EmailText->toPlainText();
    QString newPhone = ui.PhoneText->toPlainText();

    // Validate user input
    if (!validateUserInput(newUserName, newPassword, newEmail, newPhone)) {
        return; // Validation failed, return without further processing
    }

    qDebug() << "Before updating currentUser: " << QString::fromStdString(currentUser.getUserName()) << " "
        << QString::fromStdString(currentUser.getPassword()) << " "
        << QString::fromStdString(currentUser.getEmail()) << " "
        << QString::fromStdString(currentUser.getPhone());

    // Update the currentUser object with the new information
    currentUser.setUserName(newUserName.toStdString());
    currentUser.setPassword(newPassword.toStdString());
    currentUser.setEmail(newEmail.toStdString());
    currentUser.setPhone(newPhone.toStdString());

    // After updating the currentUser object
    qDebug() << "After updating currentUser: " << QString::fromStdString(currentUser.getUserName()) << " "
        << QString::fromStdString(currentUser.getPassword()) << " "
        << QString::fromStdString(currentUser.getEmail()) << " "
        << QString::fromStdString(currentUser.getPhone());

    // Update the user's information in the userMap
    userMap[currentUser.getId()] = currentUser;
    qDebug() << "userMap size: " << userMap.size();
    // Update the UI elements displaying the user's information
    ui.NameText->setPlainText(newUserName);
    ui.PasswordText->setPlainText(newPassword);
    ui.EmailText->setPlainText(newEmail);
    ui.PhoneText->setPlainText(newPhone);
    qDebug() << "userMap size: " << userMap.size();

    // Use 'this' instead of 'parentWidget()' here
    QMessageBox::information(this, "Success", "User information updated successfully.");
}

void UserProfile::on_Homebutton_clicked()
{
    // Create an instance of UserHomePage with the provided userList and currentUser
    UserHomePage* userHWindow = new UserHomePage(userMap, currentUser);
    userHWindow->show();
    this->hide();
}
