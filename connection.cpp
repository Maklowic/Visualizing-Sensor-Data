#include "connection.h"
#include "ui_connection.h"

connection::connection(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::connection)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: darkgray;");
    this->device = new QSerialPort;
}

connection::connection(wheel_speed1 &ws, mapped_path &mp, sensor_state &ss, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::connection)
{
    // przechwytujemy ramiona z konstruktora
    WheelSpeed = &ws;
    MappedPath = &mp;
    SensorState = &ss;

    ui->setupUi(this);
    this->setStyleSheet("background-color: darkgray;");
    this->device = new QSerialPort;
}

connection::~connection()
{
    delete ui;
}

void connection::on_pushButtonSearch_clicked() {
  this->addToLogs("Szukam urządzeń...");
  QList<QSerialPortInfo> devices;
  devices = QSerialPortInfo::availablePorts();

  for(int i = 0; i < devices.count(); i++) {
    this->addToLogs("Znalazłem urządzenie: " + devices.at(i).portName() + " " + devices.at(i).description());
    ui->comboBoxDevices->addItem(devices.at(i).portName() + "\t" + devices.at(i).description());
  }
}

void connection::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textEditLogs->append(currentDateTime + "\t" + message);
}

void connection::addToInfo(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");//
    ui->textEditInfo->append(currentDateTime + "\t" + message);
}

void connection::on_pushButtonConnect_clicked()
{

    if(ui->comboBoxDevices->count() == 0) {
      this->addToLogs("Nie wykryto żadnych urządzeń!");
      return;
    }

    QString portName = ui->comboBoxDevices->currentText().split("\t").first();
    this->device->setPortName(portName);

    // OTWÓRZ I SKONFIGURUJ PORT:
    if(!device->isOpen()) {
        if(device->open(QSerialPort::ReadWrite)) {
          this->device->setBaudRate(QSerialPort::Baud115200);
          this->device->setDataBits(QSerialPort::Data8);
          this->device->setParity(QSerialPort::NoParity);
          this->device->setStopBits(QSerialPort::OneStop);
          this->device->setFlowControl(QSerialPort::NoFlowControl);

          this->addToLogs("Otwarto port szeregowy.");
          connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));
        } else {
          this->addToLogs("Otwarcie porty szeregowego się nie powiodło!");
        }
    } else {
      this->addToLogs("Port już jest otwarty!");
      return;
    }
}

void connection::on_pushButtonCloseConnection_clicked()
{
    if(this->device->isOpen()) {
      this->device->close();
      this->addToLogs("Zamknięto połączenie.");
    } else {
      this->addToLogs("Port nie jest otwarty!");
      return;
    }
}

// Reading from open port.
void connection::readFromPort() {
  while(this->device->canReadLine()) {
    QString msg = this->device->readAll();

    int pos = msg.lastIndexOf("\r\n"); // returns \r\n position in string index
    msg = msg.left(pos); // cuts all signs starting with \r\n

    int co, ktory, dane;

    if(ParseDataFrame(msg.toLocal8Bit().data(), co, ktory, dane))
    {
        this->addToLogs("Data frame |" + msg + "| parsing successful");
        this->addToInfo("Urządzenie: " + QString::number(co) + " numer: " + QString::number(ktory) + " dane: " + QString::number(dane));

//      view->updateScreen(sensor, status);
//        SensorState->updateSensor(ktory, dane);
        manageData(co, ktory, dane);

    }
    else
    {
        this->addToLogs("DATA FRAME |" + msg + "| PARSING FAILED");
    }
  }
}

void connection::manageData(int co, int ktory, int dane){

    QPointF nowe(ktory, dane);
    switch (co) {
    // enkoder szybkość
    case 1:
        WheelSpeed->updateSpeed(ktory, dane);
        break;
    // enkoder położenie
    case 2:
        MappedPath->updatePosition(nowe);
        break;
    // sensor
    case 3:
        SensorState->updateSensor(ktory,dane);
        break;
    default:
         qDebug() << "manageData ERROR: Wrong input!";
        break;
    }
}

bool connection::connStatus(){
    return this->device->isOpen();
}
