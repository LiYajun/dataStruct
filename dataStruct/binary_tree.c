//
//  binary_tree.c
//  dataStruct
//
//  Created by li yajun on 16/5/3.
//  Copyright © 2016年 li yajun. All rights reserved.
//
#include <assert.h>
#include "binary_tree.h"
#include "mem_allocator.h"

static btree_node_p
_find_node(object_p ouside_obj, btree_node_p node, compare_func_p find_func);

static btree_node_p
_find_min_node(btree_node_p node);

static btree_node_p
_find_max_node(btree_node_p node);

static btree_node_p
_find_max_node_non_recursion(btree_node_p node);

static btree_node_p
_del_node(object_p outside_obj, btree_node_p node,compare_func_p compare_func, obj_free_p obj_free);

extern btree_p
btree_alloc(obj_order (*compare_func)(object_p obj1, object_p obj2),void (*obj_free)(object_p object)) {
    btree_p p = NULL;
    assert(compare_func!=NULL);
    assert(obj_free != NULL);
    
    p = Calloc(1, sizeof(struct _btree));
    if(p == NULL){
        return  NULL;
    }
    p->root = NULL;
    p->maxdepth = 0;
    p->compare_func = compare_func;
    p->obj_free = obj_free;
    return  p;
}

extern object_p
find_obj(object_p outside_obj, btree_p p) {
    assert(p!=NULL);
    assert(outside_obj!=NULL);
    btree_node_p node = _find_node(outside_obj, p->root, p->compare_func);
    if (node == NULL) {
        return NULL;
    }
    return node->data;
}
extern object_p
find_max_obj(btree_p p) {
    btree_node_p node = NULL;
    assert(p!=NULL);
    if(p->root != NULL) {
        node = _find_max_node(p->root);
    }
    return node;
}
extern object_p
find_min_obj(btree_p p) {
    btree_node_p node = NULL;
    assert(p!=NULL);
    if(p->root !=NULL) {
       node = _find_min_node(p->root);
    }
    return node->data;
}

extern BOOL
insert_obj(object_p outside_obj, btree_p p) {
    btree_node_p node = NULL;
    btree_node_p temp = NULL;
    btree_node_p new_node = NULL;
    obj_order order =  none;
    assert(p!=NULL);
    assert(outside_obj!=NULL);
    node = p->root;
    if(node == NULL)
        return NO;
    while (node!=NULL) {
        
        order = p->compare_func(outside_obj, btree_node_get_obj(node) );
        temp = node;
        if(order == big) {
            node = node->right;
        }else if(order == small) {
            node = node->left;
        }else if(order == same) {
            break;
        }
    }
    if(order == same) {
        fprintf(stdout, "has same value object...");
        return NO;
    }
     new_node = Calloc(1, sizeof(struct _btree_node));
    
    if(order == big) {
        temp->right = new_node;
    }else {
        temp->left =  new_node;
    }
     new_node->data = outside_obj;
    return YES;
}
extern BOOL
del_obj(object_p outside_obj, btree_p p) {
    
    btree_node_p node = NULL;
    btree_node_p temp = NULL;
   
    assert(p!=NULL);
    assert(outside_obj!=NULL);
    
    node = p->root;
    if(node == NULL)
        return NO;
    temp = _del_node(outside_obj, node, p->compare_func, p->obj_free);
    if(temp == NULL)
        return NO;
    return  YES;
}
static btree_node_p
_del_node(object_p outside_obj, btree_node_p node,compare_func_p compare_func, obj_free_p obj_free){
    obj_order order       = none;
    btree_node_p min_node = NULL;
    btree_node_p temp     = NULL;
    
    if(node==NULL) { /*没有找到*/
        return NULL;
    }
    order =  compare_func(outside_obj, node->data) ;
    if( order == big ){
        node->right = _del_node(outside_obj, node->right, compare_func, obj_free);
    }else if(order == small) {
        node->left  = _del_node(outside_obj, node->left,  compare_func, obj_free);
    }else if(node->left !=NULL && node->right!=NULL){
        min_node    = _find_min_node(node->right);
        obj_free(node->data);
        node->data  = min_node->data;
        node->right = _del_node(outside_obj, node->right,compare_func, obj_free);
    }else {
        temp = node;
        if(node->left == NULL)
            node = node->right;
        else if(node->right == NULL)
            node = node->left;
        
        Free(temp);
    }
    return node;
    
}
/*找到最大的节点*/
static btree_node_p
_find_max_node(btree_node_p node) {
    if(node == NULL) {
        return NULL;
    }else if( btree_node_get_right(node) == NULL) {
        return node;
    }else{
        return _find_max_node( btree_node_get_right(node));
    }
}
/*找到最大的节点，非递归*/
static btree_node_p
_find_max_node_non_recursion(btree_node_p node) {
    if (node!=NULL) {
        while (node->right!=NULL )
            node = node->right;
    }
    return node;
}


/*找到最小的节点*/
static btree_node_p
_find_min_node(btree_node_p node) {
    if(node == NULL) {
        return NULL;
    }else if( btree_node_get_left(node) == NULL) {
        return node;
    }else{
        return _find_min_node( btree_node_get_left(node));
    }
}
/*找到符合要求的节点*/
static btree_node_p
_find_node(object_p ouside_obj, btree_node_p node, compare_func_p find_func){
    
    if(node == NULL || ouside_obj == NULL){
        return NULL;
    }else if( find_func(ouside_obj, btree_node_get_obj(node))==same ) {
        
        return node;
        
    }else if( find_func(ouside_obj, btree_node_get_obj(node))==big  ) {
        
        return  _find_node(ouside_obj, btree_node_get_right(node), find_func);
        
    }else if( find_func(ouside_obj, btree_node_get_obj(node))==small) {
        
        return  _find_node(ouside_obj, btree_node_get_left(node),  find_func);
        
    }else {
        return NULL;
    }
}
