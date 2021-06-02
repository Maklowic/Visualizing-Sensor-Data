#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtCharts>
#include<QChartView>
#include<QBarSet>
#include<QBarSeries>
#include "mapped_path.h"
#include "wheel_speed1.h"
#include "connection.h"
#include "sensor_state.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_OpenWS_clicked();

    void on_pushButton_OpenC_clicked();

    void on_pushButton_OpenMP_clicked();

    void on_pushButton_OpenSS_clicked();

private:
    Ui::MainWindow *ui;
    mapped_path *Window_MP;
    connection *Window_C;
    sensor_state *Window_SS;
    wheel_speed1 *Window_WS;
};
#endif // MAINWINDOW_H
