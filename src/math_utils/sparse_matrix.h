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
    SparseMatrix();
    SparseMatrix(const SparseMatrix& arg);
    SparseMatrix(int size, double* diagonalValues,const char* s); 
    ~SparseMatrix();
    double& operator()(int row, int index);              // 非constオブジェクト向け
    const double& operator()(int row, int index) const;  // constオブジェクト向け
    
    //(i,j,"index") : スパースでi行目，j番目の要素の、スパースではない本来の列番号
    int& operator()(int row, int index, const char* s);
    const int& operator()(int row, int index, const char* s) const;

    const int operator()(int row, const char* s) const; //.row(引数) : row行目の要素数
    int rows() const;
    int cols() const;
    int nnz() const; //total要素数
    SparseMatrix& operator=(const SparseMatrix& arg);  // コピー代入演算子
    SparseMatrix& operator=(SparseMatrix&& arg);       // ムーブ代入演算子
    Matrix operator*(Matrix& arg);
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
    SparseMatrix transpose() const;
};

//Matrix operator*(const SparseMatrix& lhs, const Matrix& rhs);

#endif  // __SPARSE_MATRIX__