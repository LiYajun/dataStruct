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
d_node_link(d_node_p p, d_node_p next){

    if(p==NULL && next==NULL) {
        return;
    }else if(p==NULL && next!=NULL){
        next->pre = p;
    }else if(p!=NULL && next==NULL){
        p->next = next;
    }else {
        p->next = next;
        next->pre = p;
    }
        

}
extern d_node_p
d_node_get_next(d_node_p p) {
    assert(p!= NULL);
    return p->next;
}
extern d_node_p
d_node_get_pre(d_node_p p) {
    assert(p!=NULL);
    return p->pre;
}
extern object_p
d_node_get_obj(d_node_p p) {
    assert(p!= NULL);
    return p->obj;
}
extern void
d_node_set_obj(d_node_p p, object_p obj){
    assert(p!=NULL);
    assert(obj!=NULL);
    p->obj = obj;
}

extern object_p
d_node_dealloc(d_node_p p) {
    
    object_p obj = NULL;
    assert(p!=NULL);
    obj = p->obj;
    p->pre = p->next = NULL;
    Free(p);
    return obj;
}












