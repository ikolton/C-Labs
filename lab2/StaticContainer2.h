#pragma once
#include <iostream>
#include "Box.h"

// Exercise: modify code so that appropriate constructor and operators are called using just default and delete keyword.
class Container : public Box {
public:
    static bool verbose;
    Container(int content):Box(content){};                          // implement
    Container(const Container & container) = delete;
 	Container & operator=(const Container &container) = delete;

	Container(Container && container): Box(std::move(container)){
        if(verbose) std::cout << "Container: move constructor.\n";
    };                  // enable
  	Container & operator=(Container &&container){
        if(verbose) std::cout << "Container: move assignment.\n";
        Box::operator=(std::move(container));
        return *this;
      };       // enable
    ~Container(){
        if(verbose) std::cout << "Container: destructor.\n";
    };                                      // enable

    friend Container operator+(const Container & p1, const Container & p2);
    friend std::ostream & operator << (std::ostream & out, const Container & p){
        return (out << " [" << p.getContent() << "] ");
    }
};
bool Container::verbose = false;

inline Container operator+(const Container & p1, const Container & p2){
    Container suma(p1.getContent() + p2.getContent());
    return suma;
}