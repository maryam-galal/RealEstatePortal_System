#include "propertywidget.h"
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>

PropertyWidget::PropertyWidget(const QString& picturePath, const QString& name, double price, QWidget* parent)
    : QFrame(parent), m_picturePath(picturePath), m_name(name), m_price(price)
{
    // Set frame properties
    setStyleSheet("PropertyWidget { border: 1px solid gray; border-radius: 5px; }");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setCursor(Qt::PointingHandCursor);

    // Create QLabel for picture
    m_pictureLabel = new QLabel(this);
    QPixmap pixmap(m_picturePath);
    pixmap = pixmap.scaled(200, 250, Qt::KeepAspectRatio);
    m_pictureLabel->setPixmap(pixmap);

    // Create QLabel for name
    m_nameLabel = new QLabel(m_name, this);
    m_nameLabel->setAlignment(Qt::AlignCenter);

    // Create QLabel for price
    m_priceLabel = new QLabel(QString::number(m_price), this);
    m_priceLabel->setAlignment(Qt::AlignCenter);

    // Layout setup
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_pictureLabel);
    layout->addWidget(m_nameLabel);
    layout->addWidget(m_priceLabel);
    layout->setAlignment(Qt::AlignCenter); // Align widgets to the center
    layout->setSpacing(10); // Adjust spacing between widgets
    layout->setContentsMargins(5, 5, 5, 5); // Adjust margins

    setLayout(layout);

    // Install event filter
    installEventFilter(this);
}

PropertyWidget::~PropertyWidget()
{
    // Cleanup resources, if needed
    delete m_pictureLabel;
    delete m_nameLabel;
    delete m_priceLabel;
}

bool PropertyWidget::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == this && event->type() == QEvent::Enter) {
        qDebug() << "Mouse entered widget";
        // Create drop shadow effect
        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
        effect->setBlurRadius(10);
        effect->setOffset(3, 3);
        setGraphicsEffect(effect);
    }
    else if (obj == this && event->type() == QEvent::Leave) {
        qDebug() << "Mouse left widget";
        // Remove drop shadow effect
        setGraphicsEffect(nullptr);
    }
    return QFrame::eventFilter(obj, event);
}

void PropertyWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        // Emit signal to indicate that the widget is clicked
        emit clicked();
    }
}
