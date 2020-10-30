#include "Matrix.h"
#include <iostream>
#include <locale.h>
#include <iomanip>
#include <utility>

namespace mathTools
{
    bool Matrix::debug = false;
    settings* settings::uniqueInstance = nullptr;
    settings* Matrix::setting = settings::create();
    int Matrix::num = 0; //начальное кол-во объектов класса

    /*инициализация (создание дубликата матрицы)*/
    void Matrix::init(size_t rows, size_t cols, double* matrix) {
        
        this->numObj = ++this->num;

        if (rows * cols == 0){
            this->rows = this->cols = 0;
            this->matrix = nullptr;
            return;
        }

        this->rows = rows; this->cols = cols;

        this->matrix = new double[rows * cols]();

        if(matrix != nullptr)
            std::copy(matrix, matrix + rows * cols, this->matrix);

        /*for (int i = 0; i < this->rows * this->cols; i++)
            this->matrix[i] = matrix[i];*/
    }

    /*копирование объекта матрица*/
    void Matrix::copy(const Matrix& other){

        

        this->cols = other.cols;
        this->rows = other.rows;
        if (((this->cols * other.cols) && (this->rows * other.rows) && (this->matrix != nullptr))) {
            for (int i = 0; i < this->rows * this->cols; i++)
                this->matrix[i] = other.matrix[i];
        }
        else {
            if (this->matrix != nullptr) 
                delete[] this->matrix;
            
            this->matrix = new double[this->rows * this->cols];
            for (int i = 0; i < this->rows * this->cols; i++)
                this->matrix[i] = other.matrix[i];
        }
        
                
    }

    void Matrix::swap(Matrix & m)
    {
        std::swap(this->rows, m.rows);
        std::swap(this->cols, m.cols);
        std::swap(this->matrix, m.matrix);
    }

    settings& Matrix::getSetting()
    {
        return *Matrix::setting;
    }

    /*конструктор  без параметров*/
    Matrix::Matrix() {
        init(0, 0, nullptr);
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "конструктор 1)" << std::endl;
    }

    /*принимает матрицу с размерами rows cols*/
    Matrix::Matrix(size_t rows, size_t cols, double* matrix) {
        init(rows, cols, matrix);
        
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "конструктор 2)" << std::endl;
    }

    /*матрица размеров rows cols заполненная нулями*/
    /*Matrix::Matrix(size_t rows, size_t cols) {
        init(rows, cols, nullptr);
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "конструктор 3)" << std::endl;
    }*/

    /*принимает квадратную матрицу*/
    Matrix::Matrix(size_t square, double* matrix) {
        init(square, square, matrix);
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "конструктор 4)" << std::endl;
    }

    /*матрица размера square^2 заполненная нулями*/
    /*Matrix::Matrix(size_t square) {
        init(square , square, nullptr);
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "конструктор 5)" << std::endl;
    }*/

    /*конструктор копирования*/
    Matrix::Matrix(Matrix& other) {
        this->matrix = nullptr;
        this->numObj = ++this->num;
        copy(other);
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "конструктор копирования)" << std::endl;
    }

    Matrix::Matrix(Matrix&& m) noexcept
    {
        this->matrix = nullptr;
        this->numObj = ++this->num;
        swap(m);
    }

    /*деструктор*/
    Matrix::~Matrix() {
        /*выкидываем за собой мусор*/
        delete[] this->matrix;
        if (debug) std::cout << "(матрица " << this->numObj << ", " << "деструтор)" << std::endl;
    }

    /*подмена понятий (перегрузка)*/
    Matrix& Matrix::operator=(const Matrix& other) 
    {
        // Проверка на самоприсваивание
        if (this != &other) copy(other);
        //delete &other;
        return *this;
    }

    Matrix& Matrix::operator=(Matrix&& m) noexcept
    {
        this->numObj = ++this->num;
        swap(m);
        return *this;
    }

    /*подмена понятий (перегрузка)*/
    Matrix::MatrixRow Matrix::operator[](const int index){
        if((index<0) || (index >= this->rows)) throw "выход за границы, объект №" + this->numObj;
        return MatrixRow(this, index);//TODO сделать проверку индексов
    }

    const Matrix::MatrixRow Matrix::operator[](const int index) const
    {
        if ((index < 0) || (index >= this->rows)) throw "выход за границы, объект №" + this->numObj;
        return MatrixRow(this, index);//TODO сделать проверку индексов
    }

    /*подмена понятий (перегрузка)*/
    Matrix& Matrix::operator+=(const Matrix& other) {
        if (this->isSum(other) == false)
            throw "Вычитание невозможно, объект №" + this->numObj;
        for (int i = 0; i < this->rows * this->cols; i++)
                this->matrix[i] += other.matrix[i];

        return *this;
    }

    /*подмена понятий (перегрузка)*/
    Matrix& Matrix::operator*=(double k) {
        for (int i = 0; i < this->rows * this->cols; i++)
                this->matrix[i] *= k;
        return *this;
    }

