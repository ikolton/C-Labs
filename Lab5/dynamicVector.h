/*
 * Implement a partial specialization of template Vector  for N equal to 0 ( i.e. Vector<T, 0>). It
should store vector elements in a dynamical array (use smart pointers). The number of elements
should be provided in a constructor e.g. Vector<T,0> v(5);
Make interfaces of the primary template and the specialization the same or at least very similar (if
needed, extend also the primary template).
 Add method resize(newSize) that resizes Vector keeping elements values and adding tailing
zeroes if needed.  If it is reasonable implement move semantics.
 Operator+  should throw an exception if sizes do not match. The exception should be of a user
defined type VectorException that is derived from runtime_error.
 */


#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H

#include "staticVector.h"

template <typename T>
class Vector<T, 0> {
    std::unique_ptr<T[]> data;
    size_t N;
public:
    typedef T value_type;
    typedef std::size_t  size_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T& const_reference;

    Vector(size_t n): N(n), data(new T[n]) {
        for( size_t i = 0; i < N; i++ ){
            data[i] = 0;
        }
    }
    Vector(const Vector & v): N(v.N), data(new T[v.N]) {
        for( size_type i = 0; i < N; i++ ){
            data[i] = v.data[i];
        }
    }
    Vector &operator=(const Vector & m) {
        N = m.N;
        data.reset(new T[N]);
        for( size_type i = 0; i < N; i++ ){
            data[i] = m.data[i];
        }
        return *this;
    }
    Vector(const std::initializer_list<T> &list): N(list.size()), data(new T[list.size()]){
        size_type i = 0;
        for( auto elem: list ){
            data[i++] = elem;
        }
    }
    Vector &operator=(const std::initializer_list<T> &list){
        assert(list.size() == N);
        size_type i = 0;
        for( auto elem: list ){
            data[i++] = elem;
        }
        return *this;
    }
    T &operator[](size_t index){
        return data[index];
    }
    const T &operator[](size_t index) const {
        return data[index];
    }
    size_t size() const {
        return N;
    }

    // Explicit conversion from static vector to dynamic vector
    template <typename S, size_t M>
    explicit Vector(const Vector<S, M>& v) : N(M), data(new T[M]) {
        for (size_t i = 0; i < M; ++i) {
            data[i] = static_cast<T>(v[i]);
        }
    }

    Vector operator+(const Vector & m) const {
        if( N != m.N ){
            throw std::runtime_error("incompatible sizes in Vector::operator+");
        }
        Vector result(N);
        for( size_t i = 0; i < N; i++ ){
            result[i] = data[i] + m[i];
        }
        return result;
    }

    // Addition operation between static and dynamic vectors
    template <size_t M>
    friend Vector<T,M> operator+(const Vector<T, M>& u, const Vector<T, 0>& v) {
        if( M != v.size() ){
            throw std::runtime_error("incompatible sizes in Vector::operator+");
        }

        Vector<T, M> result(u);
        for (size_t i = 0; i < v.size(); ++i) {
            result[i] += v[i];
        }
        return result;
    }

    // Addition operation between static and dynamic vectors
    template <size_t M>
    friend Vector<T,M> operator+(const Vector<T, 0>& u, const Vector<T, M>& v) {
        if( M != u.size() ){
            throw std::runtime_error("incompatible sizes in Vector::operator+");
        }

        Vector<T, M> result(v);
        for (size_t i = 0; i < v.size(); ++i) {
            result[i] += u[i];
        }
        return result;
    }



    void resize(size_t newSize){
        std::unique_ptr<T[]> newData(new T[newSize]);
        for( size_t i = 0; i < std::min(N, newSize); i++ ){
            newData[i] = data[i];
        }
        for( size_t i = N; i < newSize; i++ ){
            newData[i] = 0;
        }
        N = newSize;
        data = std::move(newData);
    }
    friend std::ostream &operator<<(std::ostream &out, const Vector & v) {
        for( size_t i = 0; i < v.size(); i++ ){
            out << v[i] << " ";
        }
        return out;
    }
};

#endif //DYNAMIC_VECTOR_H
