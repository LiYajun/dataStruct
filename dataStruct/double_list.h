//
//  double_list.h
//  dataStruct
//
//  Created by li yajun on 16/4/5.
//  Copyright © 2016年 li yajun. All rights reserved.
//

#ifndef double_list_h
#define double_list_h

#include <stdio.h>
#include "global_types.h"
#include "_node.h"
 
typedef struct _double_list * double_list_p;

extern double_list_p
double_list_alloc(void(*obj_free)(object_p object));


extern BOOL
double_list_insert_next(double_list_p p, d_node_p obj_node, object_p obj);

extern BOOL
double_list_insert_pre(double_list_p p, d_node_p obj_node, object_p obj);

extern BOOL
double_list_insert_last(double_list_p p, object_p obj);

extern BOOL
double_list_insert_first(double_list_p p, object_p obj);

extern object_p
double_list_pop_at(double_list_p p, d_node_p obj_node);

#endif /* double_list_h */
