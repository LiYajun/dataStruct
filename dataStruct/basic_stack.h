//
//  basic_stack.h
//  dataStruct
//
//  Created by li yajun on 16/4/20.
//  Copyright © 2016年 li yajun. All rights reserved.
//

#ifndef basic_stack_h
#define basic_stack_h

#include <stdio.h>
#include "double_list.h"
typedef double_list_p basic_stack_p;

extern basic_stack_p
basic_stack_alloc(void(*obj_free)(object_p obj));

extern BOOL
basic_stack_push(basic_stack_p p, object_p obj);

extern object_p
basic_stack_pop(basic_stack_p p);

extern object_p
basic_stack_peek(basic_stack_p p);

extern void
basic_stack_dealloc(basic_stack_p p);

#endif /* basic_stack_h */
