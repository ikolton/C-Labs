#include <iostream>
#include <algorithm>
#include <memory>
#include "MyString.h"
using namespace std;

/*
 * Exercise 4. Shared Pointers
File String.h: Implement a class String that uses copy-on-change design pattern.
Use shared_ptr to store pointer to dynamically allocated object of MyString (or std::string).
See comments in the code for more details.
 */

class String{
   using string = emcpp::MyString;
//    using string = std::string;

    std::shared_ptr<string> pstr;


public:
    /// creates an empty string
    String(){
        pstr = std::make_shared<string>();
    };
    /// copy C-string
    String(const char * str) {
        pstr = std::make_shared<string>(str);
    };
    /// no copy
    String(const String & s){
        pstr = s.pstr;
    };
    /// no copy
    String operator=(const String & s){
        pstr = s.pstr;
        return *this;
    };
    /// makes a copy of a string if it has more than one reference.
    void set(int index, char ch){
        if(pstr.use_count() > 1){
            pstr = std::make_shared<string>(*pstr);
        }
        (*pstr)[index] = ch;
    };
    /// no copy
    char get(int index) const{
        return (*pstr)[index];
    };
    /// creates a new string only if both strings are non empty
    friend String operator+(String a, String b){
        if(b.pstr->empty()) return a;
        if(a.pstr->empty()) return b;
        return {(std::string(a.pstr->c_str()) + b.pstr->c_str()).c_str()};
    };
    friend std::ostream & operator<< (std::ostream & out, String s){
        return out << *s.pstr;
    };
};
