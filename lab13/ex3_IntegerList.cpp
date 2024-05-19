
#include <type_traits>

#include <iostream>
#include <iomanip>

/*
 *  Implement
• variadic class template IntegerList, that can “store” integer values as template arguments,
 • template class getInt<index, IntegerList> that turns element with a given index for the
IntegerList,
 • template class Join<IntegerList1, IntegerList2> that joins two IntegerLists,
• template class IsSorted<IntegerList> that checks if arguments of IntegerList are sorted,
 • template class Max<IntegerList> that finds maximal element in given list of integers.
 In class IntegerList implement static constexpr functions:
 • get(int index) that returns with a given index for the IntegerList,
 • max()  that finds maximal element in the IntegerList.
 */

template <int... Ints>
class IntegerList {
public:
    static constexpr int get(int index) {
        constexpr int arr[] = {Ints...};
        return arr[index];
    }

    static constexpr int max() {
        constexpr int arr[] = {Ints...};
        int max_val = arr[0];
        for (size_t i = 1; i < sizeof...(Ints); ++i) {
            if (arr[i] > max_val) {
                max_val = arr[i];
            }
        }
        return max_val;
    }
};

template <size_t I, typename T>
struct getInt;

template <size_t I, int First, int... Rest>
struct getInt<I, IntegerList<First, Rest...>> : getInt<I - 1, IntegerList<Rest...>> {};

template <int First, int... Rest>
struct getInt<0, IntegerList<First, Rest...>> {
    static constexpr int value = First;
};

template <typename, typename>
struct Join;

template <int... Ints1, int... Ints2>
struct Join<IntegerList<Ints1...>, IntegerList<Ints2...>> {
    using type = IntegerList<Ints1..., Ints2...>;
};

template <typename>
struct IsSorted;

template <int First, int Second, int... Rest>
struct IsSorted<IntegerList<First, Second, Rest...>> {
    static constexpr bool value = First <= Second && IsSorted<IntegerList<Second, Rest...>>::value;
};

template <int First>
struct IsSorted<IntegerList<First>> {
    static constexpr bool value = true;
};

template <typename>
struct Max;

template <int... Ints>
struct Max<IntegerList<Ints...>> {
    static constexpr int value = IntegerList<Ints...>::max();
};

template<int... Ints>
std::ostream& operator<<(std::ostream& os, const IntegerList<Ints...>&) {
    ((os << Ints << ' '), ...);
    return os;
}

using namespace std;
int main() {

    using listA = 	IntegerList<5, -1, 5, 2, 1>;
    using listB =   IntegerList<1, 4, 6, 9>;
    cout << "List A : " << listA() << endl;
    cout << "List B : " << listB() << endl;

    cout << "A[1] = " << getInt<1, listA>::value << endl;
    cout << "B[3] = " << listB::get(3) << endl;
    static_assert( getInt<1, listA>::value == -1 );
    static_assert( listB::get(3) == 9 );
    static_assert( listB::get(1) == 4 );

    cout << boolalpha;
    cout << "Is A sorted? " << IsSorted<listA>::value << endl;
    cout << "Is B sorted? " << IsSorted<listB>::value << endl;

    using listC = Join<listA, listB>::type;

    cout << "List C : " << listC() << endl;
    cout << Max<listC>::value << endl;
    cout << listC::max() << endl;
    static_assert(listC::max() == 9 );
    static_assert(listA::max() == 5 );

}