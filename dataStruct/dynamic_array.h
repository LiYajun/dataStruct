//
//  dynamic_array.h
//  dataStruct
//
//  Created by li yajun on 16/3/31.
//  Copyright © 2016年 li yajun. All rights reserved.
//

#ifndef dynamic_array_h
#define dynamic_array_h
#include <stdio.h>
#include "global_types.h"

typedef struct _dy_array * dy_array_p;

extern dy_array_p
dy_array_alloc(void (*obj_free)(object_p object));

extern dy_array_p
dy_array_alloc_init( uint init_cap ,
                    void (*obj_free)(object_p object) );
extern void
dy_array_add_object(const dy_array_p p, object_p anobject );

extern void
dy_array_insert_at(const dy_array_p p, object_p anobject, uint index);

extern void
dy_array_del_at(const dy_array_p p, uint index);


extern object_p
dy_array_pop_at(const dy_array_p p, uint index);

extern object_p
dy_array_object_at(const dy_array_p p, uint index);

extern uint
dy_array_object_count(const dy_array_p p);

extern void
dy_array_dealloc(const dy_array_p p);

#endif /* dynamic_array_h */
