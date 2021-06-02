#include "wheel_speed1.h"
#include "ui_wheel_speed1.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>


wheel_speed1::wheel_speed1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wheel_speed1)
{
    ui->setupUi(this);
    QPixmap kolo("D:/qt_workspace/MILF_sensors_visualization/kolo.png");
    int w = ui->label_pic_WR->width();
    int h = ui->label_pic_WR->height();
    ui->label_pic_WR->setPixmap(kolo.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_pic_WL->setPixmap(kolo.scaled(w,h,Qt::KeepAspectRatio));

    //![1]
        setL = new QBarSet("Left");
        setR = new QBarSet("Right");

        *setL << curr_speed_L;
        *setR << curr_speed_R;
    //![1]
    //!
    //!

        ui->num_speedR->display(curr_speed_R);
        ui->num_speedL->display(curr_speed_L);

    //![2]
        series = new QBarSeries();
        series->append(setL);
        series->append(setR);

    //![2]

        //![3]
            chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Wheels speed");
            chart->setAnimationOptions(QChart::SeriesAnimations);
        //![3]

        //![4]
            QStringList categories;
            categories << "Wheels";
            QBarCategoryAxis *axisX = new QBarCategoryAxis();
            axisX->append(categories);
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);

            QValueAxis *axisY = new QValueAxis();
            axisY->setRange(-150,150);
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);
        //![4]

        //![5]
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);
        //![5]

        //![6]
            chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->setMinimumSize(350, 600);
            chartView->setParent(ui->frame);
        //![6] 
}

wheel_speed1::~wheel_speed1()
{
    delete ui;
}

void wheel_speed1::update_speed(int sensor, int value){
    QPixmap kolo_R("D:/qt_workspace/MILF_sensors_visualization/koloR.png");
    QPixmap kolo_L("D:/qt_workspace/MILF_sensors_visualization/koloL.png");
    QPixmap kolo("D:/qt_workspace/MILF_sensors_visualization/kolo.png");
    int w = ui->label_pic_WR->width();
    int h = ui->label_pic_WR->height();

    if(sensor == 0){ // right wheel

        curr_speed_R = value;
        *setR << curr_speed_R;

        series->append(setR);
        speed_Disp();

        ui->num_speedR->display(value);

        if (value == 0) {
            ui->label_pic_WR->setPixmap(kolo.scaled(w,h,Qt::KeepAspectRatio));
        }
        else if(value > 0){
            ui->label_pic_WR->setPixmap(kolo_R.scaled(w,h,Qt::KeepAspectRatio));
        }
        else {
            ui->label_pic_WR->setPixmap(kolo_L.scaled(w,h,Qt::KeepAspectRatio));
        }


    }
    else if(sensor == 1){ // left wheel
        curr_speed_L = value;
        *setL << curr_speed_L;
        series->append(setL);
        speed_Disp();

        ui->num_speedL->display(value);

        if (value == 0) {
            ui->label_pic_WL->setPixmap(kolo.scaled(w,h,Qt::KeepAspectRatio));
        }
        else if(value > 0){
            ui->label_pic_WL->setPixmap(kolo_R.scaled(w,h,Qt::KeepAspectRatio));
        }
        else {
            ui->label_pic_WL->setPixmap(kolo_L.scaled(w,h,Qt::KeepAspectRatio));
        }
    }
    else{
        //ERROR
    }
}

void wheel_speed1::speed_Disp()
{
    chartView->update(); //or charView.repaint();
}
