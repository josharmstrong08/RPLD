#include "displayconfigwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QScrollArea>

DisplayConfigWidget::DisplayConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    QScrollArea *scrollArea = new QScrollArea();
    QWidget *containerWidget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout();
    QLabel *label = new QLabel("DisplayConfigWidget", this);
    QHBoxLayout *hlayout = new QHBoxLayout(this);

    gridLayout->addWidget(label, 0, 0);
    containerWidget->setLayout(gridLayout);
    scrollArea->setWidget(containerWidget);
    hlayout->addWidget(scrollArea);
    this->setLayout(hlayout);
}
