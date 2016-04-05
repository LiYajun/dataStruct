//
//  mem_allocator.h
//  dataStruct
//
//  Created by li yajun on 16/3/31.
//  Copyright © 2016年 li yajun. All rights reserved.
//

#ifndef mem_allocator_h
#define mem_allocator_h

#include <stdio.h>
#include <stdlib.h>

#define  Malloc(p)       malloc((p))
#define  Free(p)        free((p))
#define  Realloc(p, num)     realloc((p),num)
#endif /* mem_allocator_h */
