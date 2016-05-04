//
//  binary_tree.h
//  dataStruct
//
//  Created by li yajun on 16/5/3.
//  Copyright © 2016年 li yajun. All rights reserved.
//
//树的深度
#ifndef binary_tree_h
#define binary_tree_h

#include <stdio.h>
#include "_node.h"

typedef struct _btree* btree_p;
typedef   obj_order (*compare_func_p)(object_p obj1, object_p obj2);
typedef   void (*obj_free_p)(object_p object);
struct _btree{
    
    btree_node_p  root; /*根节点*/
    uint          maxdepth;
    compare_func_p   compare_func ;
    obj_free_p   obj_free;
};


extern btree_p
btree_alloc(obj_order (*find_fuc)(object_p obj1, object_p obj2), void (*obj_free)(object_p object) );



extern object_p
find_obj(object_p outside_obj, btree_p p);

#endif /* binary_tree_h */
