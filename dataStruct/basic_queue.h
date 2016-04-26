//
//  basic_queue.h
//  dataStruct
//
//  Created by li yajun on 16/4/26.
//  Copyright © 2016年 li yajun. All rights reserved.
//

#ifndef basic_queue_h
#define basic_queue_h

#include <stdio.h>
#include "double_list.h"
typedef double_list_p basic_queue_p;

extern basic_queue_p
basic_que_alloc(void(*obj_free)(object_p obj));

extern BOOL
basic_que_enque(basic_queue_p p, object_p obj);

extern object_p
basic_que_deque(basic_queue_p p);


extern void
basic_que_dealloc(basic_queue_p p);

#endif /* basic_queue_h */
