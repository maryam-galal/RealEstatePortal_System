#pragma once

#include <QMainWindow>
#include "ui_Register.h"
#include "User.h"
class Register : public QMainWindow
{
	Q_OBJECT

public:
	Register(std::map<int, User>& userMap, QWidget *parent = nullptr);
	~Register();

	bool isUsernameExists(const QString& username) const;

	bool isPasswordValid(const QString& password) const;

	

	bool isEmailValid(const QString& email) const;

	bool isPhoneNumberValid(const QString& phone) const;



private slots:
	void on_Homebutton_clicked();
	void on_Regbutton_clicked();

private:
	Ui::RegisterClass ui;
	std::map<int, User>& userMap; // Reference to the userList Map
};
