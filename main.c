#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"double_list.h"
#include <unistd.h>
#include <time.h>
#include <getopt.h>
typedef struct word_info
{
	int num;
    char *name;
}word;

void print_data(void * p)
{
        word * pp = p;
        printf("%-20s%d\n", pp->name, pp->num);
}

void add_num(void * p)
{
	 word * pp = p;
	(pp->num)++;
}

int cmp_word(void * p, char * current, int flag)
{
	word * pp = p;
//	printf("cmp_current:%s\n", current);
//	printf("pp->name:%s\n", pp->name);
//	printf("pp->num:%d\n", pp->num);
//	printf("!strcasecmp:%d\n", !strcasecmp(pp->name, current));
	if(flag == 1)
		return !strcasecmp((pp->name), current);
	else
		return !strcmp((pp->name), current);
}

void insert_word_node(list *l, char *p)
{	
	word *word1 = (word *)malloc(sizeof(word));
	if(word1 == NULL)
		return;
	word1->num = 1;
	word1->name = (char*)malloc(sizeof(char)*strlen(p));
	if(word1->name == NULL)
	{
		free(word1);
		return;
	}	
	strcpy(word1->name, p);
	insert_back(l, word1);
}

int sort_list_num(void * p1, void * p2)
{
	word * pp1 = p1;
	word * pp2 = p2;
	if(pp1->num > pp2->num)
		return 1;
	else if(pp1->num == pp2->num)
	{
		if(*(pp1->name) > *(pp2->name))
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

int sort_list_name(void * p1, void * p2)
{
	word * pp1 = p1;
	word * pp2 = p2;
	if(*(pp1->name) > *(pp2->name))
		return 1;
	else if(*(pp1->name) == *(pp2->name))
	{
		if((pp1->num) > (pp2->num))
			return 1;
		else
			return 0;
	}		
	else
		return 0;		
}

void free_name(void * p )
{
	word * pp = p;
	free(pp->name);
}

void print_usage(FILE *stream)  
{  
    fprintf(stream, "Usage: option [ dev... ] \n");  
    fprintf(stream, 
            "\t-Y  --yes\n"  
            "\t-N  --no\n" 
            "\t-h  --help\n"  
            "\t-l  --location order\n" 
			"\t-d  --dictionary order\n"
            "\t-n  --number order\n"
			"\t-p  --positive order\n"
            "\t-r  --reverse order\n"
			"\t-f  --file input\n"
            "\t-w  --write file\n"
			);  
    exit(0);  
}
const char *short_options = "YNhldnprf:w:";
const struct option long_options[] = {  
	{ "yes", 0, NULL, 'Y'},
	{ "no", 0, NULL, 'N'},
	{ "help", 0, NULL, 'h'},  
	{ "location", 0, NULL, 'l' },  
	{ "dictionary", 0, NULL, 'd' },  
	{ "number", 0, NULL, 'n'},
	{ "positive order", 0, NULL, 'p'},
	{ "reverse order", 0, NULL, 'r'},
	{ "file", 1, NULL, 'f'},
	{ "write", 1, NULL, 'w'},
	{ 0, 0, 0, 0},  
};

int flag_case = 0;
int flag_sort = 0;
int main(int argc, char *argv[])
{ 
	clock_t start = 0;
	clock_t stop = 0;
	double duration;
	start = clock();
	    
	list *my_list = NULL;
//	for(int i=0; i<argc; ++i)
//	{
//		printf("%s\n", argv[i]);
//	}

	int option;
	char *p_opt = NULL;
	while ((option = getopt_long(argc, argv, short_options, long_options, NULL)) != -1)
	{
		switch (option) 
		{
			case 'Y':
				printf("忽略大小写\n");
				flag_case = 1;
				break;
			case 'N':
				printf("不忽略大小写\n");
				flag_case = 0;
				break;
			case 'h':					//显示帮助信息
				printf("optarg:%s\n", optarg);
				printf("optind:%d\n", optind);
				printf("opterr:%d\n", opterr);
				printf("optopt:%d\n", optopt);
				print_usage(stdout);     
				break;
			case 'l':					//按照位置排序
				if(flag_sort == 1)
				{
					printf("输入错误！只能指定一种排序方式\n");
					break;
				}
				else
					flag_sort =1;
				print_list_begin(my_list, print_data);
					
				printf("optarg:%s\n", optarg);
				printf("optind:%d\n", optind);
				printf("opterr:%d\n", opterr);
				printf("optopt:%d\n", optopt);
				break;
			case 'd':					//按照字典排序
				if(flag_sort == 1)
				{
					printf("输入错误！只能指定一种排序方式\n");
					break;
				}
				else
					flag_sort =1;
				printf("按照字典序\n");
				Sort_List(my_list, sort_list_name);

				printf("optarg:%s\n", optarg);
				printf("optind:%d\n", optind);
				printf("opterr:%d\n", opterr);
				printf("optopt:%d\n", optopt);
				break;
			case 'n':					//按照次数排序
				if(flag_sort == 1)
				{
					printf("输入错误！只能指定一种排序方式\n");
					break;
				}
				else
					flag_sort =1;
				printf("按照次数\n");
				Sort_List(my_list, sort_list_num);

				printf("optarg:%s\n", optarg);
				printf("optind:%d\n", optind);
				printf("opterr:%d\n", opterr);
				printf("optopt:%d\n", optopt);
				break;
			case 'p':					//正序输出
				printf("正序输出\n");	
				print_list_begin(my_list, print_data);
				printf("optarg:%s\n", optarg);
				printf("optind:%d\n", optind);
				printf("opterr:%d\n", opterr);
				printf("optopt:%d\n", optopt);
				break;
			case 'r':					//反序输出
				printf("反序输出\n");
				print_list_end(my_list, print_data);
				printf("optarg:%s\n", optarg);
				printf("optind:%d\n", optind);
				printf("opterr:%d\n", opterr);
				printf("optopt:%d\n", optopt);
				break;
			case 'f':
				my_list=creat_word_list(optarg, add_num,cmp_word, insert_word_node, print_data, flag_case);
				printf("optarg:%s\n", optarg);
				printf("optind:%d\n", optind);
				printf("opterr:%d\n", opterr);
				printf("optopt:%d\n", optopt);
				break;
			case 'w':					//写入文件
				freopen(optarg, "w", stdout);//标准输出被重定向到文件
				print_list_begin(my_list, print_data);
		  		freopen("/dev/tty","w",stdout);//恢复到标准输出

				printf("共统计 %d  个单词\n", my_list->size);
				printf("optarg:%s\n", optarg);
				printf("optind:%d\n", optind);
				printf("opterr:%d\n", opterr);
				printf("optopt:%d\n", optopt);
				break;
			case '?':
				printf("optopt=%c, optarg=%s\n", optopt, optarg);
				break;
			default :
				printf("optopt = %c\n", (char)optopt);
				printf("opterr = %d\n", opterr);
				fprintf(stderr, "usage: %s [-t nsecs] [-n] name\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}	
	
	for(int i=0; i<argc; ++i)
	{
		printf("%s\n", argv[i]);
	}
	printf("共统计 %d 个单词\n", my_list->size);
	destroy_list(my_list, free_name);
	my_list = NULL;
	stop = clock();
	duration = (double)((stop - start)/1000);
	printf("程序运行时间为：%lf\n",duration);
	fclose(stdout);
	
	
	return 0;
}

