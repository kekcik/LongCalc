//
//  opt_vector.cpp
//  LongCalc
//
//  Created by Иван Трофимов on 28.10.16.
//  Copyright © 2016 Иван Трофимов. All rights reserved.
//

#include "opt_vector.hpp"

opt_vector::opt_vector() {
    cur_size = 0;
}

opt_vector::opt_vector(const opt_vector& other) {
    //если текущее число большое, то удалим его
    if (other.cur_size > 1) {
        big_number = other.big_number;
        other.big_number -> link++;
    } else {
        small_number = other.small_number;
    }
    cur_size = other.cur_size;
}

opt_vector::~opt_vector() {
    if (cur_size > 1 and big_number -> link != 0) {
        safe_delete();
    }
}

void opt_vector::clear() {
    if (cur_size > 1) {
        make_copy();
        big_number -> data.clear();
    }
    cur_size = 0;
}

void opt_vector::safe_delete() {
    //уменьшаем количество ссылок или удаляем
    if (big_number -> link > 1) {
        big_number -> link--;
    } else {
        delete big_number;
    }
}

void opt_vector::make_copy() {
    if (big_number -> link > 1) {
        my_vector* new_vector = new my_vector();
        new_vector -> data = big_number -> data;
        new_vector -> link = 1;
        big_number -> link--;
        std::swap(new_vector, big_number);
    }
}

opt_vector &opt_vector::operator=(opt_vector const &other) {
    if (cur_size > 1) safe_delete();
    if (other.cur_size <= 1) {
        small_number = other.small_number;
    } else {
        other.big_number -> link++;
        big_number = other.big_number;
    }
    cur_size = other.cur_size;
    return *this;
}

void opt_vector::resize(size_t new_size) {
    if (cur_size > 1) make_copy();
    if (new_size == 0) {
        //a -> s(0)
        small_number = 0;
    } else if (new_size == 1) {
        if (cur_size > 1) {
            // b -> s
            small_number = big_number -> data[0];
        } else {
            // s -> s
        }
    } else {
        if (cur_size > 1) {
            //b -> b
            big_number -> data.resize(new_size);
        } else {
            //s -> b
            uint32_t temp = small_number;
            big_number = new my_vector;
            big_number -> link = 1;
            big_number -> data.resize(new_size);
            big_number -> data[0] = temp;
        }
    }
    cur_size = new_size;
}

void opt_vector::push_back(uint32_t data) {
    if (cur_size > 1) {
        make_copy();
        big_number -> data.push_back(data);
    }
    if (cur_size == 1) {
        uint32_t temp = small_number;
        big_number = new my_vector();
        big_number -> data.resize(2);
        big_number -> data[0] = temp;
        big_number -> data[1] = data;
        big_number -> link = 1;
    }
    if (cur_size == 0) {
        small_number = data;
    }
    cur_size++;
}

void opt_vector::pop_back() {
    if (cur_size > 2) {
        make_copy();
        big_number -> data.pop_back();
    } else if (cur_size == 2) {
        make_copy();
        small_number = big_number -> data[0];
    } else if (cur_size == 0) {
        return;
    }
    cur_size--;
}

uint32_t& opt_vector::operator[](size_t index) {
    if (cur_size > 1) make_copy();
    return (cur_size > 1 ? big_number -> data[index] : small_number);
}

uint32_t const&  opt_vector::operator[](size_t index) const{
    return (cur_size > 1 ? big_number -> data[index] : small_number);
}

size_t opt_vector::size() const {
    return cur_size;
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
