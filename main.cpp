#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow window;
    window.setWindowTitle("MILF - sensors visualization"); // Ustawia tytuł głównego okna
    window.update();
    window.show();

    return a.exec();
}
