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
    string s1, s2;
    cin >> s1 >> s2;
    big_integer a1(s1);
    big_integer a2(s2);
    big_integer c = a1 / a2;
    cout << c <<endl;
}