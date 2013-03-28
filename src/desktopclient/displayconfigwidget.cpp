#include "displayconfigwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QEvent>
#include <QDebug>
#include <QMessageBox>

DisplayConfigWidget::DisplayConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    QScrollArea *scrollArea = new QScrollArea();
    QWidget *containerWidget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout();
    QLabel *label = new QLabel();
    QHBoxLayout *hlayout = new QHBoxLayout(this);

    label->setPixmap(QPixmap(":/images/matrix_icon.png"));
    label->installEventFilter(this);
    label->setMouseTracking(true);

    gridLayout->addWidget(label, 0, 0);
    containerWidget->setLayout(gridLayout);
    scrollArea->setWidget(containerWidget);
    hlayout->addWidget(scrollArea);
    this->setLayout(hlayout);
}

bool DisplayConfigWidget::eventFilter(QObject *obj, QEvent *event)
{
    qDebug() << "Event filter: " << event->type();
    if (event->type() == QEvent::MouseButtonPress) {
        this->currentlyDraggingLabel = static_cast<QLabel *>(obj);
        QMessageBox::information(this, "debug", "mouse pressed");
        return true;
    } else if (event->type() == QEvent::MouseButtonRelease) {
        this->currentlyDraggingLabel = NULL;

    } else {
        return QWidget::eventFilter(obj, event);
    }
}
