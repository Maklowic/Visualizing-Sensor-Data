/**
* @file mainwindow.h
* @brief Plik nagłówkowy dla mainwindow.cpp
*
* @author Michał Maćkowiak
*
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtCharts>
#include <QtCharts/QChartView>
#include<QChartView>
#include<QBarSet>
#include<QBarSeries>
#include "mapped_path.h"
#include "wheel_speed1.h"
#include "connection.h"
#include "sensor_state.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*! \file mainwindow.h
 */

/*!
 * \brief Klasa MainWindow
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT //!< Główny obiekt klasy

public:
    /*! \brief Konstruktor klasy MainWindow
    */
    MainWindow(QWidget *parent = nullptr);

    /*!
     * \brief Rozbudowany konstruktor klasy MainWindow. Tworzy okno główne z uchwytami do wszystkich pozostałych klas.
     * \param[in] ws -- Ramie do obiektu klasy Wheel Speed.
     * \param[in] mp -- Ramie do obiektu klasy Mapped Path.
     * \param[in] ss -- Ramie do obiektu klasy Mapped Path.
     * \param[in] c -- Ramie do obiektu klasy Connection.
     */
    MainWindow(wheel_speed1 &ws, mapped_path &mp, sensor_state &ss, connection &c, QWidget *parent = nullptr);

    ~MainWindow();

    /*! \brief Tworzy pasek statusu.
    */
    void createStatusBar();

private slots:
    /*! \brief Slot przycisku "Wheel Speed".
     *  Otwiera okno klasy Wheel Speed.
    */
    void on_pushButton_OpenWS_clicked();

    /*! \brief Slot przycisku "Conection".
     *  Otwiera okno klasy Connection.
    */
    void on_pushButton_OpenC_clicked();

    /*! \brief Slot przycisku "Mapped Path".
     *  Otwiera okno klasy Mapped Path.
    */
    void on_pushButton_OpenMP_clicked();

    /*! \brief Slot przycisku "Sensor State".
     *  Otwiera okno klasy Sensor State.
    */
    void on_pushButton_OpenSS_clicked();

    /*! \brief Slot przycisku "Exit".
     *  Zamyka aplikację i wszystkie otwarte okna.
    */
    void on_pushButton_Exit_clicked();

private:
    mapped_path *Window_MP; //!< Okno klasy Mapped Path.

    connection *Window_C; //!< Okno klasy Connection.

    sensor_state *Window_SS; //!< Okno klasy Sensor State.

    wheel_speed1 *Window_WS; //!< Okno klasy Wheel Speed.

    Ui::MainWindow *ui; //!< Okno główne aplikacji.

};
#endif // MAINWINDOW_H
