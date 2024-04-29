#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RealEstatePortal_System.h"
#include "User.h"

class RealEstatePortal_System : public QMainWindow
{
    Q_OBJECT

public:
    RealEstatePortal_System(std::map<int, User>& userMap, QWidget* parent = nullptr);
    ~RealEstatePortal_System();

private slots:
    void on_button_clicked();
    void on_Regbutton_clicked();

private:
    Ui::RealEstatePortal_SystemClass ui;
    std::map<int, User>& userMap;
};
