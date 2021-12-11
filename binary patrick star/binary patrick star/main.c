//
//  main.c
//  binary patrick star
//
//  Created by 朱季葳 on 2021/3/26.
//

#include <stdio.h>
#include "function.h"
#define maxN 1000000

int lch[maxN], rch[maxN], sz[maxN];

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%d %d", lch + i, rch + i);
        }
        Node* root = buildBinaryTree(n, lch, rch);
        Traversal(root, sz);
        for (int i = 0; i < n; i++) {
            printf("%d%c", sz[i], " \n"[i == n - 1]);
        }
        freeBinaryTree(root);
    }
}
