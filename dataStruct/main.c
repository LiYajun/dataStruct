//
//  main.c
//  dataStruct
//
//  Created by li yajun on 16/3/28.
//  Copyright © 2016年 li yajun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "dynamic_array.h"



void object_free(object_p ptr)
{
    free(ptr);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int count = 10;
    int i =0;
    int *t = NULL;
 
    dy_array_p ary = NULL;
    ary = dy_array_alloc( &object_free );
    
    for(i=0 ; i<count; i++)
    {
        t = (int*) malloc(sizeof(int)*1);
        *t = i;
       //dy_array_insert_at(ary, (object_p)t, 0);
        dy_array_add_object(ary, t);
    }
    
    for(i=0 ; i<count; i++)
    {
       int * p = dy_array_object_at(ary,  i);
        printf("object = %d\n", *p);
    }
    for(i=0 ; i<count; i++)
    {
        printf("i = %d\n",i);
        dy_array_remove_at(ary, 0);
    }
 
    dy_array_dealloc(ary);
 

 
    return 0;
}

