#include "mapped_path.h"
#include "ui_mapped_path.h"


mapped_path::mapped_path(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mapped_path)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: darkgray;");
    //![1] Tworzenie serii wykresu
    pathLine = new QLineSeries();
    pathLine->setName("Path");
    // zmiana koloru i grubości
    QPen pen = pathLine->pen();
    pen.setWidth(5);
    pen.setColor("red");
    pathLine->setPen(pen);

    // tymczasowa seria by urtworzyć od razu rozmiary pola wykresu
    QLineSeries *setchart = new QLineSeries();
    setchart->setName("tets");

    //![2] dodanie punktów do serii i aktualnej pozycji
    QPointF point(125.0, 125.0);
    curr_position = point;

    pathLine->append(curr_position);

    *setchart << QPointF(250,250) << QPointF(0,0) << QPointF(0,250)<<QPointF(250,0);

    //![3] dodawanie serii do wykresu
    chart = new QChart();
    chart->addSeries(pathLine);
    chart->addSeries(setchart);
    chart->createDefaultAxes();
    chart->setDropShadowEnabled(false);
    // Customize chart title
    QFont font;
    font.setPixelSize(20);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setTitle("Mapped Path");

    //![4] legenda
    chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);


    //![5] kolor wykresu

    // Customize chart background
    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0, 0));
    backgroundGradient.setFinalStop(QPointF(0, 1));
    backgroundGradient.setColorAt(0.0, QRgb(0xa7a7a7));
    backgroundGradient.setColorAt(1.0, QRgb(0x8a8a8a));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setBackgroundBrush(backgroundGradient);

    // Customize plot area background
    QLinearGradient plotAreaGradient;
    plotAreaGradient.setStart(QPointF(0, 1));
    plotAreaGradient.setFinalStop(QPointF(1, 0));
    plotAreaGradient.setColorAt(0.0, QRgb(0x0d5ca6));
    plotAreaGradient.setColorAt(1.0, QRgb(0x2198c0));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setPlotAreaBackgroundBrush(plotAreaGradient);
    chart->setPlotAreaBackgroundVisible(true);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);

    QValueAxis *axisX = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);

    // Customize axis label font
    QFont labelsFont;
    labelsFont.setPixelSize(12);
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);

    // Customize axis label colors
    QBrush axisBrush(Qt::white);
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    //![6] Wyświetlenie wykresu
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(400, 300);
    // usunięcie tymczasowej serii
    chart->removeSeries(setchart);
}

mapped_path::~mapped_path()
{
    delete ui;
}

void mapped_path::updatePosition(QPointF position){
    curr_position = position;
    pathLine->append(curr_position);
}

