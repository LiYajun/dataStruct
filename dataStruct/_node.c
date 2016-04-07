//
//  _node.c
//  dataStruct
//
//  Created by li yajun on 16/4/7.
//  Copyright © 2016年 li yajun. All rights reserved.
//

#include "_node.h"

/*双端链表节点*/
struct _d_node
{
    struct _d_node * pre;
    struct _d_node * next;
    object_p    obj;
};