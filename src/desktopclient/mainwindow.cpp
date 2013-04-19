#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "displayconfigwidget.h"
#include <QMessageBox>
#include <QColorDialog>

#include <cstdio>
#include <QDebug>
#include <QAbstractSlider>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Instead of using the config widget, a simply number slider is used for
     * horizontal-only configurations.
    displayConfigWidget = new DisplayConfigWidget(this);
    int configLabelIndex = ui->gridLayout->indexOf(ui->matrixConfigLabel);
    int row, column, rowspan, columnspan;
    ui->gridLayout->getItemPosition(configLabelIndex, &row, &column, &rowspan, &columnspan);
    ui->gridLayout->addWidget(displayConfigWidget, row, column + 1);
    */

    this->textColor = QColor(Qt::white);
    this->ui->colorButton->setStyleSheet("background-color: white");

    this->communicationsClient = new RPLDClient(this);
    connect(this->communicationsClient, SIGNAL(statusChanged(RPLDClient::ConnectionStatus)), this, SLOT(connectionStatusChanged(RPLDClient::ConnectionStatus)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_actionContents_triggered()
{
    QMessageBox::information(this, "Raspberry Pi LED Display", "Help is not yet implemented");
}

void MainWindow::on_colorButton_clicked()
{
    QColor tempColor = QColorDialog::getColor(Qt::white, this, "Select Text Color");
    if (tempColor.isValid() == true) {
        this->textColor = tempColor;
        QString qss = QString("background-color: %1").arg(this->textColor.name());
        this->ui->colorButton->setStyleSheet(qss);
    }
}

void MainWindow::on_uploadButton_clicked()
{   
    // This will upload the contents to the server
    this->communicationsClient->sendSetting("text", this->ui->textEdit->text());
    this->communicationsClient->sendSetting("speed", this->ui->scrollSpeedSlider->value());
    QString colorString = QString::number(this->textColor.red()) + "," + QString::number(this->textColor.green()) + "," + QString::number(this->textColor.blue());
    this->communicationsClient->sendSetting("color", colorString);
    this->communicationsClient->sendSetting("matrixcount", this->ui->matrixCountSpinner->value());
}

void MainWindow::on_shutdownButton_clicked()
{
    // Sends a shutdown signal to the Pi to turn it off.
    this->communicationsClient->sendSetting("shutdown", 0);
    /*NEEDS TESTED ON PI!!!*/
}

void MainWindow::on_connectButton_clicked()
{
    // Try to connect to specified ip address
    this->communicationsClient->connectToServer(this->ui->ipAddress->text());
}

void MainWindow::connectionStatusChanged(RPLDClient::ConnectionStatus status)
{
    if (status == RPLDClient::CONNECTED) {
        this->ui->statusLabel->setText("Connected");
        this->ui->statusLabel->setStyleSheet("color: rgb(0, 255, 0)");
        this->ui->ipAddress->setEnabled(false);
        this->ui->connectButton->setEnabled(false);
        this->ui->uploadButton->setEnabled(true);
        this->ui->shutdownButton->setEnabled(true);
        this->ui->colorButton->setEnabled(true);
        this->ui->scrollSpeedSlider->setEnabled(true);
        this->ui->textEdit->setEnabled(true);
        //this->displayConfigWidget->setEnabled(true);
    } else if (status == RPLDClient::DISCONNECTED || RPLDClient::CONNECTING){
        if (status == RPLDClient::CONNECTING) {
            this->ui->statusLabel->setText("Connecting..");
            this->ui->statusLabel->setStyleSheet("color: rgb(255, 170, 0)");
        } else if (status == RPLDClient::DISCONNECTED) {
            this->ui->statusLabel->setText("Disconnected");
            this->ui->statusLabel->setStyleSheet("color: rgb(255, 0, 0)");
        }
        this->ui->ipAddress->setEnabled(true);
        this->ui->connectButton->setEnabled(true);
        this->ui->uploadButton->setEnabled(false);
        this->ui->shutdownButton->setEnabled(false);
        this->ui->colorButton->setEnabled(false);
        this->ui->scrollSpeedSlider->setEnabled(false);
        this->ui->textEdit->setEnabled(false);
        //this->displayConfigWidget->setEnabled(false);
    }
}
