/* By Vamei */
/* Splay Tree */
#include <stdio.h>
#include <stdlib.h>
#include "splay_tree.h"








static void splay_tree(TREE, position);
static position search_value(TREE, ElementTP);
static void with_grandpa(TREE, position);

static void insert_node_to_nonempty_tree(TREE, position);
static TREE left_single_rotate(TREE);
static TREE left_double_rotate(TREE);
static TREE right_single_rotate(TREE);
static TREE right_double_rotate(TREE);
static TREE left_zig_zig(TREE);
static TREE right_zig_zig(TREE);
/*
 * insert a value into the tree
 * return root address of the tree
 */
position insert_value(TREE tr, ElementTP value)
{
    position np;
    /* prepare the node */
    np = (position) malloc(sizeof(struct node));
    np->element = value;
    np->parent  = NULL;
    np->lchild  = NULL;
    np->rchild  = NULL;
    
    if (tr == NULL) tr = np;
    else {
        insert_node_to_nonempty_tree(tr, np);
    }
    return tr;
}


/*
 *
 * return NUll if not found
 */
TREE find_value(TREE tr, ElementTP value)
{
    position np;
    
    np = search_value(tr, value);
    if (np != NULL && np != tr) {
        splay_tree(tr, np);
    }
    return np;
}

/*
 * splaying the tree after search
 */
static void splay_tree(TREE tr, position np)
{
    while (tr->lchild != np && tr->rchild != np) {
        with_grandpa(tr, np);
    }
    if (tr->lchild == np) {
        right_single_rotate(tr);
    }
    else if (tr->rchild == np) {
        left_single_rotate(tr);
    }
}

/*
 * dealing cases with grandparent node
 */
static void with_grandpa(TREE tr, position np)
{
    position parent, grandPa;
    int i,j;
    
    parent  = np->parent;
    grandPa = parent->parent;
    
    i = (grandPa->lchild == parent) ? -1 : 1;
    j = (parent->lchild == np) ? -1 : 1;
    if (i == -1 && j == 1) {
        right_double_rotate(grandPa);
    }
    else if (i == 1 && j == -1) {
        left_double_rotate(grandPa);
    }
    else if (i == -1 && j == -1) {
        right_zig_zig(grandPa);
    }
    else {
        left_zig_zig(grandPa);
    }
}

/*
 * search for value
 */
static position search_value(TREE tr, ElementTP value)
{
    if (tr == NULL) return NULL;
    
    if (tr->element == value) {
        return tr;
    }
    else if (value < tr->element) {
        return search_value(tr->lchild, value);
    }
    else {
        return search_value(tr->rchild, value);
    }
}

/*
 * left single rotation
 * return the new root
 */
static TREE left_single_rotate(TREE tr)
{
    TREE newRoot, parent;
    parent  = tr->parent;
    newRoot = tr->rchild;
    /* detach & attach */
    if (newRoot->lchild != NULL) newRoot->lchild->parent = tr;
    tr->rchild = newRoot->lchild;
    
    /* raise new root node */
    newRoot->lchild = tr;
    newRoot->parent = parent;
    if (parent != NULL) {
        if (parent->lchild == tr) {
            parent->lchild = newRoot;
        }
        else {
            parent->rchild = newRoot;
        }
    }
    tr->parent = newRoot;
    return newRoot;
}

/*
 * right single rotation
 * return the new root
 */
static TREE right_single_rotate(TREE tr)
{
    TREE newRoot, parent;
    parent  = tr->parent;
    newRoot = tr->lchild;
    
    /* detach & attach */
    if (newRoot->rchild != NULL) newRoot->rchild->parent = tr;
    tr->lchild = newRoot->rchild;
    
    /* raise new root node */
    newRoot->rchild = tr;
    newRoot->parent = parent;
    if (parent != NULL) {
        if (parent->lchild == tr) {
            parent->lchild = newRoot;
        }
        else {
            parent->rchild = newRoot;
        }
    }
    tr->parent = newRoot;
    return newRoot;
}

/*
 * left double rotation
 * return
 */
static TREE left_double_rotate(TREE tr)
{
    right_single_rotate(tr->rchild);
    return left_single_rotate(tr);
}

/*
 * right double rotation
 * return
 */
static TREE right_double_rotate(TREE tr)
{
    left_single_rotate(tr->lchild);
    return right_single_rotate(tr);
}

/*
 * insert a node to a non-empty tree
 * called by insert_value()
 */
static void insert_node_to_nonempty_tree(TREE tr, position np)
{
    /* insert the node */
    if(np->element <= tr->element) {
        if (tr->lchild == NULL) {
            /* then tr->lchild is the proper place */
            tr->lchild = np;
            np->parent = tr;
            return;
        }
        else {
            insert_node_to_nonempty_tree(tr->lchild, np);
        }
    }
    else if(np->element > tr->element) {
        if (tr->rchild == NULL) {
            tr->rchild = np;
            np->parent = tr;
            return;
        }
        else {
            insert_node_to_nonempty_tree(tr->rchild, np);
        }
    }
}

/*
 * right zig-zig operation
 */
static TREE right_zig_zig(TREE tr)
{
    position parent,middle,newRoot;
    parent  = tr->parent;
    middle  = tr->lchild;
    newRoot = tr->lchild->lchild;
    
    tr->lchild = middle->rchild;
    if (middle->rchild != NULL) middle->rchild->parent = tr;
    
    middle->rchild = tr;
    tr->parent     = middle;
    
    middle->lchild = newRoot->rchild;
    if (newRoot->rchild != NULL) newRoot->rchild->parent = middle;
    
    newRoot->rchild = middle;
    middle->parent  = newRoot;
    
    newRoot->parent = parent;
    if (parent != NULL) {
        if (parent->lchild == tr) {
            parent->lchild = newRoot;
        }
        else {
            parent->rchild = newRoot;
        }
    }
    return newRoot;
}

/*
 * left zig-zig operation
 */
static TREE left_zig_zig(TREE tr)
{
    position parent,middle,newRoot;
    parent  = tr->parent;
    middle  = tr->rchild;
    newRoot = tr->rchild->rchild;
    
    tr->rchild = middle->lchild;
    if (middle->lchild != NULL) middle->lchild->parent = tr;
    
    middle->lchild = tr;
    tr->parent     = middle;
    
    middle->rchild = newRoot->lchild;
    if (newRoot->lchild != NULL) newRoot->lchild->parent = middle;
    
    newRoot->lchild = middle;
    middle->parent  = newRoot;
    
    newRoot->parent = parent;
    if (parent != NULL) {
        if (parent->rchild == tr) {
            parent->rchild = newRoot;
        }
        else {
            parent->lchild = newRoot;
        }
    }
    return newRoot;  
}