#include "mapped_path.h"
#include "ui_mapped_path.h"

mapped_path::mapped_path(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mapped_path)
{
    ui->setupUi(this);
}

mapped_path::~mapped_path()
{
    delete ui;
}
