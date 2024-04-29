#pragma once

#include <QMainWindow>
#include "ui_UserHomePage.h"
#include "User.h"

class UserHomePage : public QMainWindow
{
	Q_OBJECT

public:
	UserHomePage(std::map<int, User>& userMap, const User& user, QWidget* parent = nullptr);
	
	~UserHomePage();

private slots:
	void on_Logoutbutton_clicked();
	void on_Profilebutton_clicked();


private:
	Ui::UserHomePageClass ui;
	std::map<int, User>& userMap;
	User currentUser;
};
