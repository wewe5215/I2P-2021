//
//  function.cpp
//  only children make choice
//
//  Created by 朱季葳 on 2021/5/18.
//

#include "function.hpp"
Animal::Animal(Zoo *zoo, string name)
{
    belong=zoo;
    belong->born(name);
    species=name;
    legs=4;
}
Dog::Dog(Zoo *zoo):Animal(zoo, "Dog"){}
Dog::~Dog(){}//by inheritance
Cat:: Cat(Zoo *zoo):Animal(zoo, "Cat"){}
Cat::~Cat(){}
Caog:: Caog(Zoo *zoo):Dog(zoo),Cat(zoo),Animal(zoo, "Caog"){}
void Caog:: barking()
{
    cout << "woof!woof!meow!\n";
    
}
void Caog:: carton()
{
    Cat::carton();
}
void Caog:: throwBall()
{
    Dog:: throwBall();
}
Caog:: ~Caog(){}
