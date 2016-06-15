//
//  main.cpp
//  plusi
//
//  Created by Иван Трофимов on 09.06.16.
//  Copyright © 2016 Иван Трофимов. All rights reserved.
//
#include <iostream>
#include <string>
#include <stdio.h>
#include "big_integer.h"
using namespace std;
int main () {
    int kol = 0;
    int p = 0;
    int a = -5;
    int b = 0xaa;
    big_integer aa(a);
    big_integer bb(b);
    for (int i = -65; i < 65; i++)
    {
        kol++;
        if (~i == ~big_integer(i)) p++;
    }
    
    cout << kol << " TOTAL TESTS\n";
    cout <<  p  << " PASSED\n";
}