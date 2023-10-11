#include "application.h"
#include <string>
#include <conio.h>

Application::Application()
{
	setlocale(LC_ALL, "");
	setTextColor(WHITE);
}

void Application::setTextColor(int textColorIndex) { // Смена цвета текста
	cout << "\x1B[" + to_string(textColorIndex) + "m";
}

int Application::menu() {
	int currentNum = 1;
	output(currentNum);
	int button;
	while (true) {
		button = _getch();
		button = (button == 224) ? _getch() : button;
		if (button == 80 || button == 77) {
			system("cls");
			currentNum += 1;
			currentNum = currentNum == 7 ? 1 : currentNum;
			output(currentNum);
		}
		else if (button == 72 || button == 75) {
			system("cls");
			currentNum -= 1;
			currentNum = currentNum == 0 ? 6 : currentNum;
			output(currentNum);
		}
		else if (button >= 49 && button <= 53) {
			system("cls");
			currentNum = button - 48;
			output(currentNum);
			return currentNum;
		}
		else if (button == 13) {
			if (currentNum != 6)
				return currentNum;
			else {
				return -1;
			}
		}
		else if (button == 27) {
			return -1;
		}
	}
}

void Application::output(int current) {

	setTextColor(WHITE);
	cout << "\tМеню управления квадратной матрицей.\n";
	setTextColor(current == 1 ? WHITE : BLUE);
	cout << "[1] ";
	setTextColor(WHITE);
	cout << "Заполнить матрицу." << '\n';

	setTextColor(current == 2 ? WHITE : BLUE);
	cout << "[2] ";
	setTextColor(WHITE);
	cout << "Вывести матрицу." << '\n';

	setTextColor(current == 3 ? WHITE : BLUE);
	cout << "[3] ";
	setTextColor(WHITE);
	cout << "Найти ранг матрицы." << '\n';

	setTextColor(current == 4 ? WHITE : BLUE);
	cout << "[4] ";
	setTextColor(WHITE);
	cout << "Найти определитель матрицы." << '\n';

	setTextColor(current == 5 ? WHITE : BLUE);
	cout << "[5] ";
	setTextColor(WHITE);
	cout << "Вывести транспонированную матрицу." << '\n';

	setTextColor(current == 6 ? WHITE : RED);
	cout << "[ESC] ";
	setTextColor(WHITE);
	cout << "Выход из программы." << '\n';
}

int Application::execute(int currentNum) {
	switch (currentNum) {
	case -1:
		return 1;
	case 1:
	{
		delete m;
		int a;
		cout << "Введите количество строк в матрице: ";
		cin >> a;
		while (a < 1) {
			system("cls");
			cout << "Число строк в матрице должно быть больше 0.\n\n";
			cout << "Введите количество строк в матрице: ";
			cin >> a;
		}
		Matrix *m = new Matrix(a);
		this->m = m;
		cout << "Введите " << a * a << " значений:\n";
		for (int i = 0; i < a * a; i++) {
			cin >> (*m)[i];
		}
		break;
	}
	case 2:
		cout << *m;
		break;
	case 3:
		cout << "\n\n";
		cout << "Ранг матрицы равен " << m->rank() << ".\n\n\n";
		break;
	case 4:
		cout << "\n\n";
		cout << "Определитель матрицы равен " << m->determinant() << ".\n\n\n";
		break;
	case 5:
		cout << m->transponate();
		break;
	}
	return 0;
}