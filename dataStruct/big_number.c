//
//  big_number.c
//  dataStruct
//
//  Created by li yajun on 16/4/22.
//  Copyright © 2016年 li yajun. All rights reserved.
//


#include <assert.h>
#include <string.h>

#include "big_number.h"
#include "mem_allocator.h"

#define Default_Count 100

struct _big_number{
    uint8 * data;
    uint  cur_count;
    uint  max_count;
    int8  sign; /* 1为正数， －1为负数*/
};

static BOOL
_big_number_recap(const big_number_p this );

static BOOL
_big_number_add_other(big_number_p this, big_number_p other_num);

static BOOL
_big_number_minus_other(big_number_p this, big_number_p other_num);



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
    
    p->data = Calloc(p->max_count, sizeof(uint8));
    if(p->data == NULL) {
        Free(p);
        return  NULL;
    }
    p->cur_count = 0;
    p->sign      = 1;
    return p;
}

extern BOOL
big_number_set_num(big_number_p this,  char* str){
    
    char * ptr = str;
    uint i = 0;
    uint8 temp;
    assert(this!= NULL);
    if(*ptr == '-'){
        this->sign = -1;
        ptr++;
    }else if(*ptr == '+' ){
        this->sign =  1;
        ptr++;
    }else{
        this->sign =  1;
    }
    while(*ptr!='\0') {
        
        if(*ptr - '0'<0 || *ptr - '0'>9) {
            fprintf(stderr, "input string is not number string");
            return NO;
        }
        this->data[i] = *ptr-'0';
        ptr++;
        i++;
    }
    this->cur_count = i;
    /*翻转一下位置*/
    for(i=0; i<this->cur_count/2; i++) {
        temp = this->data[i];
        this->data[i] = this->data[this->cur_count-1-i];
        this->data[this->cur_count-1-i] = temp;
    }
    return  YES;
}
extern int8*
big_number_value(big_number_p this) {
    
    sint i,j;
    sint m;
    char * str  = NULL;
    assert(this!=NULL);
    if(this->sign == 1)
    {
        str = Calloc(this->cur_count+1, sizeof(int8));
        m = 0;
    }
    else
    {
        str = Calloc(this->cur_count+2, sizeof(int8));
        str[0] = '-';
        m = 1;
    }
    
    for (i=this->cur_count-1,j=m; i>=0; i--,j++) {
        
        str[j] = this->data[i]+'0';
    }
    
    return str;
}
extern BOOL
big_number_add_other(big_number_p this, big_number_p other_num){
    assert(this!=NULL);
    assert(other_num!=NULL);
    
    if((this->sign == 1 &&  other_num->sign == 1) ||
       (this->sign ==-1 &&  other_num->sign ==-1))
    {
        _big_number_add_other(this, other_num);
        
    }
    else if((this->sign == 1 && other_num->sign == -1)||
            (this->sign ==-1 && other_num->sign == 1))
    {
        _big_number_minus_other(this, other_num);
    }
    return YES;
}
extern BOOL
big_number_minus_other(big_number_p this, big_number_p other_num){
    assert(this!=NULL);
    assert(other_num!=NULL);
    
    if((this->sign == 1 &&  other_num->sign == -1) ||
       (this->sign ==-1 &&  other_num->sign ==  1))
    {
        _big_number_add_other(this, other_num);
    }
    else if((this->sign == 1 && other_num->sign == 1)||
            (this->sign ==-1 && other_num->sign == -1))
    {
        _big_number_minus_other(this, other_num);
    }
    return YES;
}

static BOOL
_big_number_add_other(big_number_p this, big_number_p other_num){
    
    
    uint    i;
    uint    pos = 0;
    uint8   top = 0;
    uint8   num = 0;
    
    pos = this->cur_count > other_num->cur_count ? this->cur_count:other_num->cur_count;
    
    if(this->max_count <= pos){
        if( _big_number_recap( this ) == NO )
            return NO;
    }
    
    for(i=0; i< pos; i++) {
        num =  this->data[i]+other_num->data[i] +top  ;
        this->data[i] = num % 10 ;
        top = num / 10;
    }
    
    /*进位判断*/
    if(top>0){
        this->data[i]   = top;
        this->cur_count = i;
    }else{
        this->cur_count = pos;
    }
    
    return YES;
}

