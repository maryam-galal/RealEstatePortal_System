#include "User_management.h"
#include "User.h"
#include "RealEstatePortal_System.h"
#include "UserHomePage.h"
#include <QVBoxLayout>
#include <QTableWidget>
#include <iostream>
#include <QMessageBox>
using namespace std;
User_management::User_management(std::map<int, User>& userMap, QWidget* parent)
    : QMainWindow(parent), userMap(userMap)
{
    ui.setupUi(this);
    // connect(ui.Dashboardbutton, SIGNAL(clicked()), this, SLOT(on_Dashbutton_clicked())); // Connect button click to slot
    // connect(ui.manage_listingsButton, SIGNAL(clicked()), this, SLOT(on_managelbutton_clicked())); // Connect button click to slot
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    GenerateUsersTable(userMap);
    connect(ui.tableWidget, &QTableWidget::itemSelectionChanged, this, &User_management::selected_row);
    connect(ui.SaveButton, &QPushButton::clicked, this, &User_management::saveUser);
    connect(ui.RemoveButton, &QPushButton::clicked, this, &User_management::removeUser);
}



void User_management::GenerateUsersTable(const std::map<int, User>& usersMap)
{
    ui.tableWidget->setColumnCount(5);
    ui.tableWidget->setColumnWidth(0, 100);
    ui.tableWidget->setColumnWidth(1, 120);
    ui.tableWidget->setColumnWidth(2, 160);
    ui.tableWidget->setColumnWidth(3, 120);   // Set the width of column 3 to 80 pixels
    ui.tableWidget->setColumnWidth(4, 140);

    ui.tableWidget->setHorizontalHeaderLabels(QStringList() << "ID" << "Username" << "E-Mail" << "Password" << "Phone Number");

    ui.tableWidget->setRowCount(usersMap.size());

    int row = 0;
    bool alternateColor = false;
    for (const auto& pair : usersMap)
    {
        const User& user = pair.second;
        QTableWidgetItem* userID = new QTableWidgetItem(QString::number(pair.first));
        QTableWidgetItem* usernameItem = new QTableWidgetItem(QString::fromStdString(user.getUserName()));
        QTableWidgetItem* passwordItem = new QTableWidgetItem(QString::fromStdString(user.getPassword()));
        QTableWidgetItem* EmailItem = new QTableWidgetItem(QString::fromStdString(user.getEmail()));
        QTableWidgetItem* phonenumberItem = new QTableWidgetItem(QString::fromStdString(user.getPhone()));
        userID->setTextAlignment(Qt::AlignCenter);
        usernameItem->setTextAlignment(Qt::AlignCenter);
        passwordItem->setTextAlignment(Qt::AlignCenter);
        EmailItem->setTextAlignment(Qt::AlignCenter);
        phonenumberItem->setTextAlignment(Qt::AlignCenter);
        if (alternateColor) {
            userID->setBackground(QColor("#f0f0f0"));
            usernameItem->setBackground(QColor("#f0f0f0"));
            passwordItem->setBackground(QColor("#f0f0f0"));
            EmailItem->setBackground(QColor("#f0f0f0"));
            phonenumberItem->setBackground(QColor("#f0f0f0"));
        }
        else {
            userID->setBackground(QColor("#ffffff"));
            usernameItem->setBackground(QColor("#ffffff"));
            passwordItem->setBackground(QColor("#ffffff"));
            EmailItem->setBackground(QColor("#ffffff"));
            phonenumberItem->setBackground(QColor("#ffffff"));
        }
        ui.tableWidget->setItem(row, 0, userID);
        ui.tableWidget->setItem(row, 1, usernameItem);
        ui.tableWidget->setItem(row, 2, EmailItem);
        ui.tableWidget->setItem(row, 3, passwordItem);
        ui.tableWidget->setItem(row, 4, phonenumberItem);
        alternateColor = !alternateColor;
        ++row;
    }
    ui.tableWidget->setAlternatingRowColors(true);
}

User_management::~User_management()
{}

