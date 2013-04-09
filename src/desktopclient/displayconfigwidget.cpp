#include "displayconfigwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>

DisplayConfigWidget::DisplayConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    this->currentlyDraggingLabel = NULL;

    QScrollArea *scrollArea = new QScrollArea();
    QWidget *containerWidget = new QWidget();
    gridLayout = new QGridLayout();
    QLabel *label = new QLabel();
    this->labels.append(label);
    QHBoxLayout *hlayout = new QHBoxLayout(this);

    label->setPixmap(QPixmap(":/images/matrix_icon.png"));
    //this->installEventFilter(this);
    this->setMouseTracking(true);

    gridLayout->addWidget(label, 0, 0);
    containerWidget->setLayout(gridLayout);
    scrollArea->setWidget(containerWidget);
    hlayout->addWidget(scrollArea);
    this->setLayout(hlayout);
}

bool DisplayConfigWidget::eventFilter(QObject *obj, QEvent *event)
{
    //qDebug() << "Event filter: " << event->type();
    if (event->type() == QEvent::MouseButtonPress) {
        this->currentlyDraggingLabel = static_cast<QLabel *>(obj);
        qDebug() << "Mouse pressed";
        return true;
    } else if (event->type() == QEvent::MouseButtonRelease) {
        this->currentlyDraggingLabel = NULL;
        qDebug() << "Mouse released";
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        qDebug() << "Mouse move event";
        if (this->currentlyDraggingLabel != NULL) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            this->gridLayout->removeWidget(this->currentlyDraggingLabel);
            this->currentlyDraggingLabel->move(mouseEvent->x(), mouseEvent->y());
        }
        return true;
    } else {
        return QWidget::eventFilter(obj, event);
    }
}

void DisplayConfigWidget::mousePressEvent(QMouseEvent *event)
{
    this->currentlyDraggingLabel = NULL;
    for (int i = 0; i < this->labels.size(); i++) {
        if (this->labels.at(i)->underMouse() == true) {
            this->currentlyDraggingLabel = this->labels.at(i);
            this->gridLayout->removeWidget(this->currentlyDraggingLabel);
            break;
        }
    }
}

void DisplayConfigWidget::mouseReleaseEvent(QMouseEvent *event)
{
    this->currentlyDraggingLabel = NULL;
    this->gridLayout->addWidget(this->currentlyDraggingLabel, 0, 0, 0, 0);
}

void DisplayConfigWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (this->currentlyDraggingLabel != NULL) {
        this->currentlyDraggingLabel->move(event->x(), event->y());
    }
}
