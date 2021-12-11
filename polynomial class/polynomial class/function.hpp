//
//  function.hpp
//  polynomial class
//
//  Created by 朱季葳 on 2021/5/4.
//

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>

class Polynomial
{

public:
    Polynomial();
    Polynomial(const int power, const int coef[51]);
    Polynomial add( const Polynomial poly) const; // add function
    Polynomial subtract( const Polynomial poly) const; // subtract function
    Polynomial multiplication( const Polynomial poly) const; // multiplication function
    void output() const;
private:
    int coefficients[101]; // integer coefficients
    int greatestPower; // integer greatestPower
}; // end class Polynomial

#endif
