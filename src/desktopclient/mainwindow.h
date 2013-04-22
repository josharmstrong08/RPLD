#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rpldclient.h"
//#include "displayconfigwidget.h"
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
    void on_connectButton_clicked();

    void connectionStatusChanged(RPLDClient::ConnectionStatus status);
    void recievedSetting(QString settingName, QVariant settingValue);

private:
    Ui::MainWindow *ui;
    //DisplayConfigWidget *displayConfigWidget;
    RPLDClient *communicationsClient;
    QColor textColor;
    RPLDClient::ConnectionStatus connectionStatus;
};

#endif // MAINWINDOW_H
