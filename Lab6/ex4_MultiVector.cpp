#include <iostream>
#include <vector>

/*
 *  Exercise 4.  Mixins
 Implement class template MultiVector that as parameters takes any number of types.
It should store elements of that types in separate containers e.g. std::vector.
 It should be possible to push_back objects into MultiVector and print it to standard output.
 MultiVector<int, string, double> m;
 m.push_back(5);
 m.push_back(string(“text”));
 m.push_back(7);
m.push_back(1.2);
 m.print();   // [ 5 7 ] [ text ] [ 1.2 ]
 */
using namespace std;

// Forward declaration of MultiVector class template
template<typename... Args>
class MultiVector;

// Partial specialization for an empty parameter pack
template<>
class MultiVector<> {
public:
    void push_back() {} // Base case push_back for empty pack
    void print() const { std::cout << std::endl; } // Base case print for empty pack
};

// Recursive class template to store elements of different types in separate containers
template<typename T, typename... Args>
class MultiVector<T, Args...> {
    std::vector<T> container; // Container for the current type
    MultiVector<Args...> rest; // Recursive definition for the rest of the types

public:
    void push_back(const T& val) { container.push_back(val); } // Push back for the current type

    template<typename U>
    void push_back(const U& val) { rest.push_back(val); } // Forwarding push_back for the rest of the types

    void print() const {
        std::cout << "[ ";
        for (const auto& elem : container)
            std::cout << elem << " ";
        std::cout << "] ";
        rest.print(); // Print for the rest of the types
    }
};



int main(){

    MultiVector<int, string, double> m;
    m.push_back(5);
    m.push_back(string("text"));
    m.push_back(7);
    m.push_back(1.2);
    m.print();   // [ 5 7 ] [ text ] [ 1.2 ]
    auto v = std::move(m);
    for(auto x: { 1, 2, 3}){
        v.push_back(x+10);
        v.push_back(std::to_string(x));
        v.push_back(x/10.0);
    }
    m.print(); // [ ] [ ] [ ]   but can be undefined
    v.print(); // [ 5 7 11 12 13 ] [ text 1 2 3 ] [ 1.2 0.1 0.2 0.3 ]
    MultiVector<int, int, double, int> w;
    w.push_back(1);
    w.push_back(2.0);
    w.print(); // [ 1 ] [ ] [ 2 ] [ ]
}
/*
[ 5 7 ] [ text ] [ 1.2 ]
[ ] [ ] [ ]
[ 5 7 11 12 13 ] [ text 1 2 3 ] [ 1.2 0.1 0.2 0.3 ]
[ 1 ] [ ] [ 2 ] [ ]
 */