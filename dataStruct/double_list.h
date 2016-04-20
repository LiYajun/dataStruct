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
double_list_pop_node(double_list_p p, d_node_p obj_node);

extern void
double_list_set_find_func(double_list_p p, BOOL(* obj_find_func)(object_p object) );

extern d_node_p
double_list_find(double_list_p p, BOOL (* obj_find_func)(object_p object));

extern uint
double_list_count(double_list_p p);

extern void
double_list_dealloc(double_list_p p);

extern d_node_p
double_list_last_node(double_list_p p);

extern d_node_p
double_list_first_node(double_list_p p);

#endif /* double_list_h */
