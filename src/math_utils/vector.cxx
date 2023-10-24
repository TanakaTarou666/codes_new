#include "vector.h"

Vector::Vector(int size) : size_(size) {
    values_ = new double[size];
    part_of_matrix_ = false;
}

Vector::Vector(double* values, int size) : values_(values), size_(size) { part_of_matrix_ = true; };

Vector::Vector(const Vector& arg) try : size_(arg.size_), values_(new double[arg.size_]) {
    for (int i = 0; i < size_; i++) {
        values_[i] = arg.values_[i];
    }
    part_of_matrix_ = false;
} catch (std::bad_alloc&) {
    std::cerr << "Vector::Vector(const Vector &): Out of Memory!" << std::endl;
    throw;
}

Vector::Vector(int dim, double arg, const char* s) try : size_(dim) {
    values_ = new double[size_];
    part_of_matrix_ = false;
    // s="all"じゃなかったら終了
    if (strcmp(s, "all") != 0) {
        std::cerr << "Invalid string parameter" << std::endl;
        exit(1);
    }
    // Size分だけargで初期化
    for (int i = 0; i < size_; i++) {
        values_[i] = arg;
    }
} catch (std::bad_alloc&) {
    std::cerr << "Vector::Vector(int, double, const char *): Out of Memory!" << std::endl;
    throw;
}

Vector::Vector() : size_(0) {
    values_ = nullptr;
    part_of_matrix_ = false;
}

Vector::~Vector() {
    if (part_of_matrix_ == false) delete[] values_;
}

// コピー代入
Vector& Vector::operator=(const Vector& arg) {
    if (this == &arg) {
        return *this; // 自己代入の場合、何もしない
    }
    
    // 新しいリソースを確保
    double* new_values = new double[arg.size_];
    
    // 新しいリソースに値をコピー
    for (int i = 0; i < arg.size_; i++) {
        new_values[i] = arg.values_[i];
    }
    
    // 古いリソースを解放
    delete[] values_;
    
    // 新しいリソースにポインタを設定
    values_ = new_values;
    size_ = arg.size_;

    return *this;
}


Vector& Vector::operator=(Vector&& arg) {
    if (this == &arg) {
        return *this; // 自己代入の場合、何もしない
    }
    
    // 既存のリソースを解放
    delete[] values_;
    
    // リソースをムーブ
    values_ = arg.values_;
    size_ = arg.size_;

    // 右辺値のリソースを無効化
    arg.values_ = nullptr;
    arg.size_ = 0;

    return *this;
}


double& Vector::operator[](int index) {
    if (index >= 0 && index < size_) {
        return values_[index];
    } else {
        // インデックスが範囲外の場合、エラーハンドリングが必要
        // ここでは例外を投げることにします
        throw std::out_of_range("Index out of range");
    }
}

double Vector::operator[](int index) const { return values_[index]; }

double Vector::operator*(const Vector& rhs) const {
    if (size_ < 1 || rhs.size() < 1 || size_ != rhs.size()) {
        std::cout << "Can't calculate innerproduct";
        std::cout << "for 0-sized vector";
        std::cout << "or for different sized vector";
        std::cout << std::endl;
        exit(1);
    }
    double result = values_[0] * rhs[0];
    double* valuesA = (*this).get_values();
    double* valuesB = rhs.get_values();
    for (int i = 1; i < size_; i++) {
        result += valuesA[i] * valuesB[i];
    }
    return result;
}

int Vector::size() const { return size_; }

void Vector::print_values() const {
    for (int i = 0; i < size_; ++i) {
        std::cout << values_[i] << " ";
    }
    std::cout << std::endl;
}

double* Vector::get_values() { return values_; }
double* Vector::get_values() const { return values_; }