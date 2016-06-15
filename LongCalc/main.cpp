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
    int a = 0x55;
    int b = 0xaa;
    big_integer aa(a);
    big_integer bb(b);
    cout << (a | b) <<endl;
    cout << (aa | bb) <<endl;
    /*
    for (int i = -65; i <= 65; ++i)
    {
        for (int j = -65; j <= 65; ++j)
        {
            kol += 1;
            if ((i & j) == (big_integer(i) & big_integer(j))) cout<<"TRUE  "; else cout<<"FALSE ";
            cout << (i & j) << ' ';
            cout << (big_integer(i) & big_integer(j)) << endl;
            if ((i & j) == (big_integer(i) & big_integer(j))) p++;
        }
    }
    /*
    /*
    cout << a | a << endl;
    cout << aa | aa << endl;
    
    cout << a ^ a << endl;
    cout << aa ^ aa << endl;
     */
    cout << kol << " TOTAL TESTS\n";
    cout <<  p  << " PASSED\n";
}