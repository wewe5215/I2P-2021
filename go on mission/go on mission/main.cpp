//
//  main.cpp
//  go on mission
//
//  Created by 朱季葳 on 2021/5/14.
//

#include <iostream>
#include "function.hpp"

using namespace std;

int main()
{
    int n; cin >> n;
    // initialize health condition
    BigInt hi, kaminari, kedamono;
    cin >> hi; kaminari = kedamono = hi;
    // go on mission
    solution(hi, kaminari, kedamono, n);
    // output result
    cout << hi << endl;
    cout << kaminari << endl;
    cout << kedamono << endl;
}
