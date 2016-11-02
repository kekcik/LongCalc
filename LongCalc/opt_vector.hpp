//
//  opt_vector.hpp
//  LongCalc
//
//  Created by Иван Трофимов on 28.10.16.
//  Copyright © 2016 Иван Трофимов. All rights reserved.
//

#ifndef opt_vector_hpp
#define opt_vector_hpp

#include <vector>
#include <stdio.h>
#include <stdint.h>

struct my_vector {
    std::vector<uint32_t> data;
    size_t link;
};

struct opt_vector{
public:
    opt_vector();
    opt_vector(size_t, uint32_t);
    opt_vector(const opt_vector&);
    ~opt_vector();
    void clear();
    opt_vector &operator=(opt_vector const &);
    void resize(size_t);
    void push_back(uint32_t);
    void pop_back();
    uint32_t& operator[](size_t);
    uint32_t const& operator[](size_t) const;
    size_t size() const;
private:
    union {
        my_vector * big_number;
        uint32_t small_number;
    };
    size_t cur_size;
    void safe_delete();
    void make_copy();
    
};

#endif /* opt_vector_hpp */
