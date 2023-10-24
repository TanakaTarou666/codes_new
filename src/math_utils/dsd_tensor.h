#include "sparse_matrix.h"

class DSDTensor {
   private:
    int rows_;
    int cols_;
    int depth_;
    int nnz_;
    int* row_pointers_;
    int* col_indices_;
    Vector* elements_;

    public:
    DSDTensor(SparseMatrix &arg,int depth);
    DSDTensor();
    ~DSDTensor();
    Vector& operator()(int row, int col); 
    const Vector& operator()(int row, int col) const;  
    int& operator()(int row, int index, const char* s);
    const int& operator()(int row, int index, const char* s) const;
    const int operator()(int row, const char* s) const;
    DSDTensor& operator=(const DSDTensor& arg);  // コピー代入演算子
    DSDTensor& operator=(DSDTensor&& arg); 
    int rows() const;
    int cols() const;
    int depth() const;
    int nnz() const;
    Vector* get_elements();  // データへのポインタを取得するメソッド
    Vector* get_elements() const;
    int* get_row_pointers();  // データへのポインタを取得するメソッド
    int* get_row_pointers() const;
    int* get_col_indices();  // データへのポインタを取得するメソッド
    int* get_col_indices() const;
};