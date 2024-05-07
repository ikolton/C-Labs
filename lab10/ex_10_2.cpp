/*
 * Exercise 2. Tag dispatching
Implement method
 double median(Container set)
that finds median in given set. Container can be one of standard containers (list, forward_list,
vector, deque).
Use iterator tags and tag dispatching to implement two versions one for random access containers
(vector, deque) and second for general container with forward iterators (list, forward_list).
std::list<int> a{3, 2, 5, 1, 4};
cout << median(a) << endl; // 3
std::vector<int> v{3, 1, 4, 2};
cout << median(v) << endl; // 2.5
 */

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>

template <typename Container>
double median(Container set, std::random_access_iterator_tag) {
    std::sort(set.begin(), set.end());
    auto size = set.size();
    if (size % 2 == 0) {
        return (set[size / 2 - 1] + set[size / 2]) / 2.0;
    } else {
        return set[size / 2];
    }
}

template <typename Container>
double median(Container set, std::forward_iterator_tag) {
    set.sort();
    auto size = std::distance(set.begin(), set.end());
    auto mid = std::next(set.begin(), size / 2);
    if (size % 2 == 0) {
        auto prev_mid = std::prev(mid);
        return (*prev_mid + *mid) / 2.0;
    } else {
        return *mid;
    }
}

template <typename Container>
double median(Container set) {
    return median(set, typename std::iterator_traits<typename Container::iterator>::iterator_category());
}




int main() {
    std::list<int> a{3, 2, 5, 1, 4};
    std::vector<int> v{3, 1, 4, 2};
    std::cout << median(a) << std::endl; // 3
    std::cout << median(v) << std::endl; // 2.5
    return 0;
}