    Matrix& Matrix::operator*=(const Matrix& other) {
        if (this->isMultiply(other) == false) 
            throw "Вычитание невозможно, объект №" + this->numObj;
        double* newMatrix = new double [this->rows * other.cols];

        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < other.cols; j++) {
                newMatrix[/*i][j*/i * this->cols + j] = 0.0;
                for (int k = 0; k < this->cols; k++) {
                    newMatrix[/*i][j*/ i * this->cols + j] += (this->matrix[/*i][k*/ i * this->cols + k] * other.matrix[/*k][j*/ k * this->cols + j]);
                }
            }
        delete[] this->matrix;
        this->cols = other.getCols();
        matrix = newMatrix;

        return *this;
    }

    /*подмена понятий (перегрузка)*/
    Matrix& Matrix::operator-=(const Matrix& other) {
        if (this->isSum(other) == false) 
            throw "Вычитание невозможно, объект №" + this->numObj;
     
        for (int i = 0; i < this->rows * this->cols; i++)
            this->matrix[i] -= other.matrix[i];
        
        return *this;
    }

    /*подмена понятий (перегрузка)*/
    Matrix Matrix::operator+(const Matrix& other) {
        Matrix res(*this);
        res += other;
        return std::move(res);
    }

    /*подмена понятий (перегрузка)*/
    Matrix Matrix::operator-(const Matrix& other) {
        Matrix res(*this);
        res -= other;
        return std::move(res);
    }

    /*подмена понятий (перегрузка)*/
    Matrix Matrix::operator*(const Matrix& other) {
        Matrix res(*this);
        res *= other;
        return std::move(res);
    }

    /*подмена понятий (перегрузка)*/
    Matrix Matrix::operator*(double k) {
        Matrix res(*this);
        res *= k;
        return std::move(res);
    }    

    int Matrix::getCols() const{//узнать кол-во столбцов
        return this->cols;
    }

    int Matrix::getRows() const{//узнать кол-во рядов
        return this->rows;
    }

    bool Matrix::isMultiply(const Matrix& other) {
        return (this->matrix != nullptr && other.matrix != nullptr && this->cols == other.rows) ? true : false;
    }

    bool Matrix::isSum(const Matrix& other) {
        return ((this->cols == other.getCols()) && (this->rows == other.getRows()) && (other.matrix != nullptr)) ? true : false;
    }

    double Matrix::getMax() {
        if ((this->rows > 0) && (this->cols > 0)) {
            double max = matrix[0];
            for (int i = 0; i < this->rows * this->cols; i++)
                    if (matrix[i] > max)
                        max = matrix[i];
            return max;
        }
        else {
            throw "Матрица пустая, объект №" + this->numObj;
        }
    }

    settings* Matrix::settings() {
        return Matrix::setting;
    }

    double Matrix::getMin() {
        if ((this->rows > 0) && (this->cols > 0)) {
            double min = matrix[0];
            for (int i = 0; i < this->rows * this->cols; i++)
                for (int j = 0; j < this->cols; j++)
                    if (matrix[i] < min)
                        min = matrix[i];
            return min;
        }
        else {
            throw "Матрица пустая, объект №" + this->numObj;
        }
    }

    double Matrix::at(size_t i, size_t j)
    {
        return this->matrix[i * this->cols + j];
    }

    std::ostream& operator<< (std::ostream& os, const Matrix& matrix) {
        //return os << "__" << std::endl;
        for (int i = 0; i < matrix.getRows(); i++) {
            for (int j = 0; j < matrix.getCols(); j++) {
                os << std::setw(matrix.setting->getSetw()) << std::setprecision(matrix.setting->getPrecision()) << matrix.matrix[/*i][j*/i * matrix.cols + j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    settings::settings() {
        this->setw = 8;
        this->precision = 3;
    }

    settings* settings::create() {
        if (settings::uniqueInstance == nullptr) {//пофиксить при многопоточности
            settings::uniqueInstance = new settings();
        }
        return settings::uniqueInstance;
    }

    void settings::setSetw(int s)
    {
        this->setw = s;
    }

    void settings::setPrecision(int p)
    {
        this->precision = p;
    }

    int settings::getSetw()
    {
        return this->setw;
    }

    int settings::getPrecision()
    {
        return this->precision;
    }
    Matrix::MatrixRow::MatrixRow(const Matrix* owner, unsigned r)
    {
        this->m_owner = owner;
        this->m_r = r;
    }
   
    double Matrix::MatrixRow::operator[](unsigned r) const
    {
        if ((r < 0) || (r >= this->m_owner->cols)) throw "выход за границы, объект №" + this->m_owner->numObj;
        return this->m_owner->matrix[this->m_r * this->m_owner->cols + r];
    }

    double& Matrix::MatrixRow::operator[](unsigned r)
    {
        if ((r < 0) || (r >= this->m_owner->cols)) throw "выход за границы, объект №" + this->m_owner->numObj;
        return this->m_owner->matrix[this->m_r * this->m_owner->cols + r];
    }
}

