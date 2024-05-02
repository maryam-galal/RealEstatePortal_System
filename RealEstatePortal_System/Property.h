#pragma once
#include <QString>
#include <string>

class Property
{
public:

    Property()
        : m_picturePath(""), m_name(""), m_price(0.0), m_id(0) {}

    // Constructor taking QString arguments
    Property(const QString& picturePath, const QString& name, double price, int id)
        : m_picturePath(picturePath), m_name(name), m_price(price), m_id(id) {}

    // Constructor taking std::string arguments
    Property(const std::string& propertyName, const std::string& propertyLocation, float propertyPrice, float propertySpace, int roomNumbers)
        : propertyName(propertyName), propertyLocation(propertyLocation), m_price(propertyPrice), propertySpace(propertySpace), roomNumbers(roomNumbers) {}

    // Getters for QString members
    QString picturePath() const { return m_picturePath; }
    QString name() const { return m_name; }

    // Getters for other members
    double Price() const { return m_price; }
    int id() const { return m_id; }

private:
    // QString members
    QString m_picturePath;
    QString m_name;

    // std::string members
    std::string propertyName;
    std::string propertyLocation;

    // Other members
    double m_price;
    float propertySpace;
    int roomNumbers;
    int m_id;
};
