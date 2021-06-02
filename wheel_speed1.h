/**
* @file wheelspeed1.h
* @brief Plik nagłówkowy dla wheelspeed1.cpp
*
* @author Michał Maćkowiak
*
*/

#ifndef WHEEL_SPEED1_H
#define WHEEL_SPEED1_H

#include <QMainWindow>
//#include <QDialog>
#include<QtCharts>
#include<QChartView>
#include<QBarSet>
#include<QBarSeries>
#include <QPixmap>

namespace Ui {
class wheel_speed1;
}

class wheel_speed1 : public QMainWindow
{
    Q_OBJECT

public:
    QChartView *chartView;
    QChart *chart;
    explicit wheel_speed1(QWidget *parent = nullptr);
    ~wheel_speed1();
    /** @brief Updates speed of the wheel.
    *  @param[in] which wheel.
    *  @Param[in] speed value.
    */
    void update_speed(int sensor, int speed);
    /** @brief Bar chart update.
    */
    void speed_Disp();
    int curr_speed_L = 80; //! Speed of the left wheel
    int curr_speed_R = -20; //! Speed of the right

private:
    Ui::wheel_speed1 *ui;

    QBarSet *setL;
    QBarSet *setR;
    QBarSeries *series;

};

#endif // WHEEL_SPEED1_H
