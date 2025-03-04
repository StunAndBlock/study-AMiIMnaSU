#ifndef MATRIX_HPP_
#define MATRIX_HPP_
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <bits/stl_algo.h>

typedef std::vector<double> dVec;
typedef std::vector<dVec> D2dVec;

template <typename tMatr>
class Matrix {
    public:
        Matrix();
        //Matrix(const char*&);
        Matrix(uint64_t, uint64_t);
        Matrix(const tMatr&);
        void show();
    private:
        tMatr m_;
        
};

    namespace matrix {
void show(const std::vector<double>&);
void show(const std::vector<std::vector<double>>&);
std::vector<double> GaussMethod(std::vector<std::vector<double>>& , std::vector<double>& );
std::vector<std::vector<double>> pow(const std::vector<std::vector<double>>&, int );
std::vector<std::vector<double>> mult(const std::vector<std::vector<double>>& , const std::vector<std::vector<double>>&);
std::vector<std::vector<double>> sub(const std::vector<std::vector<double>>& , const std::vector<std::vector<double>>& );
std::vector<std::vector<double>> E(int);
std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>>&);
};

double avgDev(const std::vector<double>& );
double average(const std::vector<double>& );

#endif //!MATRIX_HPP_