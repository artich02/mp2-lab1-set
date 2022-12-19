// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)  // при выполнении работы использовались лекционные материалы //
{
    if (len <= 0)
        throw exception("Erorr");

    BitLen = len;
    MemLen = BitLen / (sizeof(TELEM) * 8);
    if (MemLen * sizeof(TELEM) * 8 < len)
        MemLen++;
    pMem = new TELEM[MemLen];
    memset(pMem,0, MemLen * sizeof(TELEM));
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (size_t i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField() //
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n //
{
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n 
{
    return 1 << (n & (sizeof(TELEM) * 8) - 1);
}


// доступ к битам битового поля------------------------------------------------------------------------------------


int TBitField::GetLength(void) const // получить длину (к-во битов) //
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит //
{
    if (n < 0 || n >= BitLen)
        throw exception("Erorr index");
    pMem[GetMemIndex(n)] |= GetMemMask(n);
 }

void TBitField::ClrBit(const int n) // очистить бит //
{
    if (n < 0 || n >= BitLen)
        throw exception("Erorr no index");
    pMem[GetMemIndex(n)] &= (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита ??
{
    if (n < 0 || n >= BitLen)
        throw exception("Erorr index");
    if (n < BitLen && n >= 0)
    {
        if (pMem[GetMemIndex(n)] & GetMemMask(n))
            return 1;
        return 0;
    }  
}

// битовые операции-------------------------------------------------------------------------------------------------

TBitField& TBitField::operator=(const TBitField &bf) // присваивание //
{
    BitLen = bf.BitLen;
    if (MemLen != bf.MemLen)
    { 
        delete[] pMem; 
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
    }
    for (size_t i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 0;
    
    for (size_t i = 0; i < bf.MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение //
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    //if (BitLen != bf.BitLen)
     //   throw exception("Erorr");
    if (BitLen < bf.BitLen)
        BitLen = bf.BitLen;
    
    TBitField tmp(BitLen);
    for (size_t i = 0; i < MemLen; i++)
        tmp.pMem[i] |= pMem[i];
    for (size_t i = 0; i < bf.MemLen; i++)
        tmp.pMem[i] |= bf.pMem[i];
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (BitLen < bf.BitLen)
        BitLen = bf.BitLen;
    
    TBitField tmp(BitLen);
    tmp = ~tmp;
    for (size_t i = 0; i < bf.MemLen; i++)
        tmp.pMem[i] &= bf.pMem[i];
    for (size_t i = 0; i < MemLen; i++)
        tmp.pMem[i] &= pMem[i];
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(BitLen);
    for (size_t i = 0; i < BitLen; i++)
        if (GetBit(i) != 1)
            tmp.SetBit(i);
        else
            tmp.ClrBit(i);
    return tmp;
}

// ввод/вывод-------------------------------------------------------------------------------------------------------

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int tmp;
    for (size_t i = 0; i < bf.GetLength(); i++)
    {
        istr >> tmp;
        if (tmp == 0)
            bf.ClrBit(i);
        else if (tmp == 1)
            bf.SetBit(i);
        else
            throw exception("Erorr");
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод 
{
     for (size_t i = 0; i < bf.GetLength(); i++)
        if (bf.GetBit(i))
            ostr << '1';
        else
            ostr << '0';
    return ostr;
}
