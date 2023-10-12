#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <cmath>

#include "number.h"

using namespace std;

class Matrix
{
    Number* values;
    int quantity;
    int a;
    Matrix* algComp(int row, int column, int a);
    int borderingMinorsMaxRank(Matrix m, int row, int column, int size);
public:
    Number determinant(Matrix m);
    Matrix();
    Matrix(int a);
    Matrix(Matrix* m);
    Matrix(const Matrix &m);
    Number determinant();
    Matrix transponate();
    int rank();
    friend ostream& operator << (ostream &st, Matrix m);
    Number &operator [](int index);
    ~Matrix();
    
};

#endif // MATRIX_H

