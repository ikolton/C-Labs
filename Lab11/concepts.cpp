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
concept Printable = requires(T t){t.print();};
template<typename T>
concept Operable = requires(T t){cout << t;};
template<typename T>
concept Container = requires(T t, T::value_type vt){t.begin()++;t.end();vt+vt;};

template<Operable T>
void print(T t){
cout << t;
cout << endl;
}
template<typename T>
void print(T t)requires (Printable<T> && !Operable<T>){
t.print();
cout << endl;
}
template<Container T>
void print(T t){
int i=0;
for(auto e:t){
cout << i++ << " : ";
print(e);
}
cout << "----" << endl;
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
    // print( sum(v) );
    // print( sum(vb) );
    return 0;
}
/**
* Expected output
0 : 1
1 : 2
2 : 4
3 : 5
-------
[5]
#3.14#
2.7
0 : [4]
1 : [5]
2 : [7]
3 : [9]
-------
0 : #4#
1 : #5#
2 : #7#
3 : #9#
-------
12
#25#
*/
