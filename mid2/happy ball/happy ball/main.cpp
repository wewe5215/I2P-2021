//
//  main.cpp
//  happy ball
//
//  Created by 朱季葳 on 2021/5/20.
//

#include <iostream>
#include "function.hpp"
using namespace std;
int main() {
    /* I/O optimization */
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//加速輸入輸出
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        int *arr = new int[n + 1];
        for(int i=1;i<=n;i++)    cin >> arr[i];
        
        int q;
        cin >> q;
        Operation *ops = new Operation[q + 1];
        for(int i=1;i<=q;i++) {
            cin >> ops[i].type;
            if(ops[i].type == 2)    cin >> ops[i].d;
        }

        ContainerBase *solver = create(n, arr, q, ops);
        for(int i=1;i<=q;i++) {
            if(ops[i].type == 1)
                cout << solver->print() << '\n';
            else if(ops[i].type == 2)
                solver->move(ops[i].d);
            else
                solver->remove();
        }

        delete[] arr;
        delete[] ops;
        delete solver;
    }
    return 0;
}
