#include "matrix.h"
#ifndef __TENSOR__
#define __TENSOR__

class Tensor {
   private:
    int heights_;
    int rows_;
    int cols_;
    Matrix *matrices_;

   public:
    Tensor(int heights, int rows, int cols);
    Tensor(int heights, int rows, int cols, double arg);
    Tensor();
    // デストラクタ
    ~Tensor(void);
    // 高さを返す
    int heights(void) const;
    // 行数を返す
    int rows(void) const;
    // 列数を返す
    int cols(void) const;
    // 演算子
    Matrix operator[](int height) const;
    Matrix &operator[](int height);
    Tensor& operator=(const Tensor& arg);  // コピー代入演算子
    Tensor& operator=(Tensor&& arg);
};

#endif