#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

/*
 * Exercise 3.  Function Objects (Functors)
Implement class Printer that for given std::ostream, prefix and postfix will define unary functor that
for argument x (of any type) will output to stream x surrounded by prefix na postfix.
 e.g.
 Printer printer(std::cout,  "[ ", " ] " );
 printer("hello");  // [ hello ]
 printer(5);
            //
 [ 5 ]
 */
class Printer {
private:
    std::ostream& os;
    const std::string prefix;
    const std::string postfix;

public:
    // Constructor
    Printer(std::ostream& _os, std::string  _prefix, std::string  _postfix)
            : os(_os), prefix(std::move(_prefix)), postfix(std::move(_postfix)) {}

    // Overloaded function call operator
    template <typename T>
    void operator()(const T& x) const {
        os << prefix << x << postfix;
    }
};

int cmain(){
    /// Creates unary functor that takes one argument x (of any type)
    /// and outputs to given stream x surrounded by given prefix na postfix
    /// e.g. in the following  [ x ]
    /// Hint: define function template.
    Printer printer(std::cout,  "[ ", " ] " );
    printer("hello");    // [ hello ]
    std::cout << "\nv = ";
    std::vector<int> v = {1, 2, 3, 4};
    std::for_each(v.begin(), v.end(), printer);  // v = [ 1 ] [ 2 ] [ 3 ] [ 4 ]

    std::ofstream file("myFile.txt");
    Printer filePrinter(file, "- ", "\n");
    filePrinter(5);
    filePrinter("My text");
    return 0;
}
/** myFile.txt
- 5
- My text
*/