#include <cmath>
#include <cstring>
#include <iostream>

#ifndef __VECTOR__
#define __VECTOR__

class Vector {
   private:
    double *values_;
    int size_;
    bool part_of_matrix_;

   public:
    Vector(int size);
    Vector(double *data, int size);
    Vector(const Vector &args);  // コピーコンストラクタ
    explicit Vector(int dim, double arg, const char *s);
    Vector();
    ~Vector();
    double &operator[](int index);
    double operator[](int index) const;
    Vector &operator=(const Vector &arg);
    Vector &operator=(Vector &&arg);
    double operator*(const Vector &rhs) const;
    int size() const;
    void print_values() const;
    double *get_values();  // データへのポインタを取得するメソッド
    double *get_values() const;
};

#endif  // __VECTOR__