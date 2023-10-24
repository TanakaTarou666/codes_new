#include "dsd_tensor.h"

DSDTensor::DSDTensor(SparseMatrix &arg, int depth) : depth_(depth) {
    rows_ = arg.rows();
    cols_ = arg.cols();
    nnz_ = arg.nnz();

    row_pointers_ = new int[rows_ + 1]();
    col_indices_ = new int[nnz_];
    elements_ = new Vector[nnz_];

    int* arg_row_pointers = arg.get_row_pointers();
    int* arg_col_indices = arg.get_col_indices();

    for (int i = 0; i < rows_ + 1; i++) {
        row_pointers_[i] = arg_row_pointers[i];
    }

    for (int i = 0; i < nnz_; i++) {
        col_indices_[i] = arg_col_indices[i];
        elements_[i] = Vector(depth_,0.0,"all");
    }
}

DSDTensor::DSDTensor() : rows_(0), cols_(0), depth_(0), nnz_(0) {
    row_pointers_ = nullptr;
    col_indices_ = nullptr;
    elements_ = nullptr;
}

DSDTensor::~DSDTensor() {
    if (row_pointers_ != nullptr) delete[] row_pointers_;
    if (col_indices_ != nullptr)delete[] col_indices_;
    if (elements_ != nullptr) delete[] elements_;
}

Vector& DSDTensor::operator()(int row, int index) { return elements_[row_pointers_[row] + index]; }
const Vector& DSDTensor::operator()(int row, int index) const { return elements_[row_pointers_[row] + index]; }

int& DSDTensor::operator()(int row, int index, const char* s) {
    if (strcmp(s, "index") != 0) {
        std::cerr << "Invalid string parameter" << std::endl;
        exit(1);
    }
    return col_indices_[row_pointers_[row] + index];
}

const int& DSDTensor::operator()(int row, int index, const char* s) const {
    if (strcmp(s, "index") != 0) {
        std::cerr << "Invalid string parameter" << std::endl;
        exit(1);
    }
    return col_indices_[row_pointers_[row] + index];
}

const int DSDTensor::operator()(int row, const char* s) const {
    if (strcmp(s, "row") != 0) {
        std::cerr << "Invalid string parameter" << std::endl;
        exit(1);
    }
    int result = row_pointers_[row + 1] - row_pointers_[row];
    return result;
}

DSDTensor& DSDTensor::operator=(const DSDTensor& arg) {
    if (this == &arg) {
        return *this;  // 自己代入の場合、何もしない
    }

    // メンバー変数をコピー
    rows_ = arg.rows_;
    cols_ = arg.cols_;
    depth_ = arg.depth_;
    nnz_ = arg.nnz_;

    // 既存のリソースを解放
    delete[] row_pointers_;
    delete[] col_indices_;
    delete[] elements_;

    // 新しいリソースを確保
    row_pointers_ = new int[rows_ + 1]();
    col_indices_ = new int[nnz_];
    elements_ = new Vector[nnz_];

    // メンバー変数をコピー
    for (int i = 0; i <= rows_; i++) {
        row_pointers_[i] = arg.row_pointers_[i];
    }

    for (int i = 0; i < nnz_; i++) {
        col_indices_[i] = arg.col_indices_[i];
        elements_[i] = arg.elements_[i];
    }

    return *this;
}


DSDTensor& DSDTensor::operator=(DSDTensor&& arg) {
    if (this == &arg) {
        return *this;  // 自己代入の場合、何もしない
    }

    // 既存のリソースを解放
    delete[] row_pointers_;
    delete[] col_indices_;
    delete[] elements_;

    // メンバー変数をムーブ
    rows_ = arg.rows_;
    cols_ = arg.cols_;
    depth_ = arg.depth_;
    nnz_ = arg.nnz_;
    row_pointers_ = arg.row_pointers_;
    col_indices_ = arg.col_indices_;
    elements_ = arg.elements_;

    // 右辺値のリソースを無効化
    arg.rows_ = 0;
    arg.cols_ = 0;
    arg.depth_ = 0;
    arg.nnz_ = 0;
    arg.row_pointers_ = nullptr;
    arg.col_indices_ = nullptr;
    arg.elements_ = nullptr;

    return *this;
}

int DSDTensor::rows(void) const { return rows_; }

int DSDTensor::cols(void) const { return cols_; }

int DSDTensor::depth(void) const { return depth_; }

int DSDTensor::nnz(void) const { return nnz_; }

Vector* DSDTensor::get_elements() { return elements_; }
Vector* DSDTensor::get_elements() const { return elements_; }
int* DSDTensor::get_row_pointers() { return row_pointers_; }
int* DSDTensor::get_row_pointers() const { return row_pointers_; }
int* DSDTensor::get_col_indices() { return col_indices_; }
int* DSDTensor::get_col_indices() const { return col_indices_; }
