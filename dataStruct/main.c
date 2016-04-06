//
//  main.c
//  dataStruct
//
//  Created by li yajun on 16/3/28.
//  Copyright © 2016年 li yajun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/times.h>
#include <unistd.h>
#include <sys/time.h>
#include "dynamic_array.h"



void object_free(object_p ptr)
{
    free(ptr);
}
static void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend){
    static long clktck=0;
    if(0 == clktck)
        if((clktck=sysconf(_SC_CLK_TCK))<0)
            puts("sysconf err");
    
    printf("real:%7.2f\n", real/(double)clktck);
    printf("user-cpu:%7.2f\n", (tmsend->tms_utime - tmsstart->tms_utime)/(double)clktck);
    printf("system-cpu:%7.2f\n", (tmsend->tms_stime - tmsstart->tms_stime)/(double)clktck);
    printf("child-user-cpu:%7.2f\n", (tmsend->tms_cutime - tmsstart->tms_cutime)/(double)clktck);
    printf("child-system-cpu:%7.2f\n", (tmsend->tms_cstime - tmsstart->tms_cstime)/(double)clktck);
}
int main(int argc, const char * argv[]) {
    // insert code here...
    long count = 100000;
    int i =0;
    int *t = NULL;
    clock_t start,end, tstart, tend;
    double duration;
    struct tms t1, t2;
    struct timeval t3, t4;
    dy_array_p ary = NULL;
    ary = dy_array_alloc( &object_free );
    
//   tstart = times(&t1);
     start = clock();
//    gettimeofday(&t3, NULL);
    //t = (int*) malloc(sizeof(int)*1);
    for(i=0 ; i<count; i++)
    {
         t = (int*) malloc(sizeof(int)*1);
        *t = i;
       //dy_array_insert_at(ary, (object_p)t, 0);
        dy_array_add_object(ary, t);
    }
//    gettimeofday(&t4, NULL);
    
//    double span = (t4.tv_sec-t3.tv_sec) + (t4.tv_usec - t3.tv_usec)/1000000.0;
//    printf(" span = %f seconds\n", span);
//    tend = times(&t2);
     end = clock();
    
//    pr_times(tend - tstart, &t1, &t2);
     duration = (double)(end - start)  / CLOCKS_PER_SEC;
    printf("duration = %f seconds\n",duration);
    printf("%d\n", __INT_MAX__);
    /*
    for(i=0 ; i<count; i++)
    {
       int * p = dy_array_object_at(ary,  i);
        printf("object = %d\n", *p);
    }
    for(i=0 ; i<count; i++)
    {
        printf("i = %d\n",i);
        dy_array_del_at(ary, 0);
    }
 */
    dy_array_dealloc(ary);
 

 
    return 0;
}

