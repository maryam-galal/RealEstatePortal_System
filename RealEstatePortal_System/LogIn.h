#pragma once

#include <QMainWindow>
#include "ui_LogIn.h"
#include "User.h"
class LogIn : public QMainWindow
{
	Q_OBJECT

public:
	LogIn(std::map<int, User>& userMap,QWidget *parent = nullptr);
	~LogIn();

	bool isValidCredentials(const QString& username, const QString& password) const;

private slots:
	void on_Homebutton_clicked();
	void on_Loginbutton_clicked();

private:
	Ui::LogInClass ui;
	std::map<int, User>& userMap;
};
