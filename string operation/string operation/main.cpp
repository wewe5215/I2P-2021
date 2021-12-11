//
//  main.cpp
//  string operation
//
//  Created by 朱季葳 on 2021/5/13.
//

#include "function.hpp"

int main() {

    int N;
    char input[100];

    int index=0;
    Str *s[100];

    cin>>N;
    for(int i=0;i<N;i++){
        cin>>input;
        s[index++]=new Str(input);
    }

    char op[3];//"si" || "is" || "s" || "i" || "e"
    /*s n m: Swap the nth string and the mth string.
     
     i n m: Insert the mth string at the tail of the nth string.

     si n m: Swap the specified strings first, and then insert.

     is n m: Insert first, and then swap the two specified strings.

     e: Exit.

     */
    while(1){
        cin>>op;
        if(op[0]=='e')break;

        int idx1,idx2;
        cin>>idx1;
        cin>>idx2;

        Str &s1=*s[idx1];
        Str &s2=*s[idx2];


        if(op[0]=='s'&&op[1]=='i'){
            s1.strSwap(s2).strInsert(s2);

        }else if(op[0]=='i'&&op[1]=='s'){
            s1.strInsert(s2).strSwap(s2);

        }else if(op[0]=='s'){
            s1.strSwap(s2);

        }else if(op[0]=='i'){
            s1.strInsert(s2);

        }
    }

    for(int i=0;i<N;i++){
        s[i]->strPrint();
        delete s[i];
    }

    return 0;
}