void User_management::selected_row() {
    int selectedRow = ui.tableWidget->currentRow();
    QTableWidgetItem* idItem = ui.tableWidget->item(selectedRow, 0); // Assuming ID is in the first column
    if (idItem) {
        int id = idItem->text().toInt(); 
        auto it = userMap.find(id);
        if (it != userMap.end()) {
            const User& user = it->second;           
            ui.Usernamelabel->setText(QString::fromStdString(user.getUserName()));
            ui.passwordLabel->setText(QString::fromStdString(user.getPassword()));
            ui.EmailLabel->setText(QString::fromStdString(user.getEmail()));
            ui.PhoneNumberLabel->setText(QString::fromStdString(user.getPhone()));
        }
        else {
            ui.Usernamelabel->clear();
            ui.passwordLabel->clear();
            ui.EmailLabel->clear();
            ui.PhoneNumberLabel->clear();
        }
    }
    else {
        ui.Usernamelabel->clear();
        ui.passwordLabel->clear();
        ui.EmailLabel->clear();
        ui.PhoneNumberLabel->clear();
    }
}

bool User_management::isUsernameExists(const QString& username) const
{
    for (const auto& pair : userMap) {
        if (QString::fromStdString(pair.second.getUserName()) == username) {
            return true; // Username exists
        }
    }
    return false; // Username does not exist
}

bool User_management::isPasswordValid(const QString& password) const
{
    // Password must be at least 8 characters, contain at least one digit and one letter
    return password.length() >= 8 && password.contains(QRegularExpression("[0-9]")) && password.contains(QRegularExpression("[a-zA-Z]"));
}


bool User_management::isEmailValid(const QString& email) const
{
    // Use regular expression to check email format
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return regex.match(email).hasMatch();
}

bool User_management::isPhoneNumberValid(const QString& phone) const
{ 
    return phone.length() == 11;
}

void User_management::saveUser() {
    int selectedRow = ui.tableWidget->currentRow();
    QTableWidgetItem* idItem = ui.tableWidget->item(selectedRow, 0);
    bool changeUserName = false;
    if (idItem) {
        int id = idItem->text().toInt(); 
        auto it = userMap.find(id);
        if (it != userMap.end()) {
            User& user = it->second;
            QString userName = ui.Usernamelabel->toPlainText();
            QString password = ui.passwordLabel->toPlainText();
            QString email = ui.EmailLabel->toPlainText();
            QString phone = ui.PhoneNumberLabel->toPlainText();
            if (user.getUserName() != ui.Usernamelabel->toPlainText().toStdString()) {
                changeUserName = true;
            }
            if ((changeUserName)&&(isUsernameExists(userName))) {
                QMessageBox::warning(this, "Invalid Input", "The username is already in use. Please choose a different username.", QMessageBox::Ok);
            }
            if (!isPasswordValid(password)) {
                QMessageBox::warning(this, "Invalid Input", "Password must be at least 8 characters long and contain at least one digit and one letter.", QMessageBox::Ok);
            }
            if (!isEmailValid(email)) {
                QMessageBox::warning(this, "Invalid Input", "Invalid email format. Please enter a valid email address.", QMessageBox::Ok);
            }
            if (!isPhoneNumberValid(phone)) {
                QMessageBox::warning(this, "Invalid Input", "Phone number must be numeric and exactly 11 digits long.", QMessageBox::Ok);
            }
            if (changeUserName) {
                user.setUserName(ui.Usernamelabel->toPlainText().toStdString());
            }
            user.setPassword(ui.passwordLabel->toPlainText().toStdString());
            user.setEmail(ui.EmailLabel->toPlainText().toStdString());
            user.setPhone(ui.PhoneNumberLabel->toPlainText().toStdString());
        }
    }
    GenerateUsersTable(userMap);
}

void User_management::removeUser() {
    int selectedRow = ui.tableWidget->currentRow();
    QTableWidgetItem* idItem = ui.tableWidget->item(selectedRow, 0);
    if (idItem) {
        int id = idItem->text().toInt();
        auto it = userMap.find(id);
        if (it != userMap.end()) {
            userMap.erase(it);
            GenerateUsersTable(userMap);
            ui.Usernamelabel->clear();
            ui.passwordLabel->clear();
            ui.PhoneNumberLabel->clear();
            ui.EmailLabel->clear();
        }
    }
}