#include "sparse_matrix.h"
// コンストラクタ
SparseMatrix::SparseMatrix(int rows, int cols) : rows_(rows), cols_(cols) {
    // 行ポインタ、列インデックス、データを初期化
    row_pointers_ = new int[rows + 1]();
    col_indices_ = nullptr;  // サイズは後で設定する
    values_ = nullptr;         // サイズは後で設定する
    nnz_ = 0;
}
// コンストラクタ
SparseMatrix::SparseMatrix(int rows, int cols, int nnz) : rows_(rows), cols_(cols), nnz_(nnz) {
    // 行ポインタ、列インデックス、データを初期化
    row_pointers_ = new int[rows + 1]();
    col_indices_ = new int[nnz];
    values_ = new double[nnz];
}
// デストラクタ
SparseMatrix::~SparseMatrix() {
    // データを解放
    delete[] row_pointers_;
    delete[] col_indices_;
    delete[] values_;
}

double& SparseMatrix::operator()(int row, int index) { return values_[row_pointers_[row] + index]; }
const double& SparseMatrix::operator()(int row, int index) const { return values_[row_pointers_[row] + index]; }

int& SparseMatrix::operator()(int row, int index, const char* s) {
    if (strcmp(s, "index") != 0) {
        std::cerr << "Invalid string parameter" << std::endl;
        exit(1);
    }
    return col_indices_[row_pointers_[row] + index];
}

//(i,j,"index") : スパースでi行目，j番目の要素の、スパースではない本来の列番号
const int& SparseMatrix::operator()(int row, int index, const char* s) const {
    if (strcmp(s, "index") != 0) {
        std::cerr << "Invalid string parameter" << std::endl;
        exit(1);
    }
    return col_indices_[row_pointers_[row] + index];
}

//(row,s) : row行目の要素数
const int SparseMatrix::operator()(int row, const char* s) const {
    if (strcmp(s, "row") != 0) {
        std::cerr << "Invalid string parameter" << std::endl;
        exit(1);
    }
    int result = row_pointers_[row + 1] - row_pointers_[row];
    return result;
}

int SparseMatrix::rows() const { return rows_; }
int SparseMatrix::cols() const { return cols_; }
int SparseMatrix::nnz() const { return nnz_; }　//total要素数

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& arg) {
    if (this == &arg) {
        return *this;  // 自己代入の場合、何もしない
    }

    // 新しいリソースを一時的に確保
    int* new_row_pointers = new int[arg.rows_ + 1];
    int* new_col_indices = new int[arg.nnz_];
    double* new_values = new double[arg.nnz_];

    // メンバー変数をコピー
    for (int i = 0; i <= arg.rows_; i++) {
        new_row_pointers[i] = arg.row_pointers_[i];
    }

    for (int i = 0; i < arg.nnz_; i++) {
        new_col_indices[i] = arg.col_indices_[i];
        new_values[i] = arg.values_[i];
    }

    // 既存のリソースを解放
    delete[] row_pointers_;
    delete[] col_indices_;
    delete[] values_;

    // メンバー変数を新しいリソースに設定
    row_pointers_ = new_row_pointers;
    col_indices_ = new_col_indices;
    values_ = new_values;
    rows_ = arg.rows_;
    cols_ = arg.cols_;
    nnz_ = arg.nnz_;

    return *this;
}

// ムーブ代入演算子の実装
SparseMatrix& SparseMatrix::operator=(SparseMatrix&& arg){
    if (this == &arg) {
        return *this;  // 自己代入の場合、何もしない
    }

    // 既存のリソースを解放
    delete[] row_pointers_;
    delete[] col_indices_;
    delete[] values_;

    // メンバー変数をムーブ
    rows_ = arg.rows_;
    cols_ = arg.cols_;
    nnz_ = arg.nnz_;
    row_pointers_ = arg.row_pointers_;
    col_indices_ = arg.col_indices_;
    values_ = arg.values_;

    // 右辺値のリソースを無効化
    arg.rows_ = 0;
    arg.cols_ = 0;
    arg.nnz_ = 0;
    arg.row_pointers_ = nullptr;
    arg.col_indices_ = nullptr;
    arg.values_ = nullptr;

    return *this;
}

Matrix SparseMatrix::operator*(const Matrix& arg) {
    int numRowsResult = rows_;
    int numColsResult = arg.cols();
    Matrix result(numRowsResult, numColsResult);
    double* dataA = (*this).get_values();
    int* dataArowpointers = (*this).get_row_pointers();
    int* dataAcolindices = (*this).get_col_indices();
    double* dataB = arg.get_values();
    double* dataResult = result.get_values();
    int k = 0;

    for (int i = 0; i < numRowsResult; ++i) {
        for (int j = 0; j < numColsResult; ++j) {
            dataResult[i * numColsResult + j] = 0.0;
        }
        while (k < dataArowpointers[i + 1]) {
            for (int j = 0; j < numColsResult; ++j) {
                dataResult[i * numColsResult + j] += *dataA * dataB[*dataAcolindices * numColsResult + j];
            }
            k++;
            dataAcolindices++;
            dataA++;
        }
    }

    return result;
}

void SparseMatrix::print_values() {
    int rows = (*this).rows();
    int cols = (*this).cols();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < *((*this).get_row_pointers() + i + 1) - *((*this).get_row_pointers() + i); ++j) {
            std::cout << "(" << i << ", " << *((*this).get_col_indices() + *((*this).get_row_pointers() + i) + j) << ") : " << (*this)(i, j) << "\t";
        }
        std::cout << std::endl;
    }
}

double* SparseMatrix::get_values() { return values_; }
double* SparseMatrix::get_values() const { return values_; }
int* SparseMatrix::get_row_pointers() { return row_pointers_; }
int* SparseMatrix::get_row_pointers() const { return row_pointers_; }
int* SparseMatrix::get_col_indices() { return col_indices_; }
int* SparseMatrix::get_col_indices() const { return col_indices_; }

void SparseMatrix::set_row_pointers(int* new_row_pointers) {
    // 以前のメモリを解放
    if (row_pointers_ != nullptr) delete[] row_pointers_;

    // 新しいポインタを設定
    row_pointers_ = new_row_pointers;
}

// col_indicesをセットするメンバ関数
void SparseMatrix::set_col_indices(int* new_col_indices) {
    // 以前のメモリを解放
    if (col_indices_ != nullptr) delete[] col_indices_;

    // 新しいポインタを設定
    col_indices_ = new_col_indices;
}

// dataをセットするメンバ関数
void SparseMatrix::set_values(double* new_values) {
    // 以前のメモリを解放
    if (values_ != nullptr) delete[] values_;

    // 新しいポインタを設定
    values_ = new_values;
}

// dataをセットするメンバ関数
void SparseMatrix::set_nnz(int nnz) { 
    nnz_ = nnz;}