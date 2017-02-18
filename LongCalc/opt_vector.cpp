//
//  opt_vector.cpp
//  LongCalc
//
//  Created by Иван Трофимов on 28.10.16.
//  Copyright © 2016 Иван Трофимов. All rights reserved.
//

#include "opt_vector.hpp"
#include <iostream>
#include <cassert>

opt_vector::opt_vector(){
    small_number = opt_size = 0;
    big = false;
}

opt_vector::opt_vector(const opt_vector& other)
{
    big = other.big;
    opt_size = other.opt_size;
    if(!other.big) {
        small_number = other.small_number;
    } else {
        other.big_number->link_counter++;
        big_number = other.big_number;
    }
}

opt_vector::opt_vector(size_t sz, unsigned val) : opt_size(sz) {
    if(sz>1) {
        big = true;
        big_number = new my_vector();
        big_number->data.push_back(val);
        big_number->data.resize(sz);
        big_number->link_counter = 1;
    } else {
        big = false;
        small_number = val;
    }
}
void opt_vector::safe_delete() {
    if(big_number->link_counter > 1) {
        big_number->link_counter--;
    } else {
        delete big_number;
    }
}

void opt_vector::make_alone(){
    if(big && big_number->link_counter>1) {
        my_vector* new_vector = new my_vector();
        big_number->link_counter--;
        new_vector->data = big_number->data;
        new_vector->link_counter = 1;
        std::swap(new_vector, big_number);
    }
}

opt_vector::~opt_vector() {
    if(big && big_number -> link_counter > 0) {
        safe_delete();
    }
}

void swap(opt_vector& a, opt_vector& b) {
    swap(a.big, b.big);
    swap(a.opt_size, b.opt_size);
    swap(a.big_number, b.big_number);
}

opt_vector &opt_vector::operator=(opt_vector const &other) {
    opt_vector r(other);
    swap(*this, r);
    return *this;
}

unsigned& opt_vector::operator[](size_t index) {
    assert(index<opt_size);
    make_alone();
    return (big) ? big_number->data[index] : small_number;
}

unsigned const& opt_vector::operator[](size_t index) const {
    assert(index<opt_size);
    return (big) ? big_number->data[index] : small_number;
}

size_t opt_vector::size() const {
    return opt_size;
}

unsigned &opt_vector::back() {
    make_alone();
    return (big) ? big_number->data.back() : small_number;
}

unsigned const &opt_vector::back() const  {
    return (big) ? big_number->data.back() : small_number;
}

void opt_vector::resize(size_t new_size) {
    if (big) {
        make_alone();
        big_number -> data.resize(new_size);
    } else if(new_size > 1){
        unsigned temp = small_number;
        big_number = new my_vector();
        big_number -> data.resize(new_size, 0);
        big_number -> link_counter = 1;
        if (opt_size != 0)
            big_number -> data[0] = temp;
        big = true;
    } else if (opt_size == 0) {
        small_number = 0;
    }
    opt_size = new_size;
}


void opt_vector::push_back(unsigned a) {
    if (big) {
        make_alone();
        big_number -> data.push_back(a);
    } else if (opt_size == 1){
        unsigned temp = small_number;
        big_number = new my_vector();
        big_number -> data.emplace_back(temp);
        big_number -> data.emplace_back(a);
        big_number->link_counter = 1;
        big = true;
    } else {
        small_number = a;
    }
    opt_size++;
}

void opt_vector::pop_back() {
    if (big) {
        make_alone();
        big_number -> data.pop_back();
    } else if (opt_size == 0) {
        throw "Zero pop back";
    }
    opt_size--;
}


void opt_vector::clear() {
    if (big) {
        make_alone();
        big_number -> data.clear();
    }
    opt_size = 0;
}

bool opt_vector::empty() {
    return opt_size == 0;
}


//#include <iostream>
//using namespace :: std;
//int main () {
//    opt_vector a;
//    opt_vector b;
//    a.push_back(111);
//    cout << "mark: add(111)\n";
//    cout << a.size() << endl;
//    cout << a[0] << endl;
//    cout << (a.cur_size > 1? "big" : "small") << endl << endl;
//    a.push_back(222);
//    cout << "mark: add(222)\n";
//    cout << a.size() << endl;
//    cout << a[0] << ' ' << a[1] << endl;
//    cout << (a.cur_size > 1? "big" : "small") << endl << endl;
//    a.pop_back();
//    cout << "mark: pop()\n";
//    cout << a.size() << endl;
//    cout << a[0] << ' ' << endl;
//    cout << (a.cur_size > 1? "big" : "small") << endl << endl;
//    a.pop_back();
//    cout << "mark: pop()\n";
//    cout << a.size() << endl;
//    cout << (a.cur_size > 1? "big" : "small") << endl << endl;
//    cout << "mark: add(444)\n";
//    a.push_back(444);
//    cout << a.size() << endl;
//    cout << a[0] << ' ' << endl;
//    cout << (a.cur_size > 1? "big" : "small") << endl << endl;
//    cout << "mark: add(555)\n";
//    a.push_back(555);
//    cout << a.size() << endl;
//    cout << a[0] << ' ' << a[1] << endl;
//    cout << (a.cur_size > 1? "big" : "small") << endl << endl;
    
    
//}
