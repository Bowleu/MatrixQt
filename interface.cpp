#include "interface.h"

Interface::Interface(QWidget *parent)
    : QWidget(parent)
{

    setWindowTitle("Работа №3");
    setFixedSize(600, 600);
    header = new QLabel("Matrix", this);
    nameA = new QLabel("A =", this);
    QFont f = nameA->font();
    f.setPointSize(20);
    nameA->setFont(f);
    f.setPointSize(32);
    header->setFont(f);
    nameA->setGeometry(40, 230, 40, 40);
    header->setGeometry(width() / 2 - 70, 20, 140, 60);
    valueA = new QLineEdit("2", this);
    valueA->setGeometry(90, 230, 40, 40);
    valueA->setMaxLength(1);
    values = new QLineEdit*[5 * 5];
    f = valueA->font();
    f.setPointSize(20);
    valueA->setFont(f);
    f.setPointSize(14);
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++) {
            values[i * 5 + j] = new QLineEdit("0", this);
            values[i * 5 + j]->setGeometry(200 + j * 60, 100 + i * 60, 40, 40);
            values[i * 5 + j]->setEnabled(false);
            f = values[i]->font();
            f.setPointSize(14);
            values[i * 5 + j]->setFont(f);
        }
    }
    f.setPointSize(12);
    transponateBtn = new QPushButton(this);
    transponateBtn->setGeometry(width() / 6 - 75, 450, 150, 60);
    transponateBtn->setText("Транспонировать");
    transponateBtn->setFont(f);
    determinantBtn = new QPushButton(this);
    determinantBtn->setGeometry(width() / 2 - 75, 450, 150, 60);
    determinantBtn->setText("Определитель");
    determinantBtn->setFont(f);
    rankBtn = new QPushButton(this);
    rankBtn->setGeometry(5 * width() / 6 - 75, 450, 150, 60);
    rankBtn->setText("Посчитать ранг");
    rankBtn->setFont(f);
    output = new QLabel(this);
    output->setGeometry(width() / 2 - 175, 520, 350, 60);
    output->setFont(f);
    output->setStyleSheet("background-color: #D2D6D5");
    output->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    connect(valueA, &QLineEdit::textChanged, this, &Interface::showElements);
    connect(rankBtn, &QPushButton::clicked, this, &Interface::rank);
    connect(determinantBtn, &QPushButton::clicked, this, &Interface::determinant);
    connect(transponateBtn, &QPushButton::clicked, this, &Interface::transponate);
    showElements();
}

void Interface::showElements() {
    QString n = valueA->text();
    a = n.toInt();
    if (a > 5) {
        a = 5;
        valueA->setText("5");
    }
    if (a < 1) {
        a = 1;
        if (n != "")
            valueA->setText("1");
    }
    for (int i = 0; i < 25; i++) {
        values[i]->setEnabled(false);
    }
    for (int i = 0; i < a; i++){
        for (int j = 0; j < a; j++) {
            values[i * 5 + j]->setEnabled(true);
        }
    }
}

void Interface::transponate() {
    Matrix m(a);
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            m[i * a + j] = Number(values[i * 5 + j]->text());
        }
    }
    Matrix transponatedM(m.transponate());
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            values[i * 5 + j]->setText(transponatedM[i * a + j].toQString());
        }
    }
}

void Interface::determinant() {
    Matrix m(a);
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            QString temp = values[i * 5 + j]->text();
            m[i * a + j] = Number(temp);
        }
    }
    QString s = "Определитель равен ";
    output->setText(s + m.determinant().toQString());
}

void Interface::rank() {
    Matrix m(a);
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            QString temp = values[i * 5 + j]->text();
            m[i * a + j] = Number(temp);
        }
    }
    int rank = m.rank();
    QString s = "Ранг равен ";
    output->setText(s + QString::number(rank));
}

Interface::~Interface()
{
    delete header;
    delete nameA;
    delete valueA;
    for (int i = 0; i < 25; i++) {
        delete values[i];
    }
    delete[] values;
    delete transponateBtn;
    delete rankBtn;
    delete determinantBtn;
    delete output;
}

