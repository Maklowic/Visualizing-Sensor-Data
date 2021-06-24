/**
* @file CRC8.h
* @brief Plik nagłówkowy dla CRC8.cpp
*
* @author Michał Maćkowiak
*
*/

#ifndef OSOS_CRC8_H
#define OSOS_CRC8_H

#include <iostream>
#include <cstring>
#include <string>
#include "QtDebug"
#include <cassert>
#include <iomanip>
#include <bitset>
#include <sstream>
using namespace std;

/*! @brief Definicja typu byte
 */
typedef unsigned char byte;
#define POLYNOMIAL_9 0x161  //!< Polynomial do obliczania CRC8.

/*! @brief Operacja bitowa XOR.
 * @param[in] Data2 -- Wartość do zmienienia przy pomocy XOR.
 * @see CRC8_DataArray()
 * @see ParseDataFrame()
 * @return Zwraca częściowy CRC8.
 */
unsigned int CRC8_SingleByte(unsigned int Data2);

/*! @brief Zwraca CRC8 dla danych wartości.
 * @param[in] pDataFrame -- Wartość, dla której CRC8 jest obliczana.
 * @param[in] Len -- Liczba znaków, dla której ma być policzone CRC8.
 * @see CRC8_SingleByte()
 * @see ParseDataFrame()
 * @return Zwraca CRC8.
 */
byte CRC8_DataArray(const byte *pDataFrame, byte Len);

/*! @brief Parsuje ramke danych wysłaną z robota.
 * @param[in] pDataFrame -- Ramka danych, która ma zostać sprasowana, bez <c>"\r\n"</c> na końcu.
 * \param[out] co -- bit ramki danych odpowiadający urządzeniu, na mikrokontrolerze, które wysyła dane.
 * Możliwe warianty to:
 *    - 1 -- enkoder do wysyłania szybkości kół,
 *    - 2 -- enkoder do wysyłania położenia robota,
 *    - 3 -- sensory do wysyłania stanu czujników.
 * \param[out] ktory -- bit ramki odpowiadający numerowi krotności urządzenia.
 * np.
 *    - 1 -- enkoder prawego koła,
 *    - 2 -- enkoder lewego koła.
 * \param[out] dane -- bit/bity ramki odpowiadające przesłanym informacją z konkretnego urządzenia.
 * @see CRC8_DataArray()
 * @see ParseDataFrame()
 * @return Zwraca <c>True</c> jeżeli obliczona i przesłana wartość CRC8 się taka sama.
 */
bool ParseDataFrame(const char *pDataFrame, int &co, int &ktory, int &dane);

#endif