static BOOL
_big_number_minus_other(big_number_p this, big_number_p other_num){
    sint i;
    uint max_pos = 0;
    uint min_pos = 0;
    int8 top = 0;
    int8 num = 0;
    int8 sign = 1;
    uint8 * this_data = NULL;
    uint8 * other_data= NULL;
 
    if(this->cur_count > other_num->cur_count){
        sign    = 1;
        max_pos = this->cur_count;
        min_pos = other_num->cur_count;
    }
    else if(this->cur_count < other_num->cur_count){
        sign    = -1;
        max_pos =  other_num->cur_count ;
        min_pos =  this->cur_count;
    }
    else{
        
        max_pos = this->cur_count;
        min_pos = this->cur_count;
        for(i=this->cur_count-1; i>=0; i--){
            if(this->data[i]>other_num->data[i]){
                sign =  1;
                break;
            }else if(this->data[i] < other_num->data[i] ){
                sign = -1;
                break;
            }else{
                continue;
            }
        }
        
    }
   
    if(sign == 1){
        this_data  = this->data;
        other_data = other_num->data;
    }else {
        this_data  = other_num->data;
        other_data = this->data;
    }
    if(this->max_count <= max_pos){
        if( _big_number_recap( this ) == NO )
            return NO;
    }
    for (i=0; i< min_pos; i++) {
        num = this_data[i] - other_data[i] + top;
        if(num<0){
            num = num+10;
            this->data[i] = num;
            top = -1;
        }else{
            this->data[i] = num;
            top =  0;
        }
    }
    for(i=min_pos; i<max_pos; i++){
        num = this_data[i] + top;
        if(num<0){
            num = num+10;
            this->data[i] = num;
            top = -1;
        }else{
            this->data[i] = num;
            top =  0;
        }
    }
    
    this->cur_count = max_pos;
    this->sign = sign;
    
    
    return YES;
    
}
/**
 *  @brief <#Description#>
 *
 *  @param number1 <#number1 description#>
 *  @param number2 <#number2 description#>
 *  @param oper    <#oper description#>
 *
 *  @return 1 表示结果为正，－1表示结果为负，0表示结果为0
 */
static int8
_big_number_result_sign(big_number_p number1, big_number_p number2, char oper){
    sint i;
    if(oper == '+'){
        
        if(number1->sign == 1 &&  number2->sign == 1)
        {
            return 1;
        }
        else if(number1->sign == -1 &&  number2->sign == -1)
        {
            return -1;
        }
        else /*if((number1->sign== 1 && number2->sign == -1) ||
                (number1->sign==-1 && number2->sign ==  1))*/
        {
            /*判断 正 负 号*/
            if(number1->cur_count < number2->cur_count){
                return number2->sign;
            }else if(number1->cur_count > number2->cur_count){
                return number1->sign;
            }else{
                for(i=number1->cur_count-1; i>=0; i--){
                    
                    if(number1->data[i]>number2->data[i]){
                        return  1;
                    }else if(number1->data[i] < number2->data[i]){
                        return -1;
                    }else{
                        continue;
                    }
                }
                return  0;
            }
        }
        
    }else if(oper == '-'){
        if(number1->sign == 1 &&  number2->sign == -1)
        {
            return 1;
        }
        else if(number1->sign == -1 &&  number2->sign == 1)
        {
            return -1;
        }
        else /*if((number1->sign== 1 && number2->sign == 1) ||
                (number1->sign==-1 && number2->sign ==-1))*/
        {
            /*判断 正 负 号*/
            if(number1->cur_count < number2->cur_count){
                return -number2->sign;
            }else if(number1->cur_count > number2->cur_count){
                return number1->sign;
            }else{
                for(i=number1->cur_count-1; i>=0; i--){
                    
                    if(number1->data[i]>number2->data[i]){
                        return  1;
                    }else if(number1->data[i] < number2->data[i]){
                        return -1;
                    }else{
                        continue;
                    }
                }
                return  0;
            }
        }
        
    }else{
        
        return -3;
    }
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









