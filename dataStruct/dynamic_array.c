//
//  dynamic_array.c
//  dataStruct
//
//  Created by li yajun on 16/3/31.
//  Copyright ? 2016年 li yajun. All rights reserved.
//
#include <assert.h>
#include "dynamic_array.h"
#include "mem_allocator.h"

#define  INIT_CAP    4          /*初始化的内存容量*/



static BOOL
_dy_array_check_max_cap(const dy_array_p p );

static object_p
_dy_array_remove_at(const dy_array_p p, uint index);

static uint
_dy_array_get_preindex(const dy_array_p p,  uint index);

static uint
_dy_array_get_nextindex(const dy_array_p p, uint index);

static void
_dy_array_forward(const dy_array_p p, uint index, uint start );

static void
_dy_array_backward(const dy_array_p p, uint index, uint end );


struct _dy_array
{
    uint       max_cap;             /*最大的内存容量  */
    uint       objs_size;           /*现在的元素个数  */
    uint       head_index;          /*头部的索引     */
    uint       tail_index;          /*尾部的索引     */
    object_p*   objects;            /*所有元素      */
    void (* object_free_func)(object_p object); /*释放方法*/
};
/*---------------------------------------------*\
                创建对象函数
\*---------------------------------------------*/
extern dy_array_p
dy_array_alloc(void (*obj_free)(object_p object)) {
    return  dy_array_alloc_init(INIT_CAP, obj_free);
}


extern dy_array_p
dy_array_alloc_init( uint init_cap , void (*obj_free)(object_p object) ) {
    
    dy_array_p p = NULL;
    
    assert(obj_free!=NULL);
    
    if( init_cap <= 0){
        init_cap = INIT_CAP;
    }
    
   
    p = (dy_array_p)Malloc(sizeof(struct _dy_array));
    
    if(p == NULL){
        return NULL;
    }
    
    p->objects = NULL;
    p->objects = (object_p*)Malloc(sizeof(object_p) * init_cap);
    
    if(p->objects == NULL){
        Free(p);
        return NULL;
    }
    
    p->max_cap      = init_cap;
    p->objs_size    = 0;
    p->head_index   = 0;
    p->tail_index   = 0;
    p->object_free_func = obj_free;
    return p;
}
/*---------------------------------------------*\
                获取元素的总数
\*---------------------------------------------*/
extern uint
dy_array_object_count(const dy_array_p p)
{
    return  p->objs_size;
}

extern void
dy_array_add_object(const dy_array_p p, object_p anobject ) {
    
    dy_array_insert_at(p, anobject, p->objs_size);
    
}
extern void
dy_array_remove_last(const dy_array_p p ) {
    
    if(p->objs_size > 0)
    dy_array_del_at(p, p->objs_size-1);
}
/*---------------------------------------------*\
                  插入一个元素
\*---------------------------------------------*/
extern void
dy_array_insert_at(const dy_array_p p, object_p anobject, uint index) {
    
    uint real_index= 0;
    assert(p != NULL);
    assert(anobject != NULL);
    
    if(index > p->objs_size) {
        fprintf(stderr, "index out of array range!");
        return;
    }
    if(_dy_array_check_max_cap(p) == NO) {
        fprintf(stderr, "failed realloc memory!");
        return ;
    }
    
    //获取实际的插入位置
   real_index = (p->head_index+index)% p->max_cap ;
    
    if(index <= p->objs_size/2) {
        real_index = _dy_array_get_preindex(p, real_index); //实际的位置
        _dy_array_forward(p, index, p->head_index);
        p->objects[real_index] = anobject;
        p->head_index = _dy_array_get_preindex(p, p->head_index);
    }else {
        _dy_array_backward(p, p->objs_size-index, p->tail_index);
        p->objects[real_index] = anobject;
        p->tail_index = _dy_array_get_nextindex(p, p->tail_index);
    }
    p->objs_size++;
}
extern void
dy_array_del_at(const dy_array_p p, uint index) {
    object_p obj = NULL;
    obj = _dy_array_remove_at(p, index);
    if(obj == NULL) {
        return;
    }
    p->object_free_func(obj);
}
/*---------------------------------------------*\
    返回一个元素，数组放弃这个元素的内存管理，调用
        者管理
\*---------------------------------------------*/
extern object_p
dy_array_pop_at(const dy_array_p p, uint index) {
    object_p obj = NULL;
    obj = _dy_array_remove_at(p, index);
    if(obj == NULL) {
        return  NULL;
    }
    return  obj;
}

