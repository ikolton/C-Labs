#include <iostream>
#include <vector>
using namespace std;
/*
 *  Exercise 3.  Mixins
 Implement class template Mixins that as parameters takes any number of its base classes. Class
Mixins should inherit from all of them.
 Implement constructor that allows to initialize class with objects of corresponding types.
 using RedCircle = Mixins<Red, Circle>;
 RedCircle x(Red{}, Circle{3});
 using BlueRectangleWithNotes = Mixins<Blue, Rectangle, Note>;
 BlueRectangleWithNotes y (Blue{}, Rectangle{3,4}, Note{"Hey"});
 */

/* Colors */
class Red{
public:     static constexpr char color[] = "red";
};

class Yellow{
public:     static constexpr char color[] = "yellow";
};

class Blue{
public:     static constexpr char color[] = "blue";
};

/* Shapes*/
class Circle{
    double r=0;
public:
    Circle() = default;
    Circle(double r): r(r) {}
    double area(){ return 3.24*r*r; }
};
class Rectangle{
    double a=0, b=0;
public:
    Rectangle() = default;
    Rectangle(double a, double b) : a(a), b(b) {}
    double area(){ return a * b;}
};
/* Other Features */
class Note{
    std::vector<std::string> notes;
public:
    Note(const std::string & note){
        add(note);
    }
    void add(const std::string & note){
        notes.push_back(note);
    }
};

template<typename... Args>
class Mixins : public Args...{
public:
    Mixins(Args... args): Args(args)...{}


};

int main(){

    using RedCircle = Mixins<Red, Circle>;
    RedCircle x(Red{}, Circle{3});
    cout << x.color << " area = " << x.area() << endl;

    using BlueRectangleWithNotes = Mixins<Blue, Rectangle, Note>;
    BlueRectangleWithNotes y (Blue{}, Rectangle{3,4}, Note{"Hey"});
    y.add("Ho");
    cout << y.color << " area = " << y.area() << endl;

}