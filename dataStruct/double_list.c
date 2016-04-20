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

#define doulbe_list_for_each(list,pos) \
for (pos = list->first_node; pos != NULL; pos = pos->next)

struct _double_list
{
    uint      objs_num;             /*所有元素个数    */
    d_node_p  first_node;           /*第一个节点      */
    d_node_p  last_node;            /*最后一个节点    */
    
    void (* obj_free_func)(object_p object);/*释放*/
    BOOL (* obj_find_func)(object_p object);/*查找*/
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
extern d_node_p
double_list_get_first(double_list_p p) {
    assert(p!=NULL);
    return p->first_node;
}
extern d_node_p
double_list_get_last(double_list_p p) {
    assert(p!=NULL);
    return p->last_node;
}
extern BOOL
double_list_insert_next(double_list_p p, d_node_p obj_node, object_p obj) {
    
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
     p->objs_num++;
    return YES;
}

extern BOOL
double_list_insert_pre(double_list_p p, d_node_p obj_node, object_p obj){
    
    d_node_p new_node = NULL;
    assert(p!=NULL);
    assert(obj!=NULL);
    assert(obj_node!=NULL);
    
    new_node =  d_node_alloc( );  /*生成新的节点*/
    if(new_node == NULL){
        return NO;
    }
    d_node_set_obj(new_node, obj); /*放置新插入的 obj*/
    d_node_p old_pre = d_node_get_pre(obj_node);
    
    if(old_pre!=NULL){
        d_node_link(new_node, obj_node);
        d_node_link(old_pre,  new_node);
    }else{
        d_node_link(new_node, obj_node);
        p->first_node = new_node;
        
    }
    p->objs_num++;
    return YES;
    
}

/*---------------------------------------------*\
                插在尾节点之后
\*---------------------------------------------*/
extern BOOL
double_list_insert_last(double_list_p p, object_p obj) {
    
    d_node_p new_node = NULL;
    
    assert(p!=NULL);
    assert(obj!=NULL);
   
    new_node =  d_node_alloc( );  /*生成新的节点*/
    if(new_node == NULL){
        return NO;
    }
    d_node_set_obj(new_node, obj);
    if(p->last_node == NULL) {
        p->first_node = p->last_node = new_node;
    }else {
        d_node_link(p->last_node, new_node);
        p->last_node = new_node;
    }
     p->objs_num++;
    return YES;
}

/*---------------------------------------------*\
                插在头节点之前
\*---------------------------------------------*/
extern BOOL
double_list_insert_first(double_list_p p, object_p obj){
    
    d_node_p new_node = NULL;
    
    assert(p!=NULL);
    assert(obj!=NULL);
    
    new_node =  d_node_alloc( );  /*生成新的节点*/
    if(new_node == NULL){
        return NO;
    }
    d_node_set_obj(new_node, obj);
    if(p->first_node == NULL) {
        p->first_node = p->last_node = new_node;
    }else {
        d_node_link(new_node, p->first_node);
        p->first_node = new_node;
    }
    p->objs_num++;
    return YES;
}
extern void
double_list_set_find_func(double_list_p p, BOOL(* obj_find_func)(object_p object) ) {
    
    assert(p!=NULL);
    assert(obj_find_func!=NULL);
    p->obj_find_func = obj_find_func;
}

/*---------------------------------------------*\
                找到满足条件的节点
\*---------------------------------------------*/
extern d_node_p
double_list_find(double_list_p p, BOOL (* obj_find_func)(object_p object)) {
    d_node_p temp_node = NULL;
    object_p obj = NULL;
    assert(p!=NULL);
    assert(obj_find_func != NULL);
    
    if(p->objs_num==0) {
        return NULL;
    }
    temp_node = p->first_node;
    while (temp_node != NULL) {
        obj = d_node_get_obj(temp_node);
        if( obj_find_func(obj) == YES ){
            return temp_node;
        }
        temp_node = d_node_get_next(temp_node);
    }
    return NULL;
}

extern uint
double_list_count(double_list_p p) {
    assert(p!=NULL);
    return  p->objs_num;
}
/*---------------------------------------------*\
                弹出obj_node中的object
                调用者管理对象内存
\*---------------------------------------------*/
extern object_p
double_list_pop(double_list_p p, d_node_p obj_node) {
    object_p obj     = NULL;
    d_node_p obj_pre = NULL;
    d_node_p obj_next= NULL;
    
    assert(p!=NULL);
    assert(obj_node!=NULL);
    
    obj_pre = d_node_get_pre(obj_node);
    obj_next= d_node_get_next(obj_node);
    d_node_link(obj_pre, obj_next);
    
    obj =  d_node_dealloc(obj_node);
    p->objs_num--;
    return  obj;
}
extern void
double_list_dealloc(double_list_p p) {

    d_node_p node = NULL;
    d_node_p next_node = NULL;
    object_p obj = NULL;
    assert(p!=NULL);
    if(p->objs_num==0){
        return;
    }
    node = p->first_node;
    while( node!=NULL) {
        next_node = d_node_get_next(node);
        obj =  d_node_dealloc( node );
        p->obj_free_func(obj);
        node = next_node;
    }

    p->first_node = p->last_node = NULL;
    p->objs_num = 0;
    Free(p);
}
 