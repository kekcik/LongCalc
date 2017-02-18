//
//  opt_vector.cpp
//  LongCalc
//
//  Created by Иван Трофимов on 28.10.16.
//  Copyright © 2016 Иван Трофимов. All rights reserved.
//

#include "opt_vector.hpp"

opt_vector::opt_vector() : small_number(0), cur_size(0), is_big(false) {}

opt_vector::opt_vector(const opt_vector& other) : cur_size(other.cur_size), 
                                                is_big(other.is_big)
                                                 {
    if(!other.is_big) {
        small_number = other.small_number;
    } else {
        other.big_number->link_counter++;
        big_number = other.big_number;
    }
}

opt_vector::opt_vector(size_t sz, unsigned val) : cur_size(sz) {
    if(sz>1) {
        is_big = true;
        big_number = new my_vector();
        big_number->data.push_back(val);
        big_number->data.resize(sz);
        big_number->link_counter = 1;
    } else {
        is_big = false;
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
    if(is_big && big_number->link_counter>1) {
        my_vector* new_vector = new my_vector();
        big_number->link_counter--;
        new_vector->data = big_number->data;
        new_vector->link_counter = 1;
        std::swap(new_vector, big_number);
    }
}

opt_vector::~opt_vector() {
    if(is_big && big_number -> link_counter > 0) {
        safe_delete();
    }
}

void swap(opt_vector& a, opt_vector& b) {
    swap(a.is_big, b.is_big);
    swap(a.cur_size, b.cur_size);
    swap(a.big_number, b.big_number);
}

opt_vector &opt_vector::operator=(opt_vector const &other) {
    opt_vector r(other);
    swap(*this, r);
    return *this;
}

unsigned& opt_vector::operator[](size_t index) {
    assert(index<cur_size);
    make_alone();
    return (is_big) ? big_number->data[index] : small_number;
}

unsigned const& opt_vector::operator[](size_t index) const {
    assert(index<cur_size);
    return (is_big) ? big_number->data[index] : small_number;
}

size_t opt_vector::size() const {
    return cur_size;
}

unsigned &opt_vector::back() {
    make_alone();
    return (is_big) ? big_number->data.back() : small_number;
}

unsigned const &opt_vector::back() const  {
    return (is_big) ? big_number->data.back() : small_number;
}

void opt_vector::resize(size_t new_size) {
    if (is_big) {
        make_alone();
        big_number -> data.resize(new_size);
    } else if(new_size > 1){
        unsigned temp = small_number;
        big_number = new my_vector();
        big_number -> data.resize(new_size, 0);
        big_number -> link_counter = 1;
        if (cur_size != 0)
            big_number -> data[0] = temp;
        is_big = true;
    } else if (cur_size == 0) {
        small_number = 0;
    }
    cur_size = new_size;
}


void opt_vector::push_back(unsigned a) {
    if (is_big) {
        make_alone();
        big_number -> data.push_back(a);
    } else if (cur_size == 1){
        unsigned temp = small_number;
        big_number = new my_vector();
        big_number -> data.emplace_back(temp);
        big_number -> data.emplace_back(a);
        big_number->link_counter = 1;
        is_big = true;
    } else {
        small_number = a;
    }
    cur_size++;
}

void opt_vector::pop_back() {
    if (is_big) {
        make_alone();
        big_number -> data.pop_back();
    } else if (cur_size == 0) {
        throw "Zero pop back";
    }
    cur_size--;
}


void opt_vector::clear() {
    if (is_big) {
        make_alone();
        big_number -> data.clear();
    }
    cur_size = 0;
}

bool opt_vector::empty() {
    return cur_size == 0;
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
