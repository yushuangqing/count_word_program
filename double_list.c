#include"double_list.h"
#include<malloc.h>
#include<string.h>
//初始化链表
list* init_list()
{  
 	list *l = (list*)malloc(sizeof(list));
	if(NULL == l)
	{
		return NULL;
	}
	l->first = NULL;
	l->last = NULL;
	l->size = 0;
	return l;
} 
//创建结点
node* create_node(void * x)
{
	node *s = (node*)malloc(sizeof(node));	
	if(NULL == s)
	{
		return NULL;
	}
	s->data = x;
	s->front = NULL;
	s->next = NULL;
	return s;
}
//尾部插入节点
void insert_back(list * l, void * x)
{
	node *s = create_node(x);	
	if(l->size)
	{
		l->last->next = s;
		s->front = l->last;
		l->last = s;
	}
	else
	{
		l->first = s;
		l->last = s;
	}
	(l->size)++;
}

//按照名字查找
node* find_name(list *l, char *current, int (*cmp_word)(void *, char *, int), int flag)
{
	//printf("current:%s\n", current);
	node *p1 = l->first;
	//printf("p1->data=%p\n", p1->data);
	do
	{
		if((*cmp_word)(p1->data, current, flag) == 1)
		{
		//	printf("result:%d\n", (*cmp_word)(p1->data, current));
			return p1;	
		}
		else
		{
			//printf("p1->next%p\n", p1->next);
			//printf("p1->next->data:%p\n", p1->next->data);
			p1=p1->next;
		}
	}
	while(p1 != NULL);
	//printf("p1->data:%p\n", p1->data);
	return p1;
}

//快速排序
void sort_list (node* first, node* last ,int(*cmp)(void * ,void * ))
{
	if(first == last || !first || !last)  
	{
		return ;
	}
	node *low = first;
	node *high = last;
    void *p = first->data;
    while(first != last)
    {
        while (first != last && (*cmp)(p,last->data)) 
	    {
			last = last->front;
		}
		if (first != last)
	    {
			first->data = last->data;
			first = first->next; 
		}
		else break;
		while (first != last && (*cmp)(first->data,p))
	    {
		    first = first->next;
	    }
        if (first != last)
	    {
            last->data = first->data;
            last = last->front;
        }
        else break;
   }
   last->data = p;
   if(low != first)
   {
	    sort_list(low,first->front,(*cmp));
   }
   if (first!=high)  
   {
	    sort_list(first->next,high,(*cmp));
   }	
}

void Sort_List (list *l, int (*sl)(void*, void* ))
{
	node *first = l->first;
  	node *last = l->last;
  	sort_list(first, last, (*sl));	
}

//正向打印链表
void print_list_begin(list *l, void (*pt)(void *))//传入一个函数指针pt
{
	if(l->size == 0)
		return;
	node *p = l->first;
	while(NULL != p)
	{
		(*pt)(p->data);//调用print_data(void *)
		p = p->next;
	}
	printf("\n");
}

//反向打印链表
void print_list_end(list * l, void (*pt)(void * ))//传入一个函数指针pt
{
	if(l->size == 0)
		return;
	node *p = l->last;
	while(NULL != p)
	{
		(*pt)(p->data);//调用print_data(void *)
		p = p->front;
	}
	printf("\n");
}

//销毁链表
void destroy_list(list * l, void (*free_name)(void *))
{
	node *p = NULL;
	while(l->first)
	{
		p = l->first->next;
		(*free_name)(l->first->data);
		free(l->first->data);
		free(l->first);
		l->first=p;
	}
	free(l);
}

list* creat_word_list(char *file, void (*add_num)(void *), int (*cmp_word)(void *, char *, int), void (*insert_word_node)(list *, char *), void (*print_data)(void *), int flag)
{
	FILE *fp; //打开要读取的文件    
	if((fp=fopen(file, "r"))==NULL )      
	{              
		exit(1);    
	}
	//printf("file:%s\n", file); 
	list *my_list=init_list();
	char temp[256]; //临时存放单词的词组
	char *seg = "`~!@#$%^&*()-+{}:=;[]\"\',./\\ \?<>1234567890";
	char *current_word=NULL;
	node *p_node=NULL;
	while(!feof(fp))
	{ 
		fscanf(fp,"%s",temp); 
	//	printf("temp:%s\n", temp);
		current_word=strtok(temp,seg);//p接收当前strtok的字符串的指针
		while(current_word)//判断字符串查找到末尾没
		{	
			if(my_list->first == NULL)
			{
				(*insert_word_node)(my_list, current_word);
				//print_list_begin(my_list, print_data);
			}
			else
			{
			//	print_list_begin(my_list, print_data);
			//	printf("current_word:%s\n", current_word);
				p_node = find_name(my_list, current_word, cmp_word, flag);
			//	printf("p_node:%p\n", p_node);
				if(p_node != NULL)
				{
					
					(*add_num)(p_node->data);
				}
				else
				{
					(*insert_word_node)(my_list, current_word);
				}	
			}
     		//printf("current_word:%s\n", current_word);	
			current_word=strtok(NULL,seg);//接收下一个字符的指针
		}
	}       
	fclose(fp);
	return my_list; 
}


