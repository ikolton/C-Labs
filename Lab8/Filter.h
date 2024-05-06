#ifndef FILTER_H
#define FILTER_H

#include <utility>

template<typename CIter, typename Predicate>
class FIterator{
    CIter current;
    CIter end;
    Predicate p;
public:
    FIterator(CIter start,CIter e,Predicate np):
            current(start),
            end(e),
            p(np){
        while(current != end && !p(*current)){
            ++current;
        }
    }
    FIterator& operator ++(){
        ++current;
        while(current != end && !p(*current)){
            ++current;
        }
        return *this;
    }
    auto operator* (){
        return *current;
    }
    bool operator ==(FIterator &f){
        return current==f.current && end==f.end;
    }
    bool operator !=(FIterator &f){
        return !(*this==f);
    }
};

template<typename Container, typename Predicate>
class Filter{
    Container c; // Store a copy for rvalue, or a reference for lvalue
    Predicate p;
public:
    Filter(Container&& nc, Predicate np):
            c(std::forward<Container>(nc)),
            p(np){}
    auto begin(){
        return FIterator(c.begin(),c.end(),p);
    }
    auto end(){
        return FIterator(c.end(),c.end(),p);
    }
};

template<typename Container, typename Predicate>
Filter<Container,Predicate> make_filter(Container &&c, Predicate p){
    return Filter<Container,Predicate>(std::forward<Container>(c),p);
}


#endif // FILTER_H
