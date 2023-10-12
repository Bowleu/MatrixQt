#include "matrix.h"
#include "number.h"

using namespace std;

Matrix::Matrix() {
    a = 2;
    quantity = 4;
    values = new Number[a * a]{ 1, 2, 3, 4 };
}
Matrix::Matrix(int a)
{
    this->a = a;
    values = new Number[a * a];
    quantity = a * a;
}
Matrix::~Matrix() {
    delete[] values;
}

Matrix::Matrix(const Matrix &m) {
    a = m.a;
    quantity = m.quantity;
    values = new Number[a * a];
    for (int i = 0; i < quantity; i++) {
        values[i] = m.values[i];
    }
}

Matrix::Matrix(Matrix *m) {
    a = m->a;
    quantity = m->quantity;
    values = new Number[a * a];
    for (int i = 0; i < quantity; i++) {
        values[i] = m->values[i];
    }
}

Matrix* Matrix::algComp(int row, int column, int a) {
    Matrix* newMatrix = new Matrix(a - 1);
    int k = 0;
    for (int i = 0; i < quantity; i++) {
        if (i / a != row) {
            if (i % a != column) {
                (*newMatrix)[k] = (*this)[i];
                k++;
            }
        }
    }
    return newMatrix;
}

Number Matrix::determinant(Matrix m) {
    if (m.a == 1) {
        return m[0];
    }
    if (m.a == 2) {
        Number determinant = m[0] * m[3] - m[1] * m[2];
        return determinant;
    }
    Number determinant = 0;
    Matrix* algComp = nullptr;
    for (int i = 0; i < a; i++) {
        if (m.values[i] != 0) {
            algComp = m.algComp(0, i, m.a);
            Number algCompDet = algComp->determinant();
            delete algComp;
            determinant = determinant + m.values[i] * pow(-1, i) * algCompDet;
        }
    }
    return determinant;
}

Number Matrix::determinant() {
    return determinant(*this);
}

Matrix Matrix::transponate() {
    Matrix transponatedMatrix(a);
    for (int i = 0; i < quantity; i++) {
        int row = i / a;
        int column = i % a;
        transponatedMatrix[column * a + row] = values[i];
    }
    return transponatedMatrix;
}

Number& Matrix::operator[](int i){
    return values[i];
}

ostream& operator << (ostream &st, Matrix m) {
    for (int i = 0; i < m.quantity; i++) {
        st << m[i] << ' ';
        if ((i + 1) % m.a == 0)
            st << '\n';
    }
    return st;
}

int Matrix::borderingMinorsMaxRank(Matrix m, int row, int column, int size) {
    int rang = 1;
    Matrix currMinor(size);
    int k = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            currMinor[k] = m[(row + i) * m.a + column + j];
            k++;
        }
    }
    if (currMinor.determinant() != 0) {
        rang = size;
    }
    if (row > 0 and column + size < m.a) {
        rang = max(borderingMinorsMaxRank(m, row - 1, column, size + 1), rang);
        if (rang == m.a) {
            return rang;
        }
    }
    if (row + size < m.a and column + size < m.a) {
        rang = max(borderingMinorsMaxRank(m, row, column, size + 1), rang);
        if (rang == m.a) {
            return rang;
        }
    }
    if (row + size < m.a and column > 0) {
        rang = max(borderingMinorsMaxRank(m, row, column - 1, size + 1), rang);
        if (rang == m.a) {
            return rang;
        }
    }
    if (row > 0 and column > 0) {
        rang = max(borderingMinorsMaxRank(m, row - 1, column - 1, size + 1), rang);
        if (rang == m.a) {
            return rang;
        }
    }
    return rang;
}

int Matrix::rank() {
    int rang = 0;
    for (int i = 0; i < quantity; i++) {
        if (values[i] != 0) {
            rang = borderingMinorsMaxRank(*this, i / a, i % a, 1);
            if (rang == a)
                return rang;
        }
    }
    return rang;
}
