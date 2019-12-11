#include<stdio.h>
#include<stdlib.h>
#define MEM 25000
#define MEM_part 9600

char memory[MEM];
//int x=9;
struct track{
	int s_index;
	int size;
	struct track *next;
	struct track *prev;
	
}*freest,*usedst,*ftemp,*utemp,*newnode, *stemp1, *stemp2;

void sort();
void defrag();
void *sysMEM;
void *MyMalloc(int s);
void MyFree(void *fptr);
