#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: darkgray;");

    Window_WS = new wheel_speed1(this);
    Window_WS->setWindowTitle("Wheels Speed"); // Ustawia tytuł wyświetlanego okna
    Window_WS->hide();

    Window_MP = new mapped_path(this);
    Window_MP->setCentralWidget(Window_MP->chartView);
    Window_MP->setWindowTitle("Mapped Path"); // Ustawia tytuł wyświetlanego okna
    Window_MP->hide();

    Window_SS = new sensor_state(this);
    Window_SS->setWindowTitle("Sensors State"); // Ustawia tytuł wyświetlanego okna
    Window_SS->hide();

    Window_C = new connection(*Window_WS, *Window_MP, *Window_SS);
    Window_C->setWindowTitle("Connection"); // Ustawia tytuł wyświetlanego okna
    Window_C->hide();
}

MainWindow::MainWindow(wheel_speed1 &ws, mapped_path &mp, sensor_state &ss, connection &c, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    Window_WS = &ws;
    Window_MP = &mp;
    Window_SS = &ss;
    Window_C = &c;

    Window_WS->setWindowTitle("Wheels Speed"); // Ustawia tytuł wyświetlanego okna
    Window_WS->hide();

    Window_MP->setCentralWidget(Window_MP->chartView);
    Window_MP->setWindowTitle("Mapped Path"); // Ustawia tytuł wyświetlanego okna
    Window_MP->hide();

    Window_SS->setWindowTitle("Sensors State"); // Ustawia tytuł wyświetlanego okna
    Window_SS->hide();

    Window_C->setWindowTitle("Connection"); // Ustawia tytuł wyświetlanego okna
    Window_C->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 0 prawy, 1 lewy
void MainWindow::on_pushButton_OpenWS_clicked()
{
    Window_WS->show();
    Window_WS->updateSpeed(0,-10);
//    Window_WS->updateSpeed(1,150);
    Window_WS->updateSpeed(1,50);
//    Window_WS->updateSpeed(0,50);
//    Window_WS->updateSpeed(1,-80);
}

void MainWindow::on_pushButton_OpenC_clicked()
{
    Window_C->show();
}

void MainWindow::on_pushButton_OpenMP_clicked()
{
    Window_MP->show();
}

void MainWindow::on_pushButton_OpenSS_clicked()
{
    Window_SS->show();
//    Window_SS->updateSensor(1,0);
//    Window_SS->updateSensor(2,1);
//    Window_SS->updateSensor(3,1);
//    Window_SS->updateSensor(7,0);
//    Window_SS->updateSensor(4,9);
}


void MainWindow::on_pushButton_Exit_clicked()
{
    Window_SS->close();
    Window_MP->close();
    Window_WS->close();
    Window_C->close();
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Status:"));
    if(Window_C->connStatus())
        statusBar()->showMessage(tr("Status: Connected"));
    else
        statusBar()->showMessage(tr("Status: Not connected"));
}
