#include "wheel_speed1.h"
#include "ui_wheel_speed1.h"



wheel_speed1::wheel_speed1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wheel_speed1)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");


    //![1] Wczytanie obrazów oraz ich przypisanie do zdefiniowanych "label"
    // Wczytanie obrazów
    imgWheel.load("D:/qt_workspace/MILF_sensors_visualization/kolo.png");
    imgArrowRight.load("D:/qt_workspace/MILF_sensors_visualization/arrR.png");
    imgArrowLeft.load("D:/qt_workspace/MILF_sensors_visualization/arrL.png");
    // Pobranie rozmiaru etykiety
    int w = ui->label_pic_WR->width();
    int h = ui->label_pic_WR->height();
    // Przypisanie obrazów do etykiet
    ui->label_pic_WR->setPixmap(imgWheel.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_pic_WL->setPixmap(imgWheel.scaled(w,h,Qt::KeepAspectRatio));

    w = ui->label_pic_arr1_R->width();
    h = ui->label_pic_arr1_R->height();
    ui->label_pic_arr1_R->setPixmap(imgArrowRight.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_pic_arr1_R->hide();

    ui->label_pic_arr1_L->setPixmap(imgArrowLeft.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_pic_arr1_L->hide();

    ui->label_pic_arr2_R->setPixmap(imgArrowRight.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_pic_arr2_R->hide();

    ui->label_pic_arr2_L->setPixmap(imgArrowLeft.scaled(w,h,Qt::KeepAspectRatio));
    ui->label_pic_arr2_L->hide();

    //![2] Ustawienie animacji
    animation_R = new QVariantAnimation;
    animation_R->setDuration(1000000000);
    animation_R->setStartValue(0.0f);


    animation_L = new QVariantAnimation;
    animation_L->setDuration(1000000000);
    animation_L->setStartValue(0.0f);

    //![3] Deklarowanie słupków oraz ich wartości, ustawienie parametrów
    setL = new QBarSet("Left");
    setR = new QBarSet("Right");

    setR->setColor(QColor(114, 95, 227, 150));
    setR->setColor(QColor(252, 95, 153, 150));

    setL->append(123);
    setL->replace(0, curr_speed_L);
    setR->append(123);
    setR->replace(0, curr_speed_R);

    //![4] Dodanie słupków do serii
    series = new QBarSeries();
    series->append(setL);
    series->append(setR);

    //![5] Zdefiniowanie wykresu oraz dodanie do niego serii, zmiany parametrów
    chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Customize chart title
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setTitle("Wheels speed");

    // Customize chart background
    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0, 0));
    backgroundGradient.setFinalStop(QPointF(0, 1));
    backgroundGradient.setColorAt(0.0, QRgb(0x797979));
    backgroundGradient.setColorAt(1.0, QRgb(0x494949));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setBackgroundBrush(backgroundGradient);

    QLinearGradient plotAreaGradient;
    plotAreaGradient.setStart(QPointF(0, 1));
    plotAreaGradient.setFinalStop(QPointF(1, 0));
    plotAreaGradient.setColorAt(0.0, QRgb(0x0d5ca6));
    plotAreaGradient.setColorAt(1.0, QRgb(0x2198c0));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setPlotAreaBackgroundBrush(plotAreaGradient);
    chart->setPlotAreaBackgroundVisible(true);



    //![6] Ustalenie parametrów osi X oraz osi Y wykresu
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

    // Customize axis label font
    QFont labelsFont;
    labelsFont.setPixelSize(12);
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);

    // Customize axis label colors
    QBrush axisBrush(Qt::white);
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    //![7] Wyświetlanie legendy
    chart->legend()->setVisible(true);
    chart->legend()->setBrush(axisBrush);
    chart->legend()->setLabelBrush(axisBrush);
    chart->legend()->setAlignment(Qt::AlignBottom);

    //![8] Wyświetlenie wykresu
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(350, 600);
    chartView->setParent(ui->frame);

    //![9] Wyświetlanie wartości prędkości
    ui->num_speedR->display(curr_speed_R);
    ui->num_speedL->display(curr_speed_L);
}

wheel_speed1::~wheel_speed1()
{
    delete ui;
}

void wheel_speed1::updateSpeed(int wheel, int value){

    if(value < -150) {
        qDebug() << "udateSpeed ERROR: Value too low!";
    }
    else if (value > 150){
        qDebug() << "udateSpeed ERROR: Value too high!";
    }
    else {
        switch (wheel) {
        // prawe kolo
        case 0:
            curr_speed_R = value;

            setR->replace(0, curr_speed_R);

            ui->num_speedR->display(curr_speed_R);

            if (value == 0) {
                ui->label_pic_arr2_R->hide();
                ui->label_pic_arr2_L->hide();

            }
            else if(value > 0){
                ui->label_pic_arr2_R->show();
                ui->label_pic_arr2_L->hide();
            }
            else {
                ui->label_pic_arr2_R->hide();
                ui->label_pic_arr2_L->show();
            }
            break;
        // lewe kolo
        case 1:
            curr_speed_L = value;

            setL->replace(0, curr_speed_L);

            ui->num_speedL->display(curr_speed_L);

            if (value == 0) {
                ui->label_pic_arr1_R->hide();
                ui->label_pic_arr1_L->hide();
            }
            else if(value > 0){
                ui->label_pic_arr1_R->show();
                ui->label_pic_arr1_L->hide();
            }
            else {
                ui->label_pic_arr1_R->hide();
                ui->label_pic_arr1_L->show();
            }
            break;

        default:
            qDebug() << "updateSpeed ERROR: Wrong wheel value!";
            break;
        }
        speedDisp();
        spinWheel(wheel);
    }
}

void wheel_speed1::speedDisp()
{
    chartView->update();
    chartView->repaint();
}

void wheel_speed1::spinWheel(int which){
    switch (which) {
    // koło prawe
    case 0:
        animation_R->setEndValue(360.0f*curr_speed_R*animation_R->duration()/60000);
        connect(animation_R, &QVariantAnimation::valueChanged, [=](const QVariant &value){
//                    qDebug()<<value;
                    QTransform t;
                    t.translate(imgWheel.width()/2, imgWheel.height()/2);
                    t.rotate(value.toReal());
                    t.translate(imgWheel.width()/2, imgWheel.height()/2);
                    ui->label_pic_WR->setPixmap(imgWheel.transformed(t));
                });
        animation_R->start();
        break;
    // koło lewe
    case 1:
        animation_L->setEndValue(360.0f*curr_speed_L*animation_L->duration()/60000);
        connect(animation_L, &QVariantAnimation::valueChanged, [=](const QVariant &value){
//                    qDebug()<<imgWheel.width();
                    QTransform t;
                    t.translate(imgWheel.width()/2, imgWheel.height()/2);
                    t.rotate(value.toReal());
                    t.translate(-imgWheel.width()/2, -imgWheel.height()/2);
                    ui->label_pic_WL->setPixmap(imgWheel.transformed(t));
                });
        animation_L->start();
        break;
    default:
        break;
    }
}
