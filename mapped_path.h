/**
* @file mapped_path.h
* @brief Plik nagłówkowy dla mapped_path.cpp
*
* @author Michał Maćkowiak
*
*/


#ifndef MAPPED_PATH_H
#define MAPPED_PATH_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include<QtCharts>
#include<QChartView>
#include <QPixmap>
#include <QDebug>
#include <QColor>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLegendMarker>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QtMath>
#include <QPainter>
#include <QValueAxis>


namespace Ui {
class mapped_path;
}
/*! \file mapped_path.h
 */

/*!
 * \brief Klasa mapped_path
 */
class mapped_path : public QMainWindow
{
    Q_OBJECT //!< Główny obiekt klasy

public:
    /*! \brief Konstruktor klasy Mapped Path
    */
    explicit mapped_path(QWidget *parent = nullptr);

    ~mapped_path();

    QChartView *chartView; //!< Wskaźnik na obiekt do wyświetlania wykresu

    /** @brief Zmiana współrzędych w przestrzeni robota na współrzędne wprowadzonego punktu.
    *  Aktualizowanie wykresu pozycji.
    *  @param[in] position -- Punkt, którego współrzędne oznaczają pozycje robota.
    */
    void updatePosition(QPointF position);

private:
    Ui::mapped_path *ui; //!< Okno główne aplikacji.

    QPointF curr_position; //!< Aktualne współrzędne w przestrzeni wykresu

    QLineSeries *pathLine; //!< Wskaźnik na serie lini na wykresie

    QChart *chart; //!< Wskaźnik na obiekt wykresu

};

#endif // MAPPED_PATH_H
