#include "matrix.h"
#ifndef __SPARSE_MATRIX__
#define __SPARSE_MATRIX__
class SparseMatrix {
   private:
    int rows_;
    int cols_;
    int nnz_;
    int* row_pointers_;
    int* col_indices_;
    double* values_;

   public:
    SparseMatrix(int rows, int cols);
    SparseMatrix(int rows, int cols, int nnz);
    ~SparseMatrix();
    double& operator()(int row, int index);              // 非constオブジェクト向け
    const double& operator()(int row, int index) const;  // constオブジェクト向け
    int& operator()(int row, int index, const char* s);
    const int& operator()(int row, int index, const char* s) const;
    const int operator()(int row, const char* s) const;
    int rows() const;
    int cols() const;
    int nnz() const;
    SparseMatrix& operator=(const SparseMatrix& arg);  // コピー代入演算子
    SparseMatrix& operator=(SparseMatrix&& arg);       // ムーブ代入演算子
    Matrix operator*(const Matrix& arg);
    void print_values();
    double* get_values();  // データへのポインタを取得するメソッド
    double* get_values() const;
    int* get_row_pointers();  // データへのポインタを取得するメソッド
    int* get_row_pointers() const;
    int* get_col_indices();  // データへのポインタを取得するメソッド
    int* get_col_indices() const;
    void set_row_pointers(int* new_row_pointers);
    void set_col_indices(int* new_col_indices);
    void set_values(double* new_values);
    void set_nnz(int nnz);
};
#endif  // __SPARSE_MATRIX__