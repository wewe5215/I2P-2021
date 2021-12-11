//
//  function.cpp
//  encoding and decoding
//
//  Created by 朱季葳 on 2021/5/17.
//

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "function.hpp"

void RleCodec::encode()
{
    
    std::string ans="";
    int q=0;
    int cnt=0;
    char prev=' ';
    ans.clear();
//   std::cout<<"test:"<<code_str<<std::endl;
    
     for(char c: code_str)
    {
        

        if(prev!=c&&q==1)//notice the first word
        {
//            std::cout<<cnt<<std::endl;
            if(cnt<=26)
            {
               
                ans=ans+'Q'+char('A'+cnt-1)+prev;
//                std::cout<<"test:"<<ans<<std::endl;
                cnt=0;
                prev='\0';

            }
            else
                
            {
                
                while(cnt>26)
                {
                    ans=ans+"QZ"+prev;
                    cnt-=26;
                }
               
                ans=ans+'Q'+char('A'+cnt-1)+prev;
                cnt=0;
                prev='\0';
                
            }
            
        }
        cnt++;
        prev=c;
        q=1;
        
    }
    char num='A'+cnt-1;
    if(cnt<=26)ans=ans+'Q'+num+prev;
    else
    {
        while(cnt>26)
        {
            ans=ans+"QZ"+prev;
            cnt-=26;
        }
        
        ans=ans+'Q'+char('A'+cnt-1)+prev;
        
    }
    code_str=ans;
    encoded=true;
    /*  std::string s = "";
        char c = ' ';                                 //c 同樣的字
        int num = 0;
        code_str += ' ';                              //要處理最後一組
        for(char u:code_str)
            if(u==c || num==0) num++, c = u;         //num < 'A' 處理最開始
            else{
                while(num>=26) s = s + "QZ" + c, num -= 26;
                if(num) s = s + 'Q' + char('A'+num-1) + c;
                num = 1, c = u;
            }
        code_str = s, encoded = true;*/
}
void RleCodec::decode()
{
    std::stringstream os;
    std::string int_str;
    char q = 'A';
    char number = ' ';
    int cnt = 0;
    for (auto c : code_str)
    {
        if (q=='A')
        {
            q = c;
        }
        else if(number == ' ')
        {
            number = c;
        }
        else
        {
            int_str.push_back(c);
            int cnt = 0;
            cnt = number - 'A' +1;
            for (int i=0; i<cnt; ++i)os << c;
            int_str.clear();
            number = ' ';
            q = 'A';
        }
    }

    code_str = os.str();
    encoded = false;
}
