//
//  main.cpp
//  matrix
//
//  Created by 朱季葳 on 2021/5/19.
//

#include <iostream>
#include "function.hpp"

using namespace std;

int main()
{
    int matrix_size;
    cin>>matrix_size;

    Matrix a(matrix_size);
    cin>>a;

    cout<<endl;
    cout<<a.clockwise90().clockwise90()<<endl;
    cout<<a<<endl;

    return 0;
} // end main
