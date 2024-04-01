#ifndef STATIC_VECTOR_H
#define STATIC_VECTOR_H

/*
 *  Implement a class template Vector<T,N> that has two template parameters:
• T - type of vector elements,
• N - number of elements.
 Coefficients of a vector should be stored in a static array.
 Implement:
 • constructors:
◦ default (set coordinates to 0),
◦ copy constructor (can be defaulted?),
◦ from initialization list,
◦ private constructor (do not set coordinates to 0, use artificial parameter),
 • access operators to the coefficients by a[index] (both for read and write),
 • internal type value_type  equal to T and method size() that returns N,
 • addition operator.  Operations on vectors with incompatible dimensions should be detected
during compilation.
 Class should be implemented in file staticVector.h.
 Question: Is it reasonable to implement move semantics
 */

#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

template <typename T, size_t N>
class Vector{
    T data[N];

public:
    typedef T value_type;
    typedef std::size_t  size_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T& const_reference;

    Vector() {
        for( auto & elem: data ){
            elem = 0;
        }
    }
    Vector(const Vector & v) {
        for( size_type i = 0; i < N; i++ ){
            data[i] = v.data[i];
        }
    }
    Vector &operator=(const Vector & m) {
        for( size_type i = 0; i < N; i++ ){
            data[i] = m.data[i];
        }
        return *this;
    }
    Vector(const std::initializer_list<T> &list){
        assert(list.size() == N);
        size_type i = 0;
        for( auto elem: list ){
            data[i++] = elem;
        }
    }

    // Explicit conversion from dynamic vector to static vector
    template <size_t M>
    explicit Vector(const Vector<T, M>& v) {
        //static_assert(N >= v.size(), "Cannot convert from dynamic to static vector with larger dimension.");
        for (size_t i = 0; i < v.size(); ++i) {
            data[i] = v[i];
        }

    }

    // Explicit conversion from another vector type with potentially different dimensions
    template <typename S, size_t M>
    explicit Vector(const Vector<S, M>& v) {
        static_assert(N >= M, "Cannot convert from vector with larger dimension.");
        for (size_t i = 0; i < M; ++i) {
            data[i] = static_cast<T>(v[i]);
        }
        for (size_t i = M; i < N; ++i) {
            data[i] = 0;
        }
    }

    template<typename M>
    friend Vector operator+ (const Vector<M,N> & u, const Vector<M, N> & v){
        Vector result;
        for( size_type i = 0; i < N; i++ ){
            result.data[i] = u.data[i] + v.data[i];
        }
        return result;
    }

    [[nodiscard]] constexpr size_type size() const {
        return N;
    }

    const_reference get(size_type index) const {
        return data[index];
    }

    void set(size_type index, const_reference value) {
        data[index] = value;
    }

    reference operator[](size_type index){
        return data[index];
    }
    const_reference operator[](size_type index) const{
        return data[index];
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector & v) {
        for( auto elem: v.data ){
            out << elem << " ";
        }
        return out;
    }

};

#endif //STATIC_VECTOR_H