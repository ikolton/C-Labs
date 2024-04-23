///*
// * Type traits for Vector
//For given class Vector<T,N> define template class vector_traits<T> that for given type T defines:
//• How arguments of type T are passed from or to methods get and set of a Vector<T>.
//By default they should be passed by const reference, but for types int and double by value.
//• The type of scalar in
// Vector operator * ( scalar, const Vector & x)
//By default it should be T, but for std::string it should be int.
//• Operation used in operator *. By default it should be multiplication by scalar, but strings
//should be multiplied like this 3 * [„to”, „A”] → [„tototo”,”AAA”],
//• Static method that returns the default value of type T :
//zero for arithmetic types and "0" for strings.
// Modify class template Vector<T,N> but do not define its specializations.
// */

#ifndef LAB8_VECTOR_H
#define LAB8_VECTOR_H

#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

// Type traits for Vector
template<typename T>
struct vector_traits {

    using argument_type = const T&;


    using scalar_type = T;


    static T multiply(const T& scalar, const T& value) {
        return scalar * value;
    }


    static T default_value() {
        return T();
    }
};

// Specialization for int: pass by value, scalar type is int
template<>
struct vector_traits<int> {
    using argument_type = int;
    using scalar_type = int;

    static int multiply(int scalar, const int& value) {
        return scalar * value;
    }

    static int default_value() {
        return 0;
    }
};

// Specialization for double: pass by value, scalar type is double
template<>
struct vector_traits<double> {
    using argument_type = double;
    using scalar_type = double;

    static double multiply(double scalar, const double& value) {
        return scalar * value;
    }

    static double default_value() {
        return 0.0;
    }
};

// Specialization for std::string: pass by const reference, scalar type is int
template<>
struct vector_traits<std::string> {
    using argument_type = const std::string&;
    using scalar_type = int;

    static std::string multiply(int scalar, const std::string& value) {
        std::string result;
        for (int i = 0; i < scalar; ++i) {
            result += value;
        }
        return result;
    }

    static std::string default_value() {
        return "0";
    }
};

/*
 *  To class template Vector<T,N> add template parameter P that will pass policies:
 • init policy: decides if default constructor initializes vector with default values (zeroes).
• check policy: defines if methods get and set are checking indices and how they react on the
out of bound error.
 Create policies: safePolicy (it initializes, checks indices and throws exception) and fastPolicy (do
not initializes and do not  checks indices).
 Is there a way to easily define all combinations of policies?
 Vector<int, 5, SafePolicy> a;
 a.set(6, 9); // throws an exception
 Vector<double, 4, FastPolicy> b;
 b.set(6, 0);   // the result is unspecified
 */

struct SafeInitPolicy {
    template<typename T, size_t N>
    static void initialize(T (&data)[N]) {
        for (int i = 0; i < N; ++i) {
            data[i] = vector_traits<T>::default_value();
        }
    }
};

struct FastInitPolicy {
    template<typename T, size_t N>
    static void initialize(T (&data)[N]) {
    }
};

struct SafeCheckPolicy {
    static void check_index(size_t index, size_t size) {
        if (index >= size){
            throw std::out_of_range("Index out of range");
        }
    }
};

struct FastCheckPolicy {
    static void check_index(size_t index, size_t size) {
    }
};

struct SafePolicy : SafeInitPolicy, SafeCheckPolicy {
};

struct FastPolicy : FastInitPolicy, FastCheckPolicy {
};

struct InitFastPolicy : SafeInitPolicy, FastCheckPolicy {
};

template <typename T, size_t N, typename P = FastPolicy>
class Vector : P {
    T data[N];

public:
    typedef T value_type;
    typedef std::size_t  size_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T& const_reference;

    Vector() {
        P::initialize(data);
    };
    Vector(const Vector & v) {
        P::check_index(v.size(), N);
        std::copy(v.data, v.data + N, data);
    };
    Vector &operator=(const Vector & m) {
        P::check_index(m.size(), N);
        std::copy(m.data, m.data + N, data);
        return *this;
    };

    Vector(const std::initializer_list<T> &list){
        P::check_index(list.size(), N);
        std::copy(list.begin(), list.begin() + N, data);
    }
    [[nodiscard]] size_type size() const {
        return N;
    }

    typename vector_traits<T>::argument_type get(size_type index) const {
        P::check_index(index, N);
        return data[index];
    }

    void set(size_type index, typename vector_traits<T>::argument_type value) {
        P::check_index(index, N);
        data[index] = value;
    }

    friend Vector operator* (typename vector_traits<T>::scalar_type scalar, const Vector & v ){
        Vector result;
        for(int i=0; i < v.size(); ++i){
            result.set(i, vector_traits<T>::multiply(scalar, v.get(i)));
        }
        return result;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector & v) {
        for(int i=0; i < v.size(); ++i){
            out << v.get(i) << " ";
        }
        return out;
    }

    friend std::istream &operator>>(std::istream &in, Vector & v) {
        typename Vector::value_type value;
        for(int i=0; i < v.size(); ++i){
            in >> value;
            if(in)
                v.set(i, value);
        }
        return in;
    }
};

#endif // LAB8_VECTOR_H
