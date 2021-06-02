#include "sensor_state.h"
#include "ui_sensor_state.h"

sensor_state::sensor_state(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sensor_state)
{
    ui->setupUi(this);
}

sensor_state::~sensor_state()
{
    delete ui;
}
