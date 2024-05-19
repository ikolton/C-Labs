//Exercise 3.  Concepts
//        Implement concept Container, that describes containers that can be iterated using range base for
//loop, has member type value_type and its elements can be added using operator+.
//Implement methods print(object) that prints information about object using member method print
//        ( i.e. object.print() )  is object has one, otherwise use  operator<<.
//If both method and operator are present, prefer operator. Define appropriate concepts that check if
//obect has method print or operator<<.
//If object is a Container, then print all its elements (using appropriate print method).



#include <iostream>
#include <vector>
using namespace std;
template <typename  T>
class A{
protected:
    T x;
public:
    A(T x = T()) : x(x) {}
    void print() const{
        cout << "[" << x << "]";
    }
    friend A operator+(const A & a, const A & b){
        return a.x + b.x;
    }

};

template <typename T>
class B: public A<T>{
public:
    using A<T>::A;
    friend std::ostream & operator<<(std::ostream & out, const B & b){
        return (out << "#" << b.x << "#");
    }
};

template<typename T>
concept Container = requires(T a, typename T::value_type n) {
{ a.begin() } -> std::same_as<decltype(a.end())>;
{ a.end() } -> std::same_as<decltype(a.begin())>;
{ a[0] + n } -> std::same_as<typename T::value_type>;
};

template<typename T>
concept HasPrint = requires(T a) {
{ a.print() } -> std::same_as<void>;
};

template<typename T>
concept HasOstreamOperator = requires(T a, std::ostream& os) {
{ os << a } -> std::same_as<std::ostream&>;
};

template<Container T>
void print(const T& container) {
    for (const auto& item : container) {
        print(item);
    }
}

template<typename T>
requires HasOstreamOperator<T>
void print(const T& item) {
    std::cout << item << '\n';
}

template<typename T>
requires (!HasOstreamOperator<T> && HasPrint<T>)
void print(const T& item) {
    item.print();
    std::cout << '\n';
}

template<Container T>
typename T::value_type sum(const T& container) {
    typename T::value_type total = 0;
    for (const auto& item : container) {
        total = total + item;
    }
    return total;
}




int main() {
    vector v{1,2,4,5};
    print(v);
    A<int> a{5};
    print(a);
    B<double> b{3.14};
    print(b);
    print(2.7);
    vector<A<int>> va{ 4, 5, 7, 9};
    vector<B<int>> vb{ 4, 5, 7, 9};
    print(va);
    print(vb);
    print( sum(v) );
    print( sum(vb) );
    return 0;
}
/**
* Expected output
0 : 1
1 : 2
2 : 4
3 : 5------
[5]
#3.14#
2.7
0 : [4]
1 : [5]
2 : [7]
3 : [9]------
0 : #4#
1 : #5#
2 : #7#
3 : #9#------
12
#25#
*/