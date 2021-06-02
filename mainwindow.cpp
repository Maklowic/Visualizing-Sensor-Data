#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_OpenWS_clicked()
{
    Window_WS = new wheel_speed1(this);
    Window_WS->show();
}

void MainWindow::on_pushButton_OpenC_clicked()
{
    Window_C = new connection(this);
    Window_C->show();
}


void MainWindow::on_pushButton_OpenMP_clicked()
{
    Window_MP = new mapped_path(this);
    Window_MP->show();

}

void MainWindow::on_pushButton_OpenSS_clicked()
{
    Window_SS = new sensor_state(this);
    Window_SS->show();
}
