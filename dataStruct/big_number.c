//
//  big_number.c
//  dataStruct
//
//  Created by li yajun on 16/4/22.
//  Copyright © 2016年 li yajun. All rights reserved.
//

#include "big_number.h"

#include "global_types.h"
#include "mem_allocator.h"
#include <assert.h>
#include <string.h>

#define Default_Count 100

struct _big_number{
    uint8 * data;
    uint  cur_count;
    uint  max_count;
};

static BOOL
_big_number_recap(const big_number_p this );

extern big_number_p
big_number_alloc(uint length) {
    big_number_p p = NULL;
    
    p = Malloc(sizeof(struct _big_number));
    if(p == NULL) {
        return  NULL;
    }
    if(length!=0){
        p->max_count = length;
    }else{
        
        p->max_count = Default_Count;
    }
    
 /*   p->data = Malloc(p->max_count *sizeof(uint8));*/
    p->data = Calloc(p->max_count, sizeof(uint8));
    if(p->data == NULL) {
        Free(p);
        return  NULL;
    }
    p->cur_count = 0;
    return p;
}

extern BOOL
big_number_add_other(big_number_p this, big_number_p other_num){
    uint i;
    uint pos = 0;
    
    assert(this!= NULL);
    assert(other_num!=NULL);
    pos = this->cur_count > other_num->cur_count ? this->cur_count:other_num->cur_count;
    
    if(this->max_count <= pos){
        if( _big_number_recap( this ) == NO )
            return NO;
    }
    uint8 top = 0;
    for(i=0; i< pos; i++ ){
        uint8 num = this->data[i]+other_num->data[i];
        this->data[i] = num % 10 + top;
        top = num/10;
    }
    //进位判断
    if(top>0){
        this->data[i] = top;
    }
    
    return YES;
}

extern void
big_number_set_num(big_number_p this, const char* str){
    
    assert(this!= NULL);
    if(this->cur_count!=0)
        memset(this->data, 0, this->cur_count);
    
    
    
}

static BOOL
_big_number_recap(const big_number_p this ) {
    
    uint8* new_data = NULL;
    assert(this!=NULL);
    new_data = Calloc(this->max_count*1.5, sizeof(uint8)); /*(this->max_count*1.5*sizeof(uint8));*/
    if(new_data == NULL)
        return NO;
    
    memmove(new_data, this->data, this->max_count * sizeof(uint8));
    Free(this->data);
    this->data = new_data;
    
    return YES;
}









