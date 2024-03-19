#include <iostream>
#include <vector>
#include <list>
#include <deque>
using namespace std;
/*
 * Implement a function template
 OutContainer<T,Alloc> selectIf(InContainer<T,Alloc> c, Predicate p);
It should return container that contains all elements from container c for which predicate p returns
true.
Template parameters are
• OutContainer<T, Alloc> - template with two parameters that
• T – the type of the elements in the container
• Alloc – the type of the allocator
• InContainer<T, Alloc> – template with two parameters
• Predicate – the type of function or functional object that takes one argument of type T and
returns bool.
OutContainer, InContainer can be any of standard sequence containers e.g. vector, list, deque.
bool biggerThan5(int x){ return x>5; }
...
std::vector<int> v={1, 2, 13, 4, 5, 54};
std::list<int> result = selectIf<std::list>(v, biggerThan5);
// result should contain 13 and 54
 */

bool biggerThan5(int x){ return x>5; }

template <template<typename, typename> class OutContainer, template<typename, typename> class InContainer, typename T, typename Alloc, typename Predicate>
OutContainer<T, Alloc> selectIf(const InContainer<T, Alloc>& c, Predicate p) {
    OutContainer<T, Alloc> result;
    std::copy_if(c.begin(), c.end(), std::back_inserter(result), p);
    return result;
}

int main(){
    auto print = [](auto v) {
        for(auto x: v) cout << x << " ";
        cout << endl;
    };

    std::vector<int> v={1, 2, 13, 4, 5, 54};
    std::list<int> result = selectIf<std::list>(v, biggerThan5);
    print(result);  //  13 54

    auto result2 = selectIf<std::deque>(v, [](int x)->bool{ return x%2; } );
    print(result2); //  1 13 5

    auto result3 = selectIf<std::vector>(result2, biggerThan5);
    print(result3); //  13
    return 0;
}