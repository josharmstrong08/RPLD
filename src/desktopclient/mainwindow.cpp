#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "displayconfigwidget.h"
#include <QMessageBox>
#include <QColorDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DisplayConfigWidget *displayConfigWidget = new DisplayConfigWidget(this);
    int configLabelIndex = ui->gridLayout->indexOf(ui->matrixConfigLabel);
    int row, column, rowspan, columnspan;
    ui->gridLayout->getItemPosition(configLabelIndex, &row, &column, &rowspan, &columnspan);
    ui->gridLayout->addWidget(displayConfigWidget, row, column + 1);
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
    QColorDialog::getColor(Qt::white, this, "Select Text Color");
}

void MainWindow::on_uploadButton_clicked()
{
    // This will upload the contents to the server
    // Need to create a class to send the data in over serialization.
    printf("upload pressed\n");
    fflush(stdout);
}

void MainWindow::on_shutdownButton_clicked()
{
    // Sends a shutdown signal to the Pi to turn it off.
    // Will either send
    printf("shutdown pressed\n");
     fflush(stdout);
}

void MainWindow::on_textEdit_returnPressed()
{
    // Will lock in the text and maybe upload the content?
    printf("Text entered\n");
     fflush(stdout);
}

void MainWindow::on_scrollSpeedSlider_sliderMoved(int position)
{
    // This will trigger when the slider is moved, force update the scroll speed.
    // Will forcefull update the scroll speed
    printf("slider moved to %d\n", position);
     fflush(stdout);
}
