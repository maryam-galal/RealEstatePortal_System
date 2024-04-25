#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RealEstatePortal_System.h"

class RealEstatePortal_System : public QMainWindow
{
    Q_OBJECT

public:
    RealEstatePortal_System(QWidget *parent = nullptr);
    ~RealEstatePortal_System();

private:
    Ui::RealEstatePortal_SystemClass ui;
};
