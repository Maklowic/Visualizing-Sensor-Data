#ifndef MAPPED_PATH_H
#define MAPPED_PATH_H

#include <QMainWindow>

namespace Ui {
class mapped_path;
}

class mapped_path : public QMainWindow
{
    Q_OBJECT

public:
    explicit mapped_path(QWidget *parent = nullptr);
    ~mapped_path();

private:
    Ui::mapped_path *ui;
};

#endif // MAPPED_PATH_H
