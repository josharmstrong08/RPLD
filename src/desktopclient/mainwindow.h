#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rpldcommunications.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_actionContents_triggered();
    void on_colorButton_clicked();

    void on_uploadButton_clicked();

    void on_shutdownButton_clicked();


private:
    Ui::MainWindow *ui;
    RPLDCommunications communications;
};

#endif // MAINWINDOW_H
