//
//  double_list.c
//  dataStruct
//
//  Created by li yajun on 16/4/5.
//  Copyright © 2016年 li yajun. All rights reserved.
//
#include <assert.h>
#include "double_list.h"
#include "mem_allocator.h"


struct _double_list
{
    uint        objs_num;             /*所有元素个数*/
    d_node_p  first_node;
    d_node_p  last_node;
    void (* obj_free_func)(object_p object);
};

extern double_list_p
double_list_alloc(void(*obj_free)(object_p object)) {
    
    double_list_p p = NULL;
    assert(obj_free!=NULL);
    
    p = Malloc(sizeof(struct _double_list));
    if(p==NULL){
        return  NULL;
    }
    p->objs_num      = 0;
    p->first_node    = NULL;
    p->last_node     = NULL;
    p->obj_free_func = obj_free;
    
    return p;
}

extern BOOL
double_list_insert_next(double_list_p p, d_node_p obj_node, object_p obj){
    
    d_node_p new_node = NULL;
    assert(p!=NULL);
    assert(obj!=NULL);
    assert(obj_node!=NULL);
    
    new_node =  d_node_alloc( );  /*生成新的节点*/
    if(new_node == NULL){
        return NO;
    }
    d_node_set_obj(new_node, obj); /*放置新插入的 obj*/
    d_node_p old_next = d_node_get_next(obj_node);
    
    if(old_next!=NULL){
        d_node_link(obj_node, new_node);
        d_node_link(new_node, old_next);
    }else{
        d_node_link(obj_node, new_node);
        p->last_node = new_node;
    }
    
    
    
    return YES;
     
}
extern BOOL
double_list_insert_last(double_list_p p, object_p obj){
    
    d_node_p new_node = NULL;
    assert(p!=NULL);
    assert(obj!=NULL);
   
    new_node =  d_node_alloc( );  /*生成新的节点*/
    if(new_node == NULL){
        return NO;
    }
    d_node_set_obj(new_node, obj);
    
    return YES;
}

static void
double_list_init(double_list_p p, void(*obj_free)(object_p object)) {
    
    
}