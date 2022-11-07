// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp),MaxPower(mp)  // при выполнении работы использовались лекционные материалы
{
}

// конструктор копирования //
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа //
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
    TBitField tmp(BitField);
    return  tmp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов //
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества? //
{
    if (Elem >= MaxPower)
        throw exception("Erorr");
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества 
{
    if (Elem >= MaxPower)
        throw exception("Erorr");
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества 
{
    if (Elem >= MaxPower)
        throw exception("Erorr");
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции-----------------------------------------------------------------------------------

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (*this == s)     
        return *this;  
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение //
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение.
{
    TSet tmp(BitField | s.BitField);
    return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом.
{
    TSet tmp(BitField);
    tmp.InsElem(Elem);
    return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом.
{
    TSet tmp(BitField);
    tmp.DelElem(Elem);
    return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet tmp(BitField & s.BitField);
    return tmp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet tmp(*this);
    tmp.BitField=~BitField;
    return tmp;
}

// перегрузка ввода/вывода--------------------------------------------------------------------------------------------

istream &operator>>(istream &istr, TSet &s) // ввод
{
    for (size_t i = 0; i < s.MaxPower; i++)
    {
        istr >> s.BitField;
        s.IsMember(i);
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    size_t i, n;
    char ch = '{';
    n = s.GetMaxPower();
    for (i = 0; i < n; i++)
    {
        if (s.IsMember(i))
        {
            ostr << ch << ' ' << i;
            ch = ',';
        }
    }
    ostr << " }";
    return ostr;
}
