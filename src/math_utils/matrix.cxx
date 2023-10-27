#include "matrix.h"
// Matrixクラスの実装
Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) { values_ = new double[rows * cols]; }

Matrix::Matrix(const Matrix& arg) : rows_(arg.rows_), cols_(arg.cols_) {
    values_ = new double[rows_ * cols_];
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            (*this)(i, j) = arg(i, j);
        }
    }
}

// 全ての要素をargで初期化
Matrix::Matrix(int rows, int cols, double arg) try : rows_(rows), cols_(cols) {
    values_ = new double[rows_ * cols_];
    for (int i = 0; i < rows_ * cols_; i++) values_[i] = arg;
} catch (std::bad_alloc) {
    std::cerr << "Out of Memory" << std::endl;
    throw;
}

Matrix::Matrix() : rows_(0), cols_(0) { values_ = nullptr; }

Matrix::Matrix(const Vector& arg, const char* s) try : rows_(arg.size()) {
    values_ = new double[arg.size() * arg.size()];
    if (strcmp(s, "diag") != 0) {
        std::cerr << "Invalid string parameter" << std::endl;
        exit(1);
    }
    // Vectorの要素を対角成分とする対角行列生成
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < rows_; j++) {
            (*this)(i, j) = 0.0;
        }
        (*this)(i, i) = arg[i];
    }
} catch (std::bad_alloc) {
    std::cerr << "Out of Memory" << std::endl;
    throw;
}

Matrix::~Matrix() { delete[] values_; }

double& Matrix::operator()(int row, int col) { return values_[row * cols_ + col]; }

const double& Matrix::operator()(int row, int col) const { return values_[row * cols_ + col]; }

Vector Matrix::operator[](int row) {
    if (row >= 0 && row < rows_) {
        return Vector(values_ + row * cols_, cols_);
    } else {
        throw std::out_of_range("Row index out of range");
    }
}

int Matrix::rows() const { return rows_; }

int Matrix::cols() const { return cols_; }

void Matrix::print_values() const {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            std::cout << values_[i * cols_ + j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix& Matrix::operator=(const Matrix& arg) {
    if (this == &arg) {
        return *this;  // 自己代入の場合、何もしない
    }
    if (this->rows_ != arg.rows_ || this->cols_ != arg.cols_) {
        // 行と列のサイズが異なる場合に新しいメモリを確保
        delete[] values_;
        
        try {
            rows_ = arg.rows_;
            cols_ = arg.cols_;
            values_ = new double[rows_ * cols_];
        } catch (std::bad_alloc) {
            std::cerr << "Out of Memory" << std::endl;
            throw;
        }
    }
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            (*this)(i, j) = arg(i, j);
        }
    }

    return *this;
}

// ムーブ代入演算子の実装
Matrix& Matrix::operator=(Matrix&& arg) {
    if (this == &arg) {
        return *this;  // 自己代入の場合、何もしない
    }

    // 既存のリソースを解放
    delete[] values_;

    // メンバー変数をムーブ
    rows_ = arg.rows_;
    cols_ = arg.cols_;
    values_ = arg.values_;

    // 右辺値のリソースを無効化
    arg.rows_ = 0;
    arg.cols_ = 0;
    arg.values_ = nullptr;

    return *this;
}

double* Matrix::get_values() { return values_; }
const double* Matrix::get_values() const { return values_; }

Matrix operator+(Matrix& lhs, Matrix& rhs) {
    int rows_ = lhs.rows();
    int cols_ = lhs.cols();

    Matrix result(rows_, cols_);

    double* values_A = lhs.get_values();
    double* values_B = rhs.get_values();
    double* values_Result = result.get_values();

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            *values_Result++ = *values_A++ + *values_B++;
        }
    }

    return result;
}
Matrix operator-(Matrix& lhs, Matrix& rhs) {
    int rows_ = lhs.rows();
    int cols_ = lhs.cols();

    Matrix result(rows_, cols_);

    double* values_A = lhs.get_values();
    double* values_B = rhs.get_values();
    double* values_Result = result.get_values();

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            *values_Result++ = *values_A++ - *values_B++;
        }
    }

    return result;
}
Matrix operator*(Matrix& lhs, Matrix& rhs) {
    int numrows_A = lhs.rows();
    int numcols_A = lhs.cols();
    int numrows_B = rhs.rows();
    int numcols_B = rhs.cols();

    if (numcols_A != numrows_B) {
        throw std::invalid_argument("Matrix dimensions are not compatible for multiplication.");
    }

    Matrix result(lhs.rows(), rhs.cols());

    int numrows_Result = numrows_A;
    int numcols_Result = numcols_B;

    double* values_A = lhs.get_values();
    double* values_B = rhs.get_values();
    double* values_Result = result.get_values();

    for (int i = 0; i < numrows_Result; ++i) {
        for (int j = 0; j < numcols_Result; ++j) {
            *values_Result++ = 0.0;
        }
        for (int k = 0; k < numcols_A; ++k) {
            values_Result -= numcols_Result;
            for (int j = 0; j < numcols_Result; ++j) {
                *values_Result++ += *values_A * *values_B++;
            }
            values_A++;
        }
        values_B -= numcols_A * numcols_Result;
    }
    return result;
}



double frobenius_norm(const Matrix& arg) {
    double result = 0.0;
    const double* values_ = arg.get_values();
    int numrows_ = arg.rows();
    int numcols_ = arg.cols();
    for (int i = 0; i < numrows_; i++) {
        for (int j = 0; j < numcols_; j++) result += values_[i * numcols_ + j] * values_[i * numcols_ + j];
    }
    return std::sqrt(result);
}