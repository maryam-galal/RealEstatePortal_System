#include "RealEstatePortal_System.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RealEstatePortal_System w;
    w.show();
    return a.exec();
}
