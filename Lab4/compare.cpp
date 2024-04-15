#include <iostream>
#include <cstring>

using namespace std;

/*
 * Exercise 2. Function template overloading
Implement a function template
int compare(T a, T b)
Template function should return:
• 1 if a < b,
• -1 if b < a,
• 0 otherwise
We assume only that objects a and b are comparable using operator <.
In particular it should work for all integer and floating point types.
Overload function template compare with template that takes two pointers as function parameters
and compare pointed objects instead of pointers itself.
Implement the specializations of the function template compare for pointers to C strings: it should
compare strings lexicographically i.e. ”call” < ”car”
int a = 1, b=-6;
float y= 1.0 + 1e20 - 1e20, x = 1.0;
cout << compare(a,b) << " " << compare(b,a) << " " << compare(a,a) << endl;
cout << compare(x,y) << " " << compare(y,x) << " " << compare(x,x) << endl;
cout << compare(&a,&b) << " " << compare(&b,&a) << " " << compare(&a,&a) <<endl;
cout << compare(&x,&y) << " " << compare(&y,&x) << " " << compare(&x,&x) <<endl;
cout << compare(“Alpha”, “Alfa”) <<endl;
OUTPUT
-1 1 0
-1 1 0
-1 1 0
-1 1 0
-1
 */

template <typename T>
int compare(T a, T b){
    if(a<b) return 1;
    if(b<a) return -1;
    return 0;
}

template <typename T>
int compare(T * a, T * b){
    return compare(*a, *b);
}

template <>
int compare(const char * a, const char * b){
    if(strcmp(a,b) < 0) return 1;
    if(strcmp(b,a) < 0) return -1;
    return 0;
}

struct Rational{
    int nominator=0, denominator=1;
    friend bool operator<(const Rational & a, const Rational & b){
        return a.nominator*b.denominator < b.nominator*a.denominator;
    }
};



int main(){
    int a = 1, b=-6;
    float  y= 1.0 + 1e20 - 1e20, x = 1.0;
    Rational p{2}, q{1,4}, r{8,4};
    cout << "values\n";
    cout << compare(a,b) << " " << compare(b,a) << " " << compare(a,a) << endl;
    cout << compare(x,y) << " " << compare(y,x) << " " << compare(x,x) << endl;
    cout << compare(p,q) << " " << compare(q,p) << " " << compare(p,r) << endl;
    cout << "pointers\n";
    cout << compare(&a,&b) << " " << compare(&b,&a) << " " << compare(&a,&a) << endl;
    cout << compare(&x,&y) << " " << compare(&y,&x) << " " << compare(&x,&x) << endl;
    cout << compare(&p,&q) << " " << compare(&q,&p) << " " << compare(&p,&r) << endl;

    const char *s  = "Alpha", *t="Alfa", *t2 = "Alfa";
    cout << "C-strings\n";
    cout << compare(s,t) << " " << compare(t,s) << " " << compare(t,t)
         << " " << compare(t, t2) << " " << compare(t, "Beta") << endl;

    return 0;
}