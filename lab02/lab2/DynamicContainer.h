#pragma once
#include <iostream>
#include <memory> 
#include "Box.h"
#include <memory>

class Container{
    // Exercise 2: Use smart pointer.
    std::unique_ptr<Box> pbox;
public:
    static bool verbose;
    Container(int content): pbox(std::make_unique<Box>(content)){
        if(verbose) std::cout << "Creating Container" << std::endl;
        pbox->setContent(content);
    }
    Container(const Container & container): pbox(std::make_unique<Box>(*container.pbox)){
        if(verbose) std::cout << "Creating copy of Container\n";
    }
   
    Container & operator=(const Container &container) {
        if(this != &container) {
            if(verbose) std::cout << "Copying Container\n";
            *pbox = *container.pbox;
        }
        return *this;
    }

    Container(Container && container): pbox(std::move(container.pbox)){
        if(verbose) std::cout << "Moving Container\n";
    }

    Container & operator=(Container && container){
        if(this != &container) {
            if(verbose) std::cout << "Moving Container\n";
            pbox = std::move(container.pbox);
        }
        return *this;
    } 
     

    ~Container(){
        if(verbose) std::cout << "Destroying Container \n";
    }
   

    friend Container operator+(const Container & p1, const Container & p2);
    friend std::ostream & operator << (std::ostream & out, const Container & p){

        if(p.pbox) {
            return (out << " [" << p.pbox->getContent() << "] ");
        } else {
            return out;
        }
    }
};

bool Container::verbose = false;

inline Container operator+(const Container & p1, const Container & p2) {
    Container sum(p1.pbox->getContent() + p2.pbox->getContent());
    return sum;
}
