/**
* @file sensor_state.h
* @brief Plik nagłówkowy dla sensor_state.cpp
*
* @author Michał Maćkowiak
*
*/

#ifndef SENSOR_STATE_H
#define SENSOR_STATE_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "QDebug"
#include <QLabel>


namespace Ui {
class sensor_state;
}
/*! \file sensor_state.h
 */

/*!
 * \brief Klasa sensor_state
 */
class sensor_state : public QMainWindow
{
    Q_OBJECT //!< Główny obiekt klasy

public:
    /*! \brief Konstruktor klasy Sensor State
    */
    explicit sensor_state(QWidget *parent = nullptr);

    ~sensor_state();

    /** @brief Zmiana stanu wybranego czujnika na zadany stan.
    *  @param[in] witch -- Numer odpowiadający numerowi czujnika.
    *  Możliwe wartości to liczby od 1 do 5.
    *  @param[in] state -- Stan czujnika.
    *  Warianty:
    *   - 0 -- stan niski czujnika oznacza brak wykrycia,
    *   - 1 -- stan wysoki czujnika oznacza wykrywanie.
    */
    void updateSensor(int witch, int state);

    /** @brief Funkcja pomocnicza do zmiany stanu czujnika @see updateSensor.
    *  Wywoływana jest w switchu by kod był bardziej czytely.
    *  @param[in] witch -- Numer odpowiadający numerowi czujnika.
    *  Możliwe wartości to liczby od 1 do 5.
    *  Parametr ten jest już przefiltrowany przez funkcję nadrzędną.
    *  @param[in] state -- Stan czujnika.
    *  Warianty:
    *   - 0 -- stan niski czujnika oznacza brak wykrycia,
    *   - 1 -- stan wysoki czujnika oznacza wykrywanie.
    */
    void updateState(int witch, int state);

private:
    Ui::sensor_state *ui; //!< Okno główne aplikacji.

    QPixmap imgSensorPlat; //!< Obraz reprezentujący wyspę czujników
    QPixmap imgActiveSens; //!< Obraz czerwoengo kwadratu reprezetujązego aktywny czujnik

    QLabel *sensorsLabel[5]; //!< Tablica do przechowywania uchwytów do wskaźników na etykiety
};

#endif // SENSOR_STATE_H
