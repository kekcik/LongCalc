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
    big_integer a = 23;
    big_integer b = -5;
    big_integer c = -23;
    big_integer d = 5;
    cout<<(a / b)<<endl;// == -4
    cout<<(c / d)<<endl;// == -4
    cout<<(a % b)<<endl;// == 3
    cout<<(c % d)<<endl;// == -3
    
}