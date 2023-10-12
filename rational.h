#ifndef RATIONAL_H
#define RATIONAL_H
#include <QString>
#include <iostream>

class Rational
{
    int div;
    int num;
    void cut();
public:
    Rational(int num, int div);
    Rational(QString s);
    Rational (int n);
    Rational ();
    Rational operator *(Rational r);
    Rational operator *(int n);
    Rational operator +(Rational r);
    Rational operator +(int n);
    Rational operator -(Rational r);
    Rational operator -(int n);
    bool operator != (int n);
    bool operator != (Rational r);
    friend std::ostream& operator << (std::ostream &st, Rational r);
    QString toQString();

};

#endif // RATIONAL_H
