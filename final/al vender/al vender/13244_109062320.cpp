//
//  main.cpp
//  al vender
//
//  Created by 朱季葳 on 2021/6/25.
//

#include <iostream>
#include <set>
using namespace std;
struct commodity
{
    int price;
    int weight;
    commodity(int weight,int price):weight(weight),price(price){}
};
struct mycompare1
{
    bool operator() (const commodity& lhs, const commodity& rhs) const
    {
        return  lhs.weight<rhs.weight;
        
    };
};
struct mycompare2
{
    bool operator() (const commodity& lhs, const commodity& rhs) const
    {
        return  lhs.price<rhs.price;
        
    };
    
};
set<commodity,mycompare1>by_weight;
set<commodity,mycompare2>by_price;
int main(int argc, const char * argv[])
{
    int n=0;
    cin>>n;
    int price;
    int weight;
    for(int i=0;i<n;i++)
    {
        cin>>weight>>price;
        by_weight.insert(commodity(weight,price));
        by_price.insert(commodity(weight,price));
                         
    }
    int q=0;
    cin>>q;
    for(int i=0;i<q;i++)
    {
        int type;
        cin>>type;
        if(type==1||type==2)
        {
            cin>>weight>>price;
            if(type==1)
            {
                by_weight.insert(commodity(weight,price));
                by_price.insert(commodity(weight,price));
                
            }
            else
            {
                if(by_weight.find(commodity(weight,price))==by_weight.end())
                {
                    cout<<"No Item"<<endl;
                }
                else
                {
                    cout<<"OK"<<endl;
                    
                    auto it2=by_price.find(commodity(weight,price));
                    auto it=by_weight.find(commodity(it2->weight,it2->price));
                    //cout<<weight<<price<<endl;
//                    cout<<it->weight<<" "<<it->price<<endl;
//                    cout<<it2->weight<<" "<<it2->price<<endl;
                    by_weight.erase(it);
                    by_price.erase(it2);
                }
            }
        }
        else
        {
            if(type==3)
            {
                cin>>weight;
                auto it=by_weight.begin();
                auto it2=by_price.find(commodity(it->weight,it->price));
                if(it->weight>=weight)
                {
                    
                    cout<<"OK"<<" ";
                    cout<<it->weight<<" "<<it->price<<endl;
                    by_weight.erase(it);
                    by_price.erase(it2);
                }
                else
                {
                    cout<<"No Item"<<endl;
                }
            }
            else if(type==4)
            {
                cin>>price;
                auto it=by_price.begin();
                auto it2=by_weight.find(commodity(it->weight,it->price));
                if(it->price<=price)
                {
                    cout<<"OK"<<" ";
                    cout<<it->weight<<" "<<it->price<<endl;
                    by_price.erase(it);
                    by_weight.erase(it2);
                }
                else
                {
                    cout<<"No Item"<<endl;
                }
            }
        }
    }
    
    return 0;
}
