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
    // By default, pass arguments of type T by const reference
    using argument_type = const T&;

    // By default, scalar type is T
    using scalar_type = T;

    // By default, use multiplication for scalar operation
    static T multiply(const T& scalar, const T& value) {
        return scalar * value;
    }

    // Static method to return the default value of type T
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

template <typename T, size_t N >
class Vector {
    T data[N];
public:
    typedef T value_type;
    typedef std::size_t  size_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T& const_reference;

    Vector() = default;
    Vector(const Vector & v) = default;
    Vector &operator=(const Vector & m) = default;

    Vector(const std::initializer_list<T> &list){
        std::copy(list.begin(), list.end(), data);
    }
    size_type size() const {
        return N;
    }

    const typename vector_traits<T>::argument_type get(size_type index) const {
        return data[index];
    }

    void set(size_type index, typename vector_traits<T>::argument_type value) {
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
