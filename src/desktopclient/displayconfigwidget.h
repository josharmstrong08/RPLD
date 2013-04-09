#ifndef DISPLAYCONFIGWIDGET_H
#define DISPLAYCONFIGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>


class DisplayConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayConfigWidget(QWidget *parent = 0);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent * event);

private:
    QLabel *currentlyDraggingLabel;
    QGridLayout *gridLayout;
    QVector<QLabel*> labels;

signals:
    
public slots:

};

#endif // DISPLAYCONFIGWIDGET_H
