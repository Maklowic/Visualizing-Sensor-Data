/**
* @file connection.h
* @brief Plik nagłówkowy dla connection.cpp
*
* @author Michał Maćkowiak
*
*/

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class connection;
}

/*! \file connection.h
 */

/*!
 * \brief The Connection class
 */

class connection : public QMainWindow
{
    Q_OBJECT  //<! Main class object.

public:
    /*! \brief Connection window class constructor
    */
    explicit connection(QWidget *parent = nullptr);
    ~connection();

private slots:

    /*! \brief Slot of "Search" button.
    *  Searches for available COM ports.
    */
    void on_pushButtonSearch_clicked();

    /*! \brief Slot of "Connect" button.
    *  Connects with the port being displayed in the comboBox nearby.
    */
    void on_pushButtonConnect_clicked();

    /*! \brief Slot of "Disconnect" button.
    *  Closes connection with robot.
    */
    void on_pushButtonCloseConnection_clicked();

    /*! \brief Reads send data from robot.
    */
    void readFromPort();

private:
    Ui::connection *ui;  //!< Application main window.

    /** @brief Sends info to logs.
    *  @param[in] message Message to be sent.
    */
    void addToLogs(QString message);
    /** @brief Sends info to information.
    *  @param[in] message Message to be sent.
    */
    void addToInfo(QString message);

    QSerialPort *device; //!< The device with which the communication is set.

    /** @brief Sends message to robot.
    *  @param[in] message Message to be sent.
    */
    void sendMessageToDevice(QString message);
};

#endif // CONNECTION_H
