//
//  function.h
//  maxmax tree operation
//
//  Created by 朱季葳 on 2021/4/14.
//

#ifndef function_h
#define function_h

#include <stdio.h>
struct Node {
    int id;
    struct Node *next;
};

struct Graph {
    int vertices_num;
    struct Node **adjLists;
};

struct Graph* createGraph(int n);
void addEdge(struct Graph* g, int u, int v);
int findMax(struct Graph*  g, int now, int pre);
void freeGraph(struct Graph* g);
#endif /* function_h */
