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
#include "double_list.h"
#include "basic_stack.h"

#include <GLFW/glfw3.h>

int tmain(void)
{
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
static void object_free(object_p ptr)
{
    free(ptr);
}
static BOOL object_find(object_p p)
{
    if(*(int*)p == 6){
        return  YES;
    }else{
        return NO;
    }
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


void test_case1();
void test_case2();
void test_case3();

int  main(int argc, const char * argv[]) {
    // insert code here...
    //test_case2();
    int i;
    int count =0;
    for(i=1; i<=10000; i++) {
        if(i%2==0 || i%3==0) {
            count++;
            if(count == 2333) {
                printf("%d",i);
            }
        }
    }
    return 0;
}




void test_case3(void) {
    basic_stack_p stack = basic_stack_alloc(&object_free);
    
    for(int i=0; i<100; i++) {
        int * t = malloc(sizeof(int));
        *t = i;
        basic_stack_push(stack, t);
        object_p obj = basic_stack_peek(stack);
        fprintf( stdout,"%d \n", *(int*)obj );
    }
    for(int i=0; i<100; i++) {
        basic_stack_pop(stack);
    }
    basic_stack_dealloc(stack);
}

void test_case2(void) {
    
    clock_t start,end;
    double duration;
    long count = 1000000;
    d_node_p pos = NULL;
    double_list_p list =  double_list_alloc(object_free);
    
    start = clock();
    for(int i=0; i<count; i++)
    {
        int * t = malloc(sizeof(int));
        //int * m = malloc(sizeof(int));
        *t = i;
        //*m = i+10000;
        double_list_insert_last(list, t);
        //double_list_insert_first(list, m);
    }
    end = clock();
    duration = (double)(end - start)  / CLOCKS_PER_SEC;
    printf("duration = %f seconds\n",duration);
    
    
    d_node_p find_node = double_list_find(list, &object_find);
    int * test = malloc(sizeof(int));
    *test = 999;
    double_list_insert_next(list, find_node, test);
    int * test2= malloc(sizeof(int));
    *test2 = 1999;
    double_list_insert_pre(list, find_node, test2);
 
    
    for(pos = double_list_first_node(list); pos != NULL; pos = d_node_get_next(pos))
    {
        object_p obj = d_node_get_obj(pos);
        printf("%d \n", *(int*)obj);
    }
    
   
    double_list_dealloc(list);
    
}


void test_case1(void) {
    
    long count = 10;
    int i =0;
    int *t = NULL;
    clock_t start,end;
    double duration;
 
    dy_array_p ary = NULL;
    ary = dy_array_alloc( &object_free );
    
    
    start = clock();
    
    for(i=0 ; i<count; i++)
    {
        t = (int*) malloc(sizeof(int)*1);
        *t = i;
        //dy_array_insert_at(ary, (object_p)t, 0);
        dy_array_add_object(ary, t);
    }
    t = (int*) malloc(sizeof(int)*1);
    *t = 34;
    dy_array_insert_at(ary, t, 4);
    dy_array_del_at(ary, 7);
    
    end = clock();
    
    
    duration = (double)(end - start)  / CLOCKS_PER_SEC;
    printf("duration = %f seconds\n",duration);
    printf("%d\n", __INT_MAX__);
    
    count = dy_array_object_count(ary);
    for(i=0 ; i<count; i++)
    {
        int * p = dy_array_object_at(ary,  i);
        printf("object = %d\n", *p);
    }
    
    
    dy_array_dealloc(ary);
    
    

}