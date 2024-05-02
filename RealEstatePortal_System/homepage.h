#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include <QScrollArea>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class HomePage; }
QT_END_NAMESPACE

class HomePage : public QMainWindow
{
    Q_OBJECT

public:
    HomePage(QWidget* parent = nullptr);
    ~HomePage();

private:
    Ui::HomePage* ui;
};

#endif // HOMEPAGE_H
