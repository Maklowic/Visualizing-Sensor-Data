#include "sensor_state.h"
#include "ui_sensor_state.h"

sensor_state::sensor_state(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sensor_state)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: darkgray;");
    //![1] pobranie obrazow oraz przypisanie do etykiet
    imgSensorPlat.load("D:/qt_workspace/MILF_sensors_visualization/wyspa_sensorow.png");
    int w = ui->label_pic_wyspa->width();
    int h = ui->label_pic_wyspa->height();
    ui->label_pic_wyspa->setPixmap(imgSensorPlat.scaled(w,h,Qt::KeepAspectRatio));

    imgActiveSens.load("D:/qt_workspace/MILF_sensors_visualization/red.png");
    int bok = ui->label_pic_w1->height();
    ui->label_pic_w1->setPixmap(imgActiveSens.scaled(bok,bok,Qt::KeepAspectRatio));

    // przypisanie uchwytu do tablicy na odpowiadajace mu miejsce
    // dzieki czemu mozna bedzie wywolywać metody etykiet indeksami
    // a nie wprowadzajac cala nazwe
    sensorsLabel[0] = ui->label_pic_w1;
    sensorsLabel[0]->hide();

    ui->label_pic_w2->setPixmap(imgActiveSens.scaled(bok,bok,Qt::KeepAspectRatio));
    sensorsLabel[1] = ui->label_pic_w2;
    sensorsLabel[1]->hide();

    ui->label_pic_w3->setPixmap(imgActiveSens.scaled(bok,bok,Qt::KeepAspectRatio));
    sensorsLabel[2] = ui->label_pic_w3;
    sensorsLabel[2]->hide();

    ui->label_pic_w4->setPixmap(imgActiveSens.scaled(bok,bok,Qt::KeepAspectRatio));
    sensorsLabel[3] = ui->label_pic_w4;
    sensorsLabel[3]->hide();

    ui->label_pic_w5->setPixmap(imgActiveSens.scaled(bok,bok,Qt::KeepAspectRatio));
    sensorsLabel[4] = ui->label_pic_w5;
    sensorsLabel[4]->hide();

}

void sensor_state::updateSensor(int witch, int state){
    if(witch > 5){
        qDebug() << "updateState ERROR: Wrong sensor number!";
    }
    else if (witch < 0){
        qDebug() << "updateState ERROR: Wrong sensor number!";
    }
    else{
        updateState(witch, state);
    }
}

void sensor_state::updateState(int witch, int state){
    // obsluga warunkow
    switch (state) {
    // czujnik nie wykrywa
    case 0:
        // schowanie znacznika jezeli jest pokazany
        if(!sensorsLabel[witch-1]->isHidden()){
            sensorsLabel[witch-1]->hide();
        }
        // inaczej nic nie rob
        else{
            break;
        }
        break;
    // czujnik wykrywa
    case 1:
        // jezeli schowany to pokaz znacznik
        if(!sensorsLabel[witch-1]->isHidden()){
            break;
        }
        //inaczej nic nie rob
        else{
            sensorsLabel[witch-1]->show();
        }
        break;
    // obsluga innych wartosci
    default:
        qDebug() << "updateState ERROR: Wrong state!";
        break;
    }
}


sensor_state::~sensor_state()
{
    delete ui;
}
