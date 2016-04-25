//
//  big_number.h
//  dataStruct
//
//  Created by li yajun on 16/4/22.
//  Copyright © 2016年 li yajun. All rights reserved.
//  大数 加减法

#ifndef big_number_h
#define big_number_h

#include "global_types.h"

#include <stdio.h>
typedef struct _big_number big_number,*big_number_p;


extern big_number_p
big_number_alloc(uint length);

extern BOOL
big_number_add_other(big_number_p this, big_number_p other_num);

extern BOOL
big_number_minus_other(big_number_p this, big_number_p other_num);

extern BOOL
big_number_set_num(big_number_p this,  char* str);

extern int8*
big_number_value(big_number_p this);
#endif /* big_number_h */
