/**
* @file wheelspeed1.h
* @brief Plik nagłówkowy dla wheelspeed1.cpp
*
* @author Michał Maćkowiak
*
*/

#ifndef WHEEL_SPEED1_H
#define WHEEL_SPEED1_H

#include <QMainWindow>
#include <QVariantAnimation>
#include<QtCharts>
#include<QChartView>
#include<QBarSet>
#include<QBarSeries>
#include <QPixmap>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QDebug>
#include <QColor>


namespace Ui {
class wheel_speed1;
}
/*! \file wheel_speed1.h
 */

/*!
 * \brief Klasa wheel_speed1
 */
class wheel_speed1 : public QMainWindow
{
    Q_OBJECT //!< Główny obiekt klasy

public:
    /*! \brief Konstruktor klasy Wheel Speed
    */
    explicit wheel_speed1(QWidget *parent = nullptr);

    ~wheel_speed1();

    /** @brief Zmiana wartości prędkości wybranego koła na zadaną wartość. Aktualizowanie wykresu.
    *  @param[in] wheel -- Koło, któremu zmieniona będzie wartość.
    *  Warianty:
    *   - 0 -- koło prawe,
    *   - 1 -- koło lewe.
    *  @param[in] speed -- Wartość prędkości.
    */
    void updateSpeed(int wheel, int speed);

    /** @brief Zaktualizowanie wyświetlonego wykresu słupkowego.
    */
    void speedDisp();

    /** @brief Obrót obrazu koła w oknie aplikacji, szybkość obrotu zależy od aktualnej prędkości.
    *  @param[in] which -- Koło, które będzie się obracać
    *  Warianty:
    *   - 0 -- koło prawe,
    *   - 1 -- koło lewe.
    */
    void spinWheel(int which);

private:
    Ui::wheel_speed1 *ui; //!< Okno główne aplikacji.

    QPixmap imgWheel; //!< Obraz koła
    QPixmap imgArrowRight;//!< Obraz strzałki w prawo
    QPixmap imgArrowLeft;//!< Obraz strzałki w lewo

    QVariantAnimation  *animation_R; //!< animacja koła prawego
    QVariantAnimation  *animation_L; //!< animacja koła lewego

    int curr_speed_L = 0; //!< Wartość szybkości lewego koła
    int curr_speed_R = 0; //!< Wartość szybkości prawego koła

    QBarSet *setL; //!< Wskaźnik na słupek reprezentujący prędkość lewego koła
    QBarSet *setR; //!< Wskaźnik na słupek reprezentujący prędkość prawego koła
    QBarSeries *series; //!< Wskaźnik na serie słupków na wykresie

    QChartView *chartView; //!< Wskaźnik na obiekt do wyświetlania wykresu
    QChart *chart; //!< Wskaźnik na obiekt wykresu
};

#endif // WHEEL_SPEED1_H
