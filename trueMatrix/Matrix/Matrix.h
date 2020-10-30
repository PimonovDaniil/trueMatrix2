#pragma once
#include <iostream>
namespace mathTools
{

    class settings;

	class Matrix
	{
        friend std::ostream& operator<< (std::ostream& os, const Matrix& matrix);
    private:
        size_t rows;
        size_t cols;
        int numObj;
        double* matrix;
        static int num;
        static settings* setting;
        
        void init(size_t rows, size_t cols,    double* matrix);/*инициализация (создание дубликата матрицы)*/
        void copy(const Matrix& other);/*копирование объекта матрица*/
        void swap(Matrix& m); /*перемещение*/

        class MatrixRow {
        private:
            const Matrix* m_owner;
            unsigned m_r;
        public:
            MatrixRow(const Matrix* owner, unsigned r);
            double operator[] (unsigned r) const;
            double& operator[] (unsigned r);
        };

    public:
        static settings& getSetting();
        
        static bool debug;
        Matrix(); /*конструктор  без параметров*/
        Matrix(size_t rows, size_t cols, double* matrix = nullptr); /*принимает матрицу с размерами rows cols*/
        //Matrix(size_t rows, size_t cols);/*матрица размеров rows cols заполненная нулями*/
        Matrix(size_t square, double* matrix = nullptr);/*принимает квадратную матрицу*/
        //Matrix(size_t square);/*матрица размера square^2 заполненная нулями*/
        
Matrix(Matrix& other) ;/*конструктор копирования*/
        Matrix(Matrix&& m) noexcept;
        ~Matrix();/*деструктор*/

        /*подмена понятий (перегрузка)*/
        Matrix& operator=(const Matrix& other);
        Matrix& operator=(Matrix&& m) noexcept;
        MatrixRow operator[](const int index);
        const MatrixRow operator[](const int index) const;
        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        Matrix& operator*=(double k);
        Matrix& operator*=(const Matrix& other);
        Matrix operator+(const Matrix& other);
        Matrix operator-(const Matrix& other);
        Matrix operator*(const Matrix& other);
        Matrix operator*(double k);
     
        
        static settings* settings();
        int getCols() const; //узнать кол-во столбцов
        int getRows() const; //узнать кол-во рядов

        bool isMultiply(const Matrix& other); //проверка на возможность умножения
        bool isSum(const Matrix& other); //проверка на возможность сложения/вычитания

        double getMax(); //вернуть максимальный элемент
        double getMin(); //вернуть минимальный элемент
        double at(size_t i, size_t j);
	};


    /*класс в котором хранятся настройки
    формата вывода матрицы на экран. */
    class settings
    {
    private:
        int setw;
        int precision;
        static settings* uniqueInstance;
        settings(); 

    public:
        static settings* create();
        void setSetw(int s);
        void setPrecision(int p);
        int getSetw();
        int getPrecision();
    };
}
