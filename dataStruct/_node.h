//
//  _node.h
//  dataStruct
//
//  Created by li yajun on 16/4/7.
//  Copyright © 2016年 li yajun. All rights reserved.
//

#ifndef _node_h
#define _node_h

#include <stdio.h>
#include "global_types.h"

/*双端结点*/
typedef struct _d_node *  d_node_p;


extern d_node_p
d_node_alloc(void);

extern void
d_node_link(d_node_p pre, d_node_p next);

extern void
d_node_set_obj(d_node_p p, object_p obj);


extern d_node_p
d_node_get_next(d_node_p p);

extern d_node_p
d_node_get_pre(d_node_p p);

extern object_p
d_node_get_obj(d_node_p p);

extern object_p
d_node_dealloc(d_node_p p);
/*双端结点*/


#endif /* _node_h */
