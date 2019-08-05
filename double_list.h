#ifndef _DOUBLE_LIST_H
#define _DOUBLE_LIST_H
#include<stdlib.h>
#include<stdio.h>
//创建节点数据结构
typedef struct node
{
	void * data;
        struct node *front;
        struct node *next;
}node,*pnode;
//创建链表数据结构
typedef struct list
{
    int size;
	pnode first;
	pnode last;
}list;

//初始化链表
list* init_list ();
//创建结点
node* create_node(void * const x);
//尾部插入节点
void insert_back (list * l, void * x);
//按照名字查找
node* find_name(list *l, char *current, int (*cmp_word)(void *, char *, int), int flag);
//快速排序
void Sort_List (list *l, int (*sl)(void*  ,void* ));
void sort_list (node* first, node* last ,int (*cmp)(void * , void * ));
//正向打印链表
void print_list_begin(list * l, void (*pt)(void * ));
//反向打印链表
void print_list_end(list * l, void (*pt)(void * ));
//销毁链表
void destroy_list(list * l, void (*free_name)(void *));
//创建链表
list* creat_word_list(char *file, void (*add_num)(void *), int (*cmp_word)(void *, char *, int), void (*insert_word_node)(list *, char *), void (*print_data)(void *), int flag);

#endif