extern object_p
dy_array_object_at(const dy_array_p p, uint index) {
    uint real_index= 0;
    assert(p != NULL);
    if(index >= p->objs_size) {
        fprintf(stderr, "index out of array range! del index form 0 ~ objsize -1!");
        return NULL;
    }
    real_index = (p->head_index+index)% p->max_cap;
    return    p->objects[real_index];
}

/*---------------------------------------------*\
                删除一个元素
\*---------------------------------------------*/
static object_p
_dy_array_remove_at(const dy_array_p p, uint index) {
    uint real_index= 0;
    object_p obj = NULL;
    assert(p != NULL);
    
    if(index >= p->objs_size) {
        fprintf(stderr, "index out of array range! del index form 0  to objsize -1!");
        return NULL;
    }
    real_index = (p->head_index+index)% p->max_cap;
    obj = p->objects[real_index];
    if(index <= p->objs_size/2) {
        real_index = _dy_array_get_preindex(p, real_index);
        _dy_array_backward(p, index, real_index);
        p->head_index = _dy_array_get_nextindex(p, p->head_index);
    }else {
        real_index = _dy_array_get_nextindex(p, real_index);
        _dy_array_forward(p, index, real_index);
        p->tail_index = _dy_array_get_preindex(p, p->tail_index);
    }
    p->objs_size--;
    return obj;
}

/*---------------------------------------------*\
                获取内部索引
\*---------------------------------------------*/
static inline uint
_dy_real_index(const dy_array_p p, uint index) {
    
   return   (p->head_index+index)% p->max_cap;
}
/*---------------------------------------------*\
                    检查容量
\*---------------------------------------------*/
static BOOL
_dy_array_check_max_cap(const dy_array_p p ){
    object_p * new_p = NULL;
    object_p * old_p = NULL;
    uint real_index = 0;
    uint i;
    //判断容量够不够
    if(p->objs_size >= p->max_cap) {
        
        //new = Realloc(p->objects, sizeof(object_p)*2*p->max_cap); //扩大2倍
        old_p = p->objects;
        new_p = Malloc(sizeof(object_p)*2 * p->max_cap);
        
		if(new_p == NULL) {
            return NO;
        }
        for(i=0; i<p->objs_size; i++) {
        	real_index = (p->head_index+i)% p->max_cap;
        	new_p[i] = old_p[real_index];
        }
        Free(old_p);
        p->objects = new_p;
        p->head_index = 0;
        p->tail_index = p->objs_size;
        p->max_cap *= 2;
        
    }
    return YES;
}

/*---------------------------------------------*\
                 获取index上一个index
\*---------------------------------------------*/

static uint
_dy_array_get_preindex(const dy_array_p p, uint index) {
    
    if(index == 0) {
        index = p->max_cap-1;
    }else{
        index--;
    }
    return  index;
}
/*---------------------------------------------*\
                获取index的后一个index
\*---------------------------------------------*/
static uint
_dy_array_get_nextindex(const dy_array_p p, uint index) {
    
    if(index == p->max_cap-1) {
        index = 0;
    }else{
        index++;
    }
    return  index;
}
/*---------------------------------------------*\
                向左移动数据函数
\*---------------------------------------------*/
static void
_dy_array_forward(const dy_array_p p, uint num, uint start ) {
    uint i,j;
    j = start;
    for(i = 0; i<num; i++) {
        uint prej = _dy_array_get_preindex(p, j+i);
        p->objects[prej] = p->objects[j];
    }
}
/*---------------------------------------------*\
                向右边移动数据函数
\*---------------------------------------------*/
static void
_dy_array_backward(const dy_array_p p, uint num ,uint end) {
    uint i,j;
    j = end;
    for(i = 0; i<num; i++) {
        uint nextj = _dy_array_get_nextindex(p, j-i);
        p->objects[nextj] = p->objects[j];
    }
   
}
/*---------------------------------------------*\
                释放
\*---------------------------------------------*/
extern void
dy_array_dealloc(const dy_array_p p) {
    
    uint count = p->objs_size;
    uint i;
    uint real_index;
    for(i=0; i<count; i++) {
        real_index = (p->head_index+i) % p->max_cap;
        p->object_free_func( p->objects[real_index] );
    }
    Free(p->objects);
    Free(p);
}




















































