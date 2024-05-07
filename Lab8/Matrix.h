#pragma once

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <stdexcept> // For std::out_of_range
#include <initializer_list>
#include <vector>     // For std::vector
using namespace std;

template <typename T, size_t N, size_t M>
class Matrix {
    T data[N * M];

public:
    template<typename E, typename Ref, typename Ptr>
    class MatrixIterator {
        E* ptr;
        size_t jump=1;
    public:

        MatrixIterator(E* p) : ptr(p) {}
        MatrixIterator(T* p, size_t jump) : ptr(p), jump(jump) {}

        MatrixIterator& operator++() {
            ptr += jump;
            return *this;
        }

        MatrixIterator operator++(int) {
            MatrixIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Ref operator*() const {
            return *ptr;
        }

        Ptr operator->() const {
            return ptr;
        }

        bool operator==(const MatrixIterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const MatrixIterator& other) const {
            return !(*this == other);
        }
    };

    //const iterator
    using const_iterator = MatrixIterator<const T,const T&, const T*>;

    // Row iterator
    using row_iterator = MatrixIterator<T, T&, T*>;

    // Column iterator
    using col_iterator = MatrixIterator<T, T&, T*>;

    //iterator
    using iterator = MatrixIterator<T, T&, T*>;

    constexpr size_t numberOfRows() const noexcept { return N; }
    constexpr size_t numberOfColumns() const noexcept { return M; }

    Matrix() noexcept { std::fill_n(data, N * M, T{}); }

    Matrix(const std::initializer_list<std::initializer_list<T>>& list) noexcept {
        auto it = list.begin();
        for (size_t i = 0; i < N; ++i) {
            auto row = *it++;
            auto rowSize = std::min(row.size(), M);
            std::copy(row.begin(), row.begin() + rowSize, data + i * M);
            std::fill(data + i * M + rowSize, data + (i + 1) * M, T{});
        }
    }

    Matrix(const Matrix& m) noexcept {
        std::copy_n(m.data, N * M, data);
    }

    Matrix& operator=(const Matrix& m) noexcept {
        if (&m != this) {
            std::copy_n(m.data, N * M, data);
        }
        return *this;
    }

    T operator()(size_t i, size_t j) const {
        if (i >= N || j >= M) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[i * M + j];
    }

    friend Matrix operator+(const Matrix& a, const Matrix& b) noexcept {
        Matrix r;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                r.data[i * M + j] = a.data[i * M + j] + b.data[i * M + j];
            }
        }
        return r;
    }

    // Iterator functions

    iterator begin() noexcept {
        return iterator(data);
    }

    iterator end() noexcept {
        return iterator(data + N * M);
    }

    const_iterator begin() const noexcept {
        return const_iterator(data);
    }

    const_iterator end() const noexcept {
        return const_iterator(data + N * M);
    }

    row_iterator row_begin(size_t n) noexcept {
        return row_iterator(data + (n-1) * M);
    }

    row_iterator row_end(size_t n) noexcept {
        return row_iterator(data + n * M);
    }

    col_iterator col_begin(size_t n) noexcept {
        return col_iterator(data + (n-1), M);
    }

    col_iterator col_end(size_t n) noexcept {
        return col_iterator(data + N * M + (n-1), M);
    }
};

template <typename T, size_t N, size_t M>
void printMatrix(const Matrix<T, N, M>& m, int width = 10) {
    for (size_t i = 0; i < m.numberOfRows(); ++i) {
        for (size_t j = 0; j < m.numberOfColumns(); ++j) {
            if (j != 0) {
                cout << " ";
            }
            cout << setw(width) << m(i, j);
        }
        cout << endl;
    }
}
