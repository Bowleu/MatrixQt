#include "rational.h"
#include <QDebug>

Rational::Rational(int num, int div)
{
    this->num = num;
    this->div = div;
    if (div == 0)
        div = 1;
    if (div < 0) {
        num *= -1;
        div *= -1;
    }
    cut();
}

Rational::Rational() {
    num = 0;
    div = 1;
}

Rational::Rational(QString s) {
    QString number = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != '/')
            number += s[i];
        else{
            num = number.toInt();
            number = "";
        }
    }
    if (number == s) {
        div = 1;
        num = number.toInt();
        return;
    } else {
        div = number.toInt();
    }
    if (div == 0)
        div = 1;
    if (div < 0) {
        div *= -1;
        num *= -1;
    }
    cut();
}

Rational::Rational(int n) {
    div = 1;
    num = n;
}

Rational Rational::operator +(Rational r) {
    Rational answer(num, div);
    int gcd;
    for (int i = r.div; i > 0; i--) {
        if (div % i == 0 and r.div % i == 0){
            gcd = i;
            break;
        }
    }
    answer.div = div * r.div / gcd;
    answer.num = num * (answer.div / div) + r.num * (answer.div / r.div);
    answer.cut();
    return answer;
}

Rational Rational::operator +(int n) {
    Rational answer(num + n * div, div);
    return answer;
}

Rational Rational::operator -(Rational r) {
    Rational answer(num, div);
    int gcd;
    for (int i = r.div; i > 0; i--) {
        if (div % i == 0 and r.div % i == 0){
            gcd = i;
            break;
        }
    }
    answer.div = div * r.div / gcd;
    answer.num = num * (answer.div / div) - r.num * (answer.div / r.div);
    answer.cut();
    return answer;
}

Rational Rational::operator -(int n) {
    Rational answer(num - n * div, div);
    return answer;
}

Rational Rational::operator *(Rational r) {
    Rational answer(num, div);
    answer.num *= r.num;
    answer.div *= r.div;
    answer.cut();
    return answer;
}
Rational Rational::operator *(int n) {
    Rational answer(num * n, div);
    answer.cut();
    return answer;
}

bool Rational::operator != (int n) {
    if (div == 1 and num == n)
        return 0;
    return 1;
}

bool Rational::operator != (Rational r) {
    if (div == r.div and num == r.num)
        return 0;
    return 1;
}

std::ostream& operator << (std::ostream &st, Rational r) {
    if (r.div == 1)
        st << r.num;
    else
        st << r.num << '/' << r.div;
    return st;
}

void Rational::cut() {
    int gcd;
    for (int i = div; i > 0; i--) {
        if (div % i == 0 and num % i == 0){
            gcd = i;
            break;
        }
    }
    num /= gcd;
    div /= gcd;
}

QString Rational::toQString() {
    QString s = "";
    if (div != 1)
        s += QString::number(num) + '/' + QString::number(div);
    else
        s += QString::number(num);
    return s;
}
