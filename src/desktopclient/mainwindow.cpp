#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
