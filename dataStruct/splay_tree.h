//
//  splay_tree.h
//  dataStruct
//
//  Created by li yajun on 16/5/6.
//  Copyright © 2016年 li yajun. All rights reserved.
//  伸展树

#ifndef splay_tree_h
#define splay_tree_h

#include <stdio.h>
/* pointer => root node of the tree */
struct node;
typedef struct node *TREE;
typedef struct node *position;
typedef int ElementTP;

struct node {
    position parent;
    ElementTP element;
    position lchild;
    position rchild;
};
TREE find_value(TREE, ElementTP);
position insert_value(TREE, ElementTP);

#endif /* splay_tree_h */
