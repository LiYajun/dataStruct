//
//  basic_queue.c
//  dataStruct
//
//  Created by li yajun on 16/4/26.
//  Copyright © 2016年 li yajun. All rights reserved.
//

#include "basic_queue.h"
#include <assert.h>
extern basic_queue_p
basic_que_alloc(void(*obj_free)(object_p obj)){
    basic_queue_p p = NULL;
    assert(obj_free!= NULL);
    p = (basic_queue_p)double_list_alloc( obj_free );
    
    return p;
}

extern BOOL
basic_que_enque(basic_queue_p p, object_p obj){
    
    BOOL result = double_list_insert_last(p, obj);
    return  result;
}

extern object_p
basic_que_deque(basic_queue_p p){
    object_p obj = NULL;
    d_node_p node =  double_list_first_node(p);
    if(node == NULL) {
        return NULL;
    }
    obj = double_list_pop_node(p, node);
    return  obj;
}

extern object_p
basic_que_peek_first(basic_queue_p p) {
    object_p obj = NULL;
    d_node_p node = double_list_first_node(p);
    if(node == NULL) {
        return  NULL;
    }
    obj = d_node_get_obj(node);
    return  obj;
    
}


extern void
basic_que_dealloc(basic_queue_p p) {
    double_list_dealloc(p);
}
