#include "homepage.h"
#include "Property.h" 
#include "ui_homepage.h"
#include "propertywidget.h"
#include <QScrollBar>
#include <qtextformat.h>

HomePage::HomePage(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::HomePage)
{
    ui->setupUi(this);

    // Get a pointer to the existing scrollArea and gridLayout from the UI
    QScrollArea* scrollArea = ui->scrollArea;
    QGridLayout* gridLayout = ui->gridLayout;

    std::map<int, Property> properties;

    // Populate the map with Property objects
    QStringList picturePaths = { "C:/Users/Lenovo/Downloads/house1.jpeg", "C:/Users/Lenovo/Downloads/house2.jpeg", "C:/Users/Lenovo/Downloads/house3.jpeg","C:/Users/Lenovo/Downloads/house1.jpeg", "C:/Users/Lenovo/Downloads/house2.jpeg", "C:/Users/Lenovo/Downloads/house3.jpeg","C:/Users/Lenovo/Downloads/house1.jpeg", "C:/Users/Lenovo/Downloads/house2.jpeg", "C:/Users/Lenovo/Downloads/house3.jpeg","C:/Users/Lenovo/Downloads/house1.jpeg", "C:/Users/Lenovo/Downloads/house2.jpeg", "C:/Users/Lenovo/Downloads/house3.jpeg" };
    QStringList names = { "Property 1", "Property 2", "Property 3","Property 4", "Property 5", "Property 6" ,"Property 7", "Property 8", "Property 9","Property 10", "Property 11", "Property 12" };
    QList<double> prices = { 100.0, 200.0, 300.0 ,100.0, 200.0, 300.0,100.0, 200.0, 300.0 ,100.0, 200.0, 300.0 };

    int numColumns = 4;

    // Populate the map with Property objects
    for (int i = 0; i < picturePaths.size(); ++i) {
        properties[i] = Property(picturePaths[i], names[i], prices[i], i);
    }

    // Iterate over the map in reverse order
    for (auto it = properties.rbegin(); it != properties.rend(); ++it) {
        const Property& property = it->second;

        // Calculate row and column values based on the total number of columns
        int row = (properties.size() - property.id() - 1) / numColumns;
        int col = (properties.size() - property.id() - 1) % numColumns;

        // Create and add the property widget to the grid layout
        PropertyWidget* propertyWidget = new PropertyWidget(property.picturePath(), property.name(), property.Price());
        propertyWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        gridLayout->addWidget(propertyWidget, row, col);
    }

    // Set the widget contents of the scroll area
    scrollArea->setWidget(ui->scrollAreaWidgetContents);

    // Set the vertical scroll policy of the scroll area
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // Ensure the scroll area widget contents can expand vertically
    scrollArea->widget()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
}

HomePage::~HomePage()
{
    delete ui;
}
