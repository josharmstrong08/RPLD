#ifndef DISPLAYCONFIGWIDGET_H
#define DISPLAYCONFIGWIDGET_H

#include <QWidget>
#include <QLabel>


class DisplayConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayConfigWidget(QWidget *parent = 0);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    QLabel *currentlyDraggingLabel;

signals:
    
public slots:

};

#endif // DISPLAYCONFIGWIDGET_H
