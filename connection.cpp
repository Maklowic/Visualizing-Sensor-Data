#include "connection.h"
#include "ui_connection.h"

#include <QDebug>
#include <QList>
#include <QSerialPortInfo>
#include <QDateTime>

connection::connection(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::connection)
{
    ui->setupUi(this);
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

void connection::readFromPort() {
  while(this->device->canReadLine()) {
    QString line = this->device->readLine();
    //qDebug() << line;

    QString terminator = "\r";
    int pos = line.lastIndexOf(terminator);
    //qDebug() << line.left(pos);
    this->addToInfo(line.left(pos));
    if(line.at(0) == "X"){
        QString cos = line.at(2);
        QString cos4 = line.at(4);
        QString cos6 = line.at(6);
        this->addToInfo("Typ: " + cos+", Sensor: " + cos4 + ", Wartosc: " + cos6);
    }
  }
}

void connection::sendMessageToDevice(QString message) {
  if(this->device->isOpen() && this->device->isWritable()) {
    this->addToLogs("Wysyłam informacje do urządzenia " + message);
    this->device->write(message.toStdString().c_str());
  } else {
    this->addToLogs("Nie mogę wysłać wiadomości. Port nie jest otwarty!");
  }
}
