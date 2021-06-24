#include "CRC8.h"

unsigned int CRC8_SingleByte(unsigned int Data2)
{
    unsigned int Poly = (POLYNOMIAL_9 << 7);
    for (byte Idx = 0; Idx < 8; ++Idx)
    {
        if ((Data2 & 0x8000) != 0)
            Data2 ^= Poly;
        Data2 <<= 1;
    }
    return Data2;
}

byte CRC8_DataArray(const byte *pDataFrame, byte Len)
{
    unsigned int Data2 = pDataFrame[0] << 8;

    for (unsigned int Idx = 1; Idx < Len; ++Idx)
    {
        Data2 |= pDataFrame[Idx];
        Data2 = CRC8_SingleByte(Data2);
    }
    Data2 = CRC8_SingleByte(Data2);

    return static_cast<byte>(Data2 >> 8);
}

bool ParseDataFrame(const char *pDataFrame, int &co, int &ktory, int &dane)
{
    std::istringstream IStrm(pDataFrame);
    char FHeader;
    unsigned int CRC8;

    IStrm >> FHeader >> co >> ktory >> dane >> hex >> CRC8;
    if (IStrm.fail() || FHeader != 'X')
        return false;

    return static_cast<byte>(CRC8) == CRC8_DataArray(reinterpret_cast<const byte *>(pDataFrame), strlen(pDataFrame) - 3);
}
