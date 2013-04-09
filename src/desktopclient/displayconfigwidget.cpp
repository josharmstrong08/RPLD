#include "displayconfigwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <cassert>

DisplayConfigWidget::DisplayConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    this->currentlyDraggingLabel = NULL;

    QScrollArea *scrollArea = new QScrollArea();
    QWidget *containerWidget = new QWidget();
    gridLayout = new QGridLayout();

    QLabel *label = new QLabel();
    label->setPixmap(QPixmap(":/images/matrix_icon.png"));
    //label->setParent(this);
    label->resize(32,32);
    this->labels.append(label);
    label = new QLabel();
    label->setPixmap(QPixmap(":/images/matrix_icon.png"));
    //label->setParent(this);
    this->labels.append(label);
    label = new QLabel();
    label->setPixmap(QPixmap(":/images/matrix_icon.png"));
    //label->setParent(this);
    this->labels.append(label);

    QHBoxLayout *hlayout = new QHBoxLayout(this);


    //this->installEventFilter(this);
    this->setMouseTracking(true);

    gridLayout->addWidget(this->labels[0], 0, 0);
    gridLayout->addWidget(this->labels[1], 0, 1);
    gridLayout->addWidget(this->labels[2], 0, 2);
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
            //this->gridLayout->removeWidget(this->currentlyDraggingLabel);
            this->dragOffset = this->currentlyDraggingLabel->pos() - event->pos();
            break;
        }
    }
}

void DisplayConfigWidget::mouseReleaseEvent(QMouseEvent *event)
{
    assert(this->gridLayout->spacing() != -1);
    int leftmargin, topmargin, rightmargin, bottommargin;
    this->gridLayout->getContentsMargins(&leftmargin, &topmargin, &rightmargin, &bottommargin);
    int col = (event->x() - leftmargin) % (32 + this->gridLayout->spacing());
    this->gridLayout->addWidget(this->currentlyDraggingLabel, 0, col);
    this->currentlyDraggingLabel = NULL;
}

void DisplayConfigWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (this->currentlyDraggingLabel != NULL) {
        this->currentlyDraggingLabel->move(this->dragOffset + event->pos());
    }
}
