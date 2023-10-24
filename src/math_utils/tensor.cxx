#include "tensor.h"
Tensor::Tensor(int heights, int rows, int cols) : heights_(heights), rows_(rows), cols_(cols) {
    matrices_ = new Matrix[heights];
    for (int i = 0; i < heights; i++) {
        matrices_[i] = Matrix(rows, cols);
    }
}

Tensor::Tensor(int heights, int rows, int cols, double arg) : heights_(heights), rows_(rows), cols_(cols) {
    matrices_ = new Matrix[heights];
    for (int i = 0; i < heights; i++) {
        matrices_[i] = Matrix(rows, cols, arg);
    }
}

Tensor::Tensor() { matrices_ = nullptr; }

// デストラクタ
Tensor::~Tensor(void) { delete[] matrices_; }

int Tensor::heights(void) const { return heights_; }

int Tensor::rows(void) const { return rows_; }

int Tensor::cols(void) const { return cols_; }

Matrix Tensor::operator[](int height) const { return matrices_[height]; }

Matrix& Tensor::operator[](int height) { return matrices_[height]; }

Tensor& Tensor::operator=(const Tensor& arg) {
    if (this == &arg) {
        return *this;  // 自己代入の場合、何もしない
    }

    // メンバー変数をコピー
    heights_ = arg.heights_;
    rows_ = arg.rows_;
    cols_ = arg.cols_;

    // 既存のリソースを解放
    delete[] matrices_;

    // 新しいリソースを確保
    matrices_ = new Matrix[heights_];

    // メンバー変数をコピー
    for (int i = 0; i < heights_; i++) {
        matrices_[i] = arg.matrices_[i];
    }

    return *this;
}

Tensor& Tensor::operator=(Tensor&& arg) {
    if (this == &arg) {
        return *this;  // 自己代入の場合、何もしない
    }

    // 既存のリソースを解放
    delete[] matrices_;

    // メンバー変数をムーブ
    heights_ = arg.heights_;
    rows_ = arg.rows_;
    cols_ = arg.cols_;
    matrices_ = arg.matrices_;

    // 右辺値のリソースを無効化
    arg.heights_ = 0;
    arg.rows_ = 0;
    arg.cols_ = 0;
    arg.matrices_ = nullptr;

    return *this;
}
