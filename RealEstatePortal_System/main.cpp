#include "RealEstatePortal_System.h"
#include <QtWidgets/QApplication>
#include <map>
#include "User.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

std::map<int, User> userMap; // Use map instead of vector

void readUsersFromFile() {
    QFile file("RegisterFile.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in.readLine(); // Skip headers
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList data = line.split(",");
            if (data.size() == 5) {
                int userId = data[0].toInt();
                QString userName = data[1];
                QString password = data[2];
                QString email = data[3];
                QString phone = data[4];
                User newUser(userId, userName.toStdString(), password.toStdString(), email.toStdString(), phone.toStdString());
                userMap[userId] = newUser; // Insert user into map
            }
        }
        file.close();
        qDebug() << "User data has been read from file successfully.";
    }
    else {
        qDebug() << "Error: Unable to open file for reading";
    }
}

void writeUsersToFile() {
    QFile file("RegisterFile.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Id,UserName,Password,Email,PhoneNumber\n";
        qDebug() << "userMap size: " << userMap.size();
        for (const auto& pair : userMap) {
            const User& user = pair.second;
            qDebug() << QString::number(user.getId()) << ","
                << QString::fromStdString(user.getUserName()) << ","
                << QString::fromStdString(user.getPassword()) << ","
                << QString::fromStdString(user.getEmail()) << ","
                << QString::fromStdString(user.getPhone()) << "\n";
        }
        for (const auto& pair : userMap) {
            const User& user = pair.second;
            out << QString::number(user.getId()) << ","
                << QString::fromStdString(user.getUserName()) << ","
                << QString::fromStdString(user.getPassword()) << ","
                << QString::fromStdString(user.getEmail()) << ","
                << QString::fromStdString(user.getPhone()) << "\n";
        }
        file.close();
        qDebug() << "User data has been written to file successfully.";
    }
    else {
        qDebug() << "Error: Unable to open file for writing.";
    }
}

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    RealEstatePortal_System w(userMap); // Pass userMap to RealEstatePortal_System
    w.show();

    readUsersFromFile(); // Load data from file into the program at the beginning

    // Connect to the aboutToQuit signal of QApplication to save data to file at the end
    QObject::connect(&a, &QCoreApplication::aboutToQuit, [&]() {
        writeUsersToFile(); // Save data to file at the end of the program
        });

    return a.exec();
}
