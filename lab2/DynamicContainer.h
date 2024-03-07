#pragma once
#include <iostream>
#include <memory>
#include "Box.h"
using namespace std;
/*
 * Exercise 3. Unique Pointers
File DynamicContainer.h:
Change the implementation of the class Pointer so that it stores pointer to dynamically allocated
Box in a unique_ptr not as a raw pointer.
Implement move semantics for Container.
 */
class Container{
    // Exercise 2: Use smart pointer.
    //instead of this Box * pbox = nullptr;
    std::unique_ptr<Box> pbox;
public:
    static bool verbose;
    Container(int content): pbox(new Box(content)){
        if(verbose) cout << "Creating Container" << endl;
        pbox->setContent(content);
    }
    Container(const Container & container): pbox(new Box{*(container.pbox)}){
        if(verbose) cout << "Creating copy of Container\n";
    }
    Container & operator=(const Container &container){
        if(this != &container) {
            if(verbose) cout << "Copying Container\n";
            *pbox = *container.pbox;
        }
        return *this;
    }

    Container(Container && container): pbox(std::move(container.pbox)){
        if(verbose) cout << "Moving Container\n";
    }

    Container & operator=(Container &&container){
        if(this != &container) {
            if(verbose) cout << "Moving Container\n";
            pbox = std::move(container.pbox);
        }
        return *this;
    }

    ~Container(){
        if(verbose) cout << "Destroying Container \n";
        //delete pbox;
    }
    friend Container operator+(const Container & p1, const Container & p2);
    friend std::ostream & operator << (std::ostream & out, const Container & p){
        return (out << " [" << p.pbox->getContent() << "] ");
    }
};

bool Container::verbose = false;

inline Container operator+(const Container & p1, const Container & p2){
    Container suma(p1.pbox->getContent() + p2.pbox->getContent());
    return suma;
}
