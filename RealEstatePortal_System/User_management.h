#pragma once
#include <QMainWindow>
#include"User.h"
#include "ui_User_management.h"

class User_management : public QMainWindow
{
	Q_OBJECT

public:
	User_management(std::map<int, User>& userMap, QWidget* parent = nullptr);
	void GenerateUsersTable(const std::map<int, User>& usersMap);
	void selected_row();
	void saveUser();
	void removeUser();
	~User_management();
	bool isUsernameExists(const QString& username) const;
	bool isPasswordValid(const QString& password) const;
	bool isEmailValid(const QString& email) const;
	bool isPhoneNumberValid(const QString& phone) const;

//private slots:
	//void on_Dashbutton_clicked();
	//void on_managelbutton_clicked();

private:
	Ui::User_managementClass ui;
	std::map<int, User>& userMap;
};


