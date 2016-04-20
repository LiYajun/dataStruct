//
//  basic_stack.c
//  dataStruct
//
//  Created by li yajun on 16/4/20.
//  Copyright © 2016年 li yajun. All rights reserved.
//

#include "basic_stack.h"
#include <assert.h>

extern basic_stack_p
basic_stack_alloc( void(*obj_free)(object_p obj) ){
    basic_stack_p p = NULL;
    assert(obj_free!= NULL);
    p =  (basic_stack_p)double_list_alloc( obj_free);
    return p;
}

extern BOOL
basic_stack_push(basic_stack_p p, object_p obj) {
    
   BOOL result = double_list_insert_last(p, obj);
    return  result;
}

extern object_p
basic_stack_pop(basic_stack_p p ) {
    
    object_p obj = NULL;
    d_node_p node =  double_list_last_node(p);
    if(node == NULL) {
        return NULL;
    }
    obj = double_list_pop_node(p, node);
    
    return  obj;
}
extern object_p
basic_stack_peek(basic_stack_p p) {
    object_p obj = NULL;
    d_node_p node = double_list_last_node(p);
    if(node == NULL) {
        return  NULL;
    }
    obj = d_node_get_obj(node);
    return  obj;
    
}


extern void
basic_stack_dealloc(basic_stack_p p) {
    double_list_dealloc(p);
}







































