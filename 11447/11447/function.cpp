//
//  function.cpp
//  11447
//
//  Created by 朱季葳 on 2021/6/2.
//

#include "function.hpp"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
namespace oj
{
void insert(std::map<int,String> &ma,int key,const std::string &str)
{
    
    auto found=ma.find(key);
    std::string new_elem;
    if(found==ma.cend())
    {
        new_elem=str;
        ma.insert(pair<int, String>(key,String(new_elem)));
    }
    else
    {
        new_elem=str+found->second.str;
        ma.erase(found);//clear all thing
        ma.insert(pair<int, String>(key,String(new_elem)));
    }
    
}
void output(const std::map<int,String> &ma,int begin,int end)
{
    
    for(auto i:ma)
    {
        if(i.first>=begin&&i.first<=end)
        cout << i.second <<' ';
    }
}
void erase(std::map<int,String> &ma,int begin,int end)
{
    for(int i=begin;i<=end;i++)
    {
        ma.erase(i);
    }
}

std::ostream& operator<<(std::ostream &os,const std::map<int,String> & str)
{
    for(auto i:str)
        os<< i.second <<' ';
    return os;
}

}
