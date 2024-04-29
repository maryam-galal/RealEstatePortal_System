#pragma once

#include <QMainWindow>
#include "ui_UserProfile.h"
#include"User.h"
#include "Register.h"
class UserProfile : public QMainWindow
{
	Q_OBJECT

public:
	UserProfile(std::map<int,User>& userMap, const User& user, QWidget* parent);
	~UserProfile();

	bool validateUserInput(const QString& newUserName, const QString& newPassword, const QString& newEmail, const QString& newPhone) const;

	

private slots:
	void on_Homebutton_clicked();
	void on_Editbutton_clicked();

private:
	Ui::UserProfileClass ui;
	std::map<int, User>& userMap;
	User currentUser;
	Register* r;
};
