#ifndef SENSOR_STATE_H
#define SENSOR_STATE_H

#include <QMainWindow>

namespace Ui {
class sensor_state;
}

class sensor_state : public QMainWindow
{
    Q_OBJECT

public:
    explicit sensor_state(QWidget *parent = nullptr);
    ~sensor_state();

private:
    Ui::sensor_state *ui;
};

#endif // SENSOR_STATE_H
