/*
 * Exercise 1. SFINAE, enable_if & if constexpr
Implement template classes that use SFINAE to detect during compilation:
• hasSize<T> - if given type T has method size()
• hasValueType<T> - if given type T has member type value_type
cout << hasSize< int >::value << endl; // false
cout << hasSize< vector<int> >::value << endl //true
cout << hasValueType< int >::value << endl; // false
cout << hasValueType< vector<int> >::value << endl //true
Implement template function
 size_t getSize(const T & x)
that:
• returns x.size() * sizeof(T::value_type) if T has method size and member type value_type,
• sizeof(x) otherwise.
Make two versions in separate namespaces to implement getSize function:
• v1 – use enable_if,
• v2 – use if constexpr
std::vector<int> v{1,2,3,4,5};
cout << v1::getSize(5) << endl; // 4
cout << v1::getSize(v) << endl; // 20
cout << v2::getSize(5) << endl; // 4
cout << v2::getSize(v) << endl; // 20
 */


#include <type_traits>
#include <vector>
#include <iostream>

template <typename T, typename = void>
struct hasSize : std::false_type {};

template <typename T>
struct hasSize<T, std::void_t<decltype(std::declval<T>().size())>> : std::true_type {};

template <typename T, typename = void>
struct hasValueType : std::false_type {};

template <typename T>
struct hasValueType<T, std::void_t<typename T::value_type>> : std::true_type {};

namespace v1 {
    template <typename T>
    typename std::enable_if<hasSize<T>::value && hasValueType<T>::value, size_t>::type
    getSize(const T& x) {
        return x.size() * sizeof(typename T::value_type);
    }

    template <typename T>
    typename std::enable_if<!hasSize<T>::value || !hasValueType<T>::value, size_t>::type
    getSize(const T& x) {
        return sizeof(x);
    }
}

namespace v2 {
    template <typename T>
    size_t getSize(const T& x) {
        if constexpr (hasSize<T>::value && hasValueType<T>::value) {
            return x.size() * sizeof(typename T::value_type);
        } else {
            return sizeof(x);
        }
    }
}

int main() {
    std::vector<int> v{1,2,3,4,5};

    std::cout << v1::getSize(5) << std::endl; // 4
    std::cout << v1::getSize(v) << std::endl; // 20
    std::cout << v2::getSize(5) << std::endl; // 4
    std::cout << v2::getSize(v) << std::endl; // 20

    return 0;
}