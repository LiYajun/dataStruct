//
//  avl_btree.c
//  dataStruct
//
//  Created by li yajun on 16/5/4.
//  Copyright © 2016年 li yajun. All rights reserved.
//

#include "avl_btree.h"
#include "mem_allocator.h"

struct AvlNode
{
    ElementType Element;
    AvlTree     Left;
    AvlTree     Right;
    int         Height;
};
static int
Height(Position p);

static AvlTree
SingleRotateWithLeft(AvlTree T);

static AvlTree
DoubleRotateWithLeft(AvlTree T);

static AvlTree
SingleRotateWithRight(AvlTree T);

static AvlTree
DoubleRotateWithRight(AvlTree T);

static int
Max(int a, int b);
/*插入一个数值*/
AvlTree
Insert( ElementType X, AvlTree T)
{
    if( T == NULL ) {
        T = Malloc(sizeof( struct AvlNode ) );
        if(T == NULL)
            fprintf(stdout, "malloc failed");
        else {
            T->Element = X;
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
        
    }else if( X < T->Element ){
        
        T->Left = Insert(X, T->Left);
        if( Height(T->Left)-Height(T->Right)==2){
            
            if ( X < T->Left->Element)
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
            
        }
            
    }else if( X > T->Element ){
        T->Right = Insert(X, T->Right);
        if( Height(T->Right)-Height(T->Left)==2){
            
            if ( X > T->Right->Element)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
        }
    }
    T->Height = Max(Height(T->Left), Height(T->Right))+1;
    return  T;
}
/*左边的旋转*/ //LL
static Position
SingleRotateWithLeft( Position K2 )
{
    Position K1;
    
    K1 = K2->Left;
    K2->Left   = K1->Right;
    K1->Right  = K2;
    K2->Height = Max(Height(K2->Left), Height(K2->Right))+1;
    K1->Height = Max(Height(K1->Left), K2->Height)+1;
    return K1;
}
/*右边的旋转*/ //RR
static Position
SingleRotateWithRight( Position K1 )
{
    Position K2;
    
    K2 = K1->Right;
    K1->Right  = K2->Left;
    K2->Left   = K1;
    K1->Height = Max( Height(K1->Left), Height(K1->Right) )+1;
    K2->Height = Max(Height(K2->Right), K1->Height)+1;
    return K2;
}
/*右旋加左旋*/ //LR
static Position
DoubleRotateWithLeft( Position K3 )
{
    K3->Left = SingleRotateWithRight(K3->Left);
    return SingleRotateWithLeft( K3 );
}
/*左旋加右旋*/ //RL
static Position
DoubleRotateWithRight( Position K1)
{
    K1->Right = SingleRotateWithLeft(K1->Right);
    return SingleRotateWithRight( K1 );
}
inline static int
Max(int a, int b)
{
    return  a>b? a:b;
}
static int
Height(Position p){
    if ( p == NULL )
        return  -1;
    else
        return p->Height;
}