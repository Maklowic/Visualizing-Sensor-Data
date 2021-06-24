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
#include "QDebug"
#include <QList>
#include <QSerialPortInfo>
#include <QDateTime>
#include "CRC8.h"
#include "mapped_path.h"
#include "wheel_speed1.h"
#include "sensor_state.h"


namespace Ui {
class connection;
}

/*! \file connection.h
 */

/*!
 * \brief Klasa connection
 */

class connection : public QMainWindow
{
    Q_OBJECT  //!< Główny obiekt klasy

public:
    /*! \brief Konstruktor klasy Connection
    */
    connection(QWidget *parent = nullptr);

    /*!
     * \brief Rozbudowany konstruktor klasy Connection.
     * \param[in] ws -- Ramie do obiektu klasy Wheel Speed.
     * \param[in] mp -- Ramie do obiektu klasy Mapped Path.
     * \param[in] ss -- Ramie do obiektu klasy Mapped Path.
     */
    connection(wheel_speed1 &ws, mapped_path &mp, sensor_state &ss, QWidget *parent = nullptr);

    ~connection();


    /*! \brief Zarządza danymi wpływającymi przez otwarty port za pomocą ramek danych.
     *  \param[in] co -- bit ramki danych odpowiadający urządzeniu, na mikrokontrolerze, które wysyła dane.
     *  Możliwe warianty to:
     *     - 1 -- enkoder do wysyłania szybkości kół,
     *     - 2 -- enkoder do wysyłania położenia robota,
     *     - 3 -- sensory do wysyłania stanu czujników.
     *  \param[in] ktory -- bit ramki odpowiadający numerowi krotności urządzenia.
     *  np.
     *     - 1 -- enkoder prawego koła,
     *     - 2 -- enkoder lewego koła.
     *  \param[in] dane -- bit/bity ramki odpowiadające przesłanym informacją z konkretnego urządzenia.
    */
    void manageData(int co, int ktory, int dane);

    /*! \brief Sprawdza aktualny stan połączenia.
     *  Zwraca 1 jeżeli jest połączenie z urządzeniem komunikacyjnym.
     *  W przeciwnym razie zwraca 0.
    */
    bool connStatus();

private slots:

    /*! \brief Slot dla przycisku "Search".
    *  Wyszukuje dostępne porty COM.
    */
    void on_pushButtonSearch_clicked();

    /*! \brief Slot dla przycisku "Connect".
    *  Podłącza się do wybranego portu pokazanego w liście comboBox obok.
    */
    void on_pushButtonConnect_clicked();

    /*! \brief Slot dla przycisku "Disconnect".
    *  Zamyka połączenie z otwartym portem.
    */
    void on_pushButtonCloseConnection_clicked();

    /*! \brief Odczytuje dane przychodzące z mikrokontrolera poprzez komunikację UART.
    */
    void readFromPort();



private:
    Ui::connection *ui;  //!< Okno główne aplikacji.

    /** @brief Funkcja wysyła wiadomość do okna z logami.
    *  @param[in] message -- Wiadomość do wysłania.
    */
    void addToLogs(QString message);

    /** @brief Funkcja wysyła wiadomość do okna z wiadomościami.
    *  @param[in] message -- Wiadomość do wysłania.
    */
    void addToInfo(QString message);

    QSerialPort *device; //!< Urządzenie, z którym odbywa się komunikacja poprzez otwarty port COM.

    wheel_speed1 *WheelSpeed; //!< Ramie do obiektu Wheel Speed
    mapped_path *MappedPath; //!< Ramie do obiektu Mapped Path
    sensor_state *SensorState; //!< Ramie do obiektu Sensor State
};

#endif // CONNECTION_H
