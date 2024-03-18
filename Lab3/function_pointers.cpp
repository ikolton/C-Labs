
//Change the file function_pointers.cpp so that it will compile with -std=c++03 flag.
// Replace auto and decltype with appropriate function pointers.

#include <iostream>
#include <cmath>
using namespace std;

// Function pointer for sqrtn
typedef double (*SqrtFuncPtr)(int, double);

// Function pointer for power
typedef double (*PowerFuncPtr)(double, double);

// Computes n-th root of x
double sqrtn(int n, double x) {
    return exp(log(x) / n);
}

// Computes x raised to the power of y
double power(double x, double y) {
    return exp(log(x) * y);
}

template <typename F, typename G>
double function(int n, double y, double z, F f, G g) {
    return (f(n, y) > z) ? g(z, y) : g(y, z);
}

int nmain() {
    SqrtFuncPtr fp1 = sqrtn;
    PowerFuncPtr fp2 = power;
    double (*fp3)(int, double, double, SqrtFuncPtr, PowerFuncPtr) = function;

    cout << fp3(2, 10, 3, fp1, fp2) << endl;
    cout << fp3(3, 10, 3, fp1, fp2) << endl;

    return 0;
}
