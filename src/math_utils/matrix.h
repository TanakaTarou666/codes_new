#include "vector.h"
#ifndef __MATRIX__
#define __MATRIX__

class Matrix {
   private:
    int rows_;
    int cols_;
    double* values_;

   public:
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, double arg);
    Matrix(const Matrix& arg);
    Matrix();
    explicit Matrix(const Vector& arg, const char* s);  // 第二引数をdiagとすることでargの要素を対角成分とする対角行列生成
    ~Matrix();
    double& operator()(int row, int col);              // 非constオブジェクト向け
    const double& operator()(int row, int col) const;  // constオブジェクト向け
    Vector operator[](int row);
    const Vector& operator[](int row) const;
    int rows() const;
    int cols() const;
    void print_values() const;
    Matrix& operator=(const Matrix& arg);  // コピー代入演算子
    Matrix& operator=(Matrix&& arg);       // ムーブ代入演算子

    double* get_values();  // データへのポインタを取得するメソッド
    double* get_values() const;
};
Matrix operator+(const Matrix& lhs, const Matrix& rhs);
Matrix operator-(const Matrix& lhs, const Matrix& rhs);
Matrix operator*(const Matrix& lhs, const Matrix& rhs);
// 各要素を2乗し足し合わせたものを平方根
double frobenius_norm(const Matrix& arg);

#endif  // __MATRIX__