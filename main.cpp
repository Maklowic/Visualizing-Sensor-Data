#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    wheel_speed1 cos;

    cos.update_speed(0, -80);
    cos.update_speed(1, 20);
    w.update();
    printf("%d    %d\n", cos.curr_speed_L, cos.curr_speed_R);


    return a.exec();
}
