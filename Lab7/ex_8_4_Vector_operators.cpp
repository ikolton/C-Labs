#include <iostream>
#include <functional> // For std::plus, std::minus
using namespace std;



template<typename T, typename U>
struct Node{
    const T& lhs;
    const U& rhs;

    Node(const T& lhs, const U& rhs) : lhs(lhs), rhs(rhs) {}

    [[nodiscard]] constexpr size_t size() const {
        return rhs.size();
    }

    virtual int operator[](int index) const = 0;
};


// Node representing an addition operation
template <typename T, typename U>
struct AddNode : Node<T, U>{
    using Node<T, U>::Node;

    int operator[](int index) const {
        return this->lhs[index] + this->rhs[index];
    }
};
// Operator overloading for addition
template <typename T, typename U>
AddNode<T, U> operator+(const T& lhs, const U& rhs) {
    return AddNode<T, U>(lhs, rhs);
}

// Node representing a multiplication operation
template <typename U>
struct MulNode : Node<int, U>{
    using Node<int, U>::Node;

    int operator[](int index) const {

        return this ->lhs * this->rhs[index];
    }
};
// Operator overloading for multiplication
template <typename U>
MulNode<U> operator*(const int& lhs, const U& rhs) {
    return MulNode<U>(lhs, rhs);
}

template <typename T, typename U>
struct SubNode : Node<T, U>{
    using Node<T, U>::Node;

    int operator[](int index) const {
        return this ->lhs[index] - this->rhs[index];
    }
};

template <typename T, typename U>
SubNode<T, U> operator-(const T& lhs, const U& rhs) {
    return SubNode<T, U>(lhs, rhs);
}

template <int N>
class Vector {
    int data[N];
public:
    Vector() {
        cout << " Default constr" << endl;
    }
    Vector(std::initializer_list<int> list) {
        cout << " Init list constr" << endl;
        auto it = list.begin();
        for (int i = 0; i < N; i++) {
            data[i] = *it++;
        }
    }
    Vector(const Vector& m) {
        std::copy(m.data, m.data + N, data);
        cout << " Copy constr" << endl;
    }

    template <typename T, typename U>
    Vector(const Node<T,U>& m) {
        for (int i = 0; i < m.size(); i++) {
            data[i] = m[i];
        }
    }

    int operator[](int index) const {
        return data[index];
    }
    int& operator[](int index) {
        return data[index];
    }

    friend ostream& operator<<(ostream& out, const Vector& m) {
        for (auto x : m.data) {
            cout << x << ", ";
        }
        return out;
    }
    [[nodiscard]] constexpr size_t size() const {
        return N;
    }
};






int main(){
  using V = Vector<10>;
  V v{1,2,3,4,5,6,7,8,9,10};
  V x(v);
  V y{4,4,2,5,3,2,3,4,2,1};

    cout << "Lazy operations :\n";
    // It does not create temporary Vectors
    // It computes resulting vector coordinate by coordinate
    // (evaluating whole expression)
    V z = v + x + 3 * y - 2 * x;
    cout << z << endl;

    // Computes only one coordinate of Vector
    int e = (z + x + y)[2];
    cout << " e = " << e << endl;

//    V h = 2*v;
//    cout << h << endl;

    return 0;
}

/**
 Init list constr
 Copy constr
 Init list constr
Lazy operations :
 Default constr
12, 12, 6, 15, 9, 6, 9, 12, 6, 3,
e = 11
 */