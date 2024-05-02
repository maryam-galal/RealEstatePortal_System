#pragma once

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QMouseEvent>

class PropertyWidget : public QFrame
{
    Q_OBJECT

public:
    PropertyWidget(const QString& picturePath, const QString& name, double price, QWidget* parent = nullptr);
    ~PropertyWidget();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QString m_picturePath;
    QString m_name;
    double m_price;
    QLabel* m_pictureLabel;
    QLabel* m_nameLabel;
    QLabel* m_priceLabel;
};
