#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <functional>

using namespace std;
/*
 * A) Implement a function template sqr with one type template parameter T
T sqr(T x)
that returns x*x for all numeric types.
Define specialization for std::string that returns doubled string e.g for “ab” it returns “abab”
cout << sqr(4) << endl; // 16
cout << sqr(14.5) << endl; // 210.25
cout << sqr(string("hey")) << endl; // heyhey
 */

template <typename T>
T sqr(T x){
    return x*x;
}

template <>
string sqr(string x){
    return x+x;
}

/*
 * Implement a function template mod with one non-type template parameter N (of type
unsigned)
int mod<N>(int a, int b)
that returns a+b modulo N. Specialization for N=0 should return just a + b;
cout << mod<5>(130,1) << endl; // 1
cout << mod<7>(1,130) << endl; // 5
cout << mod<0>(13,14) << endl; // 27
 */

template <unsigned N>
int mod(int a, int b){
    return (a+b)%N;
}

template <>
int mod<0>(int a, int b){
    return a+b;
}

/*
 * Implement a function template
void print(const Container & v)
that prints to standard output all elements of the given container (vector, list, deque, C array)
separating elements by a single space.
std::vector<int> v = {1, 21, 34, 4, 15};
print(v); // 1 21 34 4 15
std::list<double> l = {1, 2.1, 3.2, 6.3};
print(l); // 1 2.1 3.2 6.3
double tab[] = {1.2, 3.4, 5.5};
print(tab); // 1.2 3.4 5.5
 */

template <typename Container>
void print(const Container & v){
    for( auto x  : v)
        cout << x << " ";
    cout << endl;
}

/*
 *
 * Implement a function template apply with two template parameters
C – type of container
F – type of function or functional object
 C apply (const C& c, F f)
that for each element x in c calls f(x) and inserts returned result to new container.
Function should return this new container (of type C).
auto w = applyFun(v, sqr<int>); // 1 441 1156 16 225
auto w3 = applyFun(w, [](int a){return mod<0>(a, 3);}); // 4 444 1159 19 228
auto l2 = applyFun(l, sqr<double>); // 1 4.41 10.24 39.69
 */

template <typename C, typename F>
C applyFun(const C& c, F f){
    C result;
    for( auto x  : c)
        result.push_back(f(x));
    return result;
}

/*
 * Implement a function template process that has three template parameters
◦ T – the type of array elements
◦ f – a pointer to function with one argument of type T and return type T
◦ N – the number of elements in the array
void process<T,f,N>(T array[]);
The function process for each element in given array calls function f and replaces this
element with the result of the call.
double a[] = {1, 2, 3, 4};
process<double, sin, 4> (a);
print(a); // 0.841471 0.909297 0.14112 -0.756802
 */

template <typename T, T (*f)(T), int N>
void process(T array[]){
    for(int i = 0; i < N; i++)
        array[i] = f(array[i]);
}



int main(){

    // function template  sqr<T>
    cout << sqr(4) << endl;             // 16
    cout << sqr(14.5) << endl;          // 210.25
    cout << sqr(string("hey")) << endl; // heyhey

    // function template mod<N>
    cout << mod<5>(130,1) << endl;        // 1
    cout << mod<7>(1,130) << endl;        // 5
    cout << mod<0>(13,14) << endl;        // 27

    // function template print
    std::vector<int> v = {1, 21, 34, 4, 15};
    print(v);                    // 1 21 34 4 15

    std::list<double> l = {1, 2.1, 3.2, 6.3};
    print(l);                    // 1 2.1 3.2 6.3

    double tab[] = {1.2, 3.4, 5.5};
    print(tab);                  // 1.2 3.4 5.5

    using namespace std::placeholders;  // for _1, _2, _3...
    // function template applyFun
    auto w = applyFun(v, sqr<int>);
    print(w);  // 1 441 1156 16 225

    // applyFun accepts unary function so we bind the first argument of mod<5>
    auto w2 = applyFun(w, std::bind(mod<5>, 4, _1));
    print(w2); // 0 0 0 0 4

    auto w3 = applyFun(w, [](int a){return mod<0>(a, 3);}  );
    print(w3); // 4 444 1159 19 228


    auto l2 = applyFun(l, sqr<double>);
    print(l2); // 1 4.41 10.24 39.69

    auto l3 = applyFun(l2, std::bind(mod<5>, _1, 2));
    print(l3); // 3 1 2 1

    // function sin is overloaded, we need to cast it
    auto l4 = applyFun(l3, static_cast<double(*)(double)>(std::sin));
    print(l4); // 0.14112 0.841471 0.909297 0.841471

    double a[] = {1, 2, 3, 4};
    process<double, sin, 4> (a);
    print(a);  // 0.841471 0.909297 0.14112 -0.756802

    return 0;
}
/**
16
210.25
heyhey
1
5
27
1 21 34 4 15
1 2.1 3.2 6.3
1.2 3.4 5.5
1 441 1156 16 225
0 0 0 0 4
4 444 1159 19 228
1 4.41 10.24 39.69
3 1 2 1
0.14112 0.841471 0.909297 0.841471
0.841471 0.909297 0.14112 -0.756802
*/