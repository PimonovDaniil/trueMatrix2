
// trueMatrix.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//https://github.com/PimonovDaniil/trueMatrix
#include <locale.h>
#include <iostream>
#include <ctime>
#include "Matrix/Matrix.h"
using namespace mathTools;
using namespace std;

Matrix getRandomSquareMatrix(int k/*размер*/) { //для демонстрации и отладки
    Matrix m(k);
    for (int i = 0; i < k; i++) 
        for (int j = 0; j < k; j++)
            m[i][j] = rand() % 10;
    return m;
}

int main()
{
    setlocale(LC_CTYPE, "RUSSIAN");
    Matrix::debug = false; //отображать конструкторы/деструкторы

    /*настройка формата вывода матрицы*/
    Matrix::getSetting().setPrecision(3); //устанавливает точность
    Matrix::getSetting().setSetw(5); //Устанавливает ширину поля

    //const Matrix test(3);
    ////test[0][0] = 5;
    //cout << test[0][0] << endl;
    //cout << test;

    /*первый вариант инициализации матрицы(через двумерный динамический массив)*/
    double* a1 = new double [2*3];
    a1[0] = 2; a1[1] = 0; a1[2] = -1;
    a1[3] = 0; a1[4] = -2; a1[5] = 2;
    Matrix a(2, 3, a1);
    delete[] a1;
 
    /*второй вариант инициализации матрицы*/
    Matrix b(3, 3);
    b[0][0] = 4; b[0][1] = 1; b[0][2] = 0;
    b[1][0] = 3; b[1][1] = 2; b[1][2] = 1;
    b[2][0] = 0; b[2][1] = 1; b[2][2] = 0;

    cout << "I. С помощью функций-элементов класса обеспечить:" << endl;
    cout << "  есть матрица А:\n" << a << "  есть матрица B:\n" << b;
    cout << "  1) проверку возможности умножения двух матриц;\n";
    cout << "\tA * B: " << ((a.isMultiply(b)) ? "TRUE" : "FALSE") << endl;
    cout << "\tB * A: " << ((b.isMultiply(a)) ? "TRUE" : "FALSE") << endl;
    cout << "  2) проверку возможности сложения двух матриц;\n";
    cout << "\tA + B: " << ((b.isSum(a)) ? "TRUE" : "FALSE") << endl;
    cout << "  3) максимального элемента матрицы;\n";
    cout << "\tмаксимальный элемент матрицы А: " << a.getMax() << endl;
    cout << "  4) минимального элемента матрицы.\n";
    cout << "\tминимальный элемент матрицы А: " << a.getMin() << endl;

    cout << "\nматематические действия над матрицами A и B\nбез получения новых матриц, т.е.переопределить\nоператоры\n";
    cout << "а) A = B;";
    a = getRandomSquareMatrix(3); b = getRandomSquareMatrix(3);
    cout << "\n  пусть матрица А:\n" << a << "\n  пусть матрица B:\n" << b << endl;
    a = b;
    cout << "  А = B" << endl;
    cout << "  матрица А:\n" << a << "\n  матрица B:\n" << b;
    cout << "\nб) A += B;";
    a = getRandomSquareMatrix(2); b = getRandomSquareMatrix(2);
    cout << "\n  пусть матрица А:\n" << a << "\n  пусть матрица B:\n" << b << endl;
    if (a.isSum(b)) a += b;
    cout << "  А += B" << endl;
    cout << "  матрица А:\n" << a << "\n  матрица B:\n" << b;
    cout << "\nв) A -= B;";
    a = getRandomSquareMatrix(4); b = getRandomSquareMatrix(4);
    cout << "\n  пусть матрица А:\n" << a << "\n  пусть матрица B:\n" << b << endl;
    if (a.isSum(b)) a -= b;
    cout << "  А -= B" << endl;
    cout << "  матрица А:\n" << a << "\n  матрица B:\n" << b;
    cout << "\nг) A *= B;";
    a = getRandomSquareMatrix(2); b = getRandomSquareMatrix(2);
    cout << "\n  пусть матрица А:\n" << a << "\n  пусть матрица B:\n" << b << endl;
    if (a.isMultiply(b)) a *= b;
    cout << "  А *= B" << endl;
    cout << "  матрица А:\n" << a << "\n  матрица B:\n" << b;
    cout << "\nд) а также A *= k – умножение матрицы на скаляр";
    a = getRandomSquareMatrix(2); b = getRandomSquareMatrix(2);
    cout << "\n  пусть матрица А:\n" << a << endl;
    a *= 2.5;
    cout << "  А *= 2.5" << endl;
    cout << "  матрица А:\n" << a << endl;

    Matrix c;
    cout << "III. C помощью внешних операторов обеспечить \nдвуместные операции над матрицами A и B\nс получением новой матрицы C:" << endl;
    a = getRandomSquareMatrix(4); b = getRandomSquareMatrix(4);
    cout << "  есть матрица А:\n" << a << "  есть матрица B:\n" << b;
    cout << "1) сложение (C = A + B);" << endl << "  матрица C:" << endl;
    if(a.isSum(b)) c = a + b;
    cout << c;
    cout << "2) вычитание (C = A – B);" << endl << "  матрица C:" << endl;
    if (a.isSum(b)) c = a - b;
    cout << c;
    cout << "3) произведение (С = A * B);" << endl << "  матрица C:" << endl;
    if (a.isMultiply(b)) c = a * b;
    cout << c;
    cout << "4) умножение матрицы на скаляр (С = A * 3.1)." << endl << "  матрица C:" << endl;
    c = a * 3.1;
    cout << c;
}