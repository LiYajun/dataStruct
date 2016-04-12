//
//  _node.c
//  dataStruct
//
//  Created by li yajun on 16/4/7.
//  Copyright © 2016年 li yajun. All rights reserved.
//
#include <assert.h>
#include "_node.h"
#include "mem_allocator.h"
/*双端链表节点*/
struct _d_node
{
    struct _d_node * pre;
    struct _d_node * next;
    object_p    obj;
};


extern d_node_p
d_node_alloc(void){
    d_node_p p = NULL;
   
    p = Malloc(sizeof(struct _d_node));
    if(p == NULL){
        return NULL;
    }
    p->obj = NULL;
    p->pre = NULL;
    p->next= NULL;
    return p;
}
extern void
d_node_link(d_node_p pre, d_node_p next){
    assert(pre);
    assert(next);
    pre->next = next;
    next->pre = pre;
}
extern void
d_node_set_obj(d_node_p p, object_p obj){
    assert(p!=NULL);
    assert(obj!=NULL);
    p->obj = obj;
}