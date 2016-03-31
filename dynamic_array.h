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
typedef struct _dy_array * dy_array_p;

extern dy_array_p
dy_array_alloc(void);

extern dy_array_p
dy_array_alloc_init( uint init_cap );

#endif /* dynamic_array_h */
