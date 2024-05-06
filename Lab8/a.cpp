//#include <iostream>
//#include <vector>
//
//template <typename Container, typename Predicate>
//class Filter {
//public:
//    Filter(Container& container, Predicate pred) : container(container), pred(pred) {}
//
//    class iterator {
//    public:
//        iterator(typename Container::iterator iter, typename Container::iterator end, Predicate pred)
//                : iter(iter), end(end), pred(pred) {
//            // Advance to the first valid element
//            while (iter != end && !pred(*iter)) {
//                ++iter;
//            }
//        }
//
//        iterator& operator++() {
//            do {
//                ++iter;
//            } while (iter != end && !pred(*iter));
//            return *this;
//        }
//
//        bool operator!=(const iterator& other) const {
//            return iter != other.iter;
//        }
//
//        auto operator*() const {
//            return *iter;
//        }
//
//    private:
//        typename Container::iterator iter;
//        typename Container::iterator end;
//        Predicate pred;
//    };
//
//    iterator begin() {
//        return iterator(container.begin(), container.end(), pred);
//    }
//
//    iterator end() {
//        return iterator(container.end(), container.end(), pred);
//    }
//
//private:
//    Container& container;
//    Predicate pred;
//};
//
//template <typename Container, typename Predicate>
//Filter<Container, Predicate> make_filter(Container&& container, Predicate&& pred) {
////    return Filter<Container, Predicate>(container, pred);
//    return Filter<Container, Predicate>(std::forward<Container>(container), std::forward<Predicate>(pred));
//}
//
//int main() {
//    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 23};
//
//    auto isEven = [](int n) { return n % 2 == 0; };
//
//    Filter filter(v, isEven);
//    Filter filter2(filter, [](int n) { return n % 2 == 1; });
////    auto filter3 = make_filter(filter2, [](int n) { return n % 3 == 0; });
//
//    for (auto num : filter2) {
//        std::cout << num << " ";
//    }
//    std::cout << std::endl;
//
//    return 0;
//}
