#include <iostream>
#include <vector>
/*
 *  Implement variadic functions:
 • average(a1, a2,…, an) that computes average of any number of numbers a1, …, an (they of
numerical type int, double etc)
• computeSum(f, x1, x2, x3, …)  it should return f(x1)+f(x2)+f(x3)+…
 • insert(container, x1, x2, x3, … ) - it pushes back x1, x2, x3, … into container.
 Hint: You can use fold expressions.
 */

using namespace std;

int f(int x){
    return x*x;
}
int cube(int x){
    return x*x*x;
}

template<typename T, typename... Args>
double average(T a, Args... args){
    return (a + ... + args) / (sizeof...(args) + 1.0);
}

template<typename F, typename... Args>
auto computeSum(F f, Args... args){
    return (f(args) + ...);
}

template<typename T, typename... Args>
void insert(std::vector<T> & v, Args... args){
    (v.push_back(args), ...);
}

int main(){

    cout << average(1, 2) << endl;                    // 1.5
    cout << average(1.0, 10, 1, 34.5f, 12u) << endl;  // 11.7
    cout << computeSum(f, 1, 2, 3, 4) << endl;        // f(1)+f(2)+f(3)+f(4) = 30
    cout << computeSum(cube, 1, 2, 3, 4) << endl;     // 1^3 + 2^3 + 3^3 + 4^3 = 100

    std::vector<int> v;
    insert(v, 1, 2, 3, 4, 5, 6);
    insert(v, 7, 8);

    for(auto x: v)                              //1 2 3 4 5 6 7 8
        cout << x << " ";
    return 0;
}