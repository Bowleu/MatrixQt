#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>
#include <QtDebug>
#include <QFont>
#include "matrix.h"
#include "rational.h"

class Interface : public QWidget
{
    Q_OBJECT
    QLabel* nameA, *header, *output;
    QLineEdit* valueA;
    QLineEdit** values = nullptr;
    int a = 1;
    QPushButton *transponateBtn, *determinantBtn, *rankBtn;

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();
public slots:
    void showElements();
    void rank();
    void determinant();
    void transponate();
};
#endif // INTERFACE_H
