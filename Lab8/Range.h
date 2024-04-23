
/*
 * Exercise 1. Range
Implement class Range that defines range for range based loop.
Range( start, stop, step) defines range [start, start+step, start+2*step, …, stop).
It should provide begin and end methods and iterator that goes from start to stop with given step.
By default step=1 and start = 0.
for( auto x : Range<int>(1, 9, 2) )
 cout << x <<” “; // 1 3 5 7
for( auto x : Range<double>(1, 5))
 cout << x << “, “; // 1, 2, 3, 4,
for( auto x : Range<int>(7) )
 cout << x << “ “; // 0 1 2 3 4 5 6
for( auto x : make_range(1.0, 9.0, 1.5) )
 cout << x << “ “; // 1 2.5 4 5.5 7 8.5
 */
#ifndef LAB6_RANGE_H
#define LAB6_RANGE_H

#include <iterator>

template <typename T>
class Range {
private:
    T start, stop, step;

public:
    Range(T start_, T stop_, T step_ = 1) : start(start_), stop(stop_), step(step_) {}

    Range(T stop_) : start(0), stop(stop_), step(1) {}

    class iterator {
    private:
        T current;
        T step;
        T stop;

    public:
        using pointer = T *;
        using reference = T &;

        iterator(T current_, T step_, T stop_) : current(current_), step(step_), stop(stop_) {}

        reference operator*() { return current; }

        pointer operator->() { return &current; }

        iterator &operator++() {
            current += step;
            if (current > stop) {
                current = stop;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator &other) const { return current == other.current; }

        bool operator!=(const iterator &other) const { return !(*this == other); }
    };

    iterator begin() { return iterator(start, step, stop); }

    iterator end() { return iterator(stop, step, stop); }
};

template <typename T>
Range<T> make_range(T start, T stop, T step = 1) {
    return Range<T>(start, stop, step);
}

//for stop only
template <typename T>
Range<T> make_range(T stop) {
    return Range<T>(stop);
}

#endif //LAB6_RANGE_H

