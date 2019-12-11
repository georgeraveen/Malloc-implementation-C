#include<stdio.h>
#include<stdlib.h>
#include "mymalloc.h"





void *MyMalloc(int s){
	if(s>(MEM-MEM_part)){
		return NULL;
	}
	//x=s;
	
	if(usedst==NULL&&freest==NULL){
		//memory for linkedlists
		sysMEM = &memory[MEM_part];
		//define free list		
		//freest = (struct track*)malloc(sizeof(struct track));
		freest = sysMEM;
		sysMEM+=sizeof(struct track);
		//
		freest->next=NULL;
		freest->prev=NULL;
		freest->size = MEM-MEM_part;
		freest->s_index = 0;	
		
		//used list
		//newnode = (struct track*)malloc(sizeof(struct track));
		newnode = sysMEM;
		sysMEM+=sizeof(struct track);
		//
		newnode->s_index=freest->s_index;
		newnode->size=s;
		newnode->next=NULL;
		newnode->prev=NULL;		
		usedst=newnode;
		//update free list
		freest->s_index+=s;
		freest->size-=s;
		
	}
	else{
		//free list
		ftemp=freest;
		while(ftemp->size<s){
			//MEMORY IS EMPTY
			if(ftemp->next==NULL){
				return NULL;
			}
			//
			ftemp=ftemp->next;
		}
		
		//used list
		utemp=usedst;
		while(utemp->next!=NULL){
			utemp=utemp->next;
		}
		
		
		//free list update
		if(ftemp->next==NULL){
			//newnode for usedlist
			//newnode = (struct track*)malloc(sizeof(struct track));
			newnode = sysMEM;
			sysMEM+=sizeof(struct track);
			//	
			newnode->s_index=ftemp->s_index;
			newnode->size=s;
			newnode->next=NULL;
			newnode->prev=utemp;		
			utemp->next=newnode;
			//update free
			ftemp->s_index+=s;
			ftemp->size-=s;
			
		}
		else{
			//remove ftemp
			if(ftemp->size==s){
				//split and merge free list
				if(ftemp->prev==NULL){
					freest=ftemp->next;
					freest->prev==NULL;
				}
				else{
					ftemp->prev->next=ftemp->next;
					ftemp->next->prev=ftemp->prev;
				}
				//update used list
				ftemp->prev=utemp;
				utemp->next=ftemp;
				ftemp->next=NULL;
				return (void*)&memory[ftemp->s_index];
			}
			else{ //if the free node is bigger than required
				//newnode for usedlist
				//newnode = (struct track*)malloc(sizeof(struct track));
				newnode = sysMEM;
				sysMEM+=sizeof(struct track);
				//
				newnode->s_index=ftemp->s_index;
				newnode->size=s;
				newnode->next=NULL;
				newnode->prev=utemp;		
				utemp->next=newnode;
				//reduce ftemp size
				ftemp->s_index+=s;
				ftemp->size-=s;
			}
			//free(ftemp);
			
		}
	}
	return (void*)&memory[newnode->s_index];
	//printf("%d ",&x);
	//return &x;
}
void MyFree(void *fptr){
	//printf("\nfree%d\n\n",fptr);
	utemp=usedst;
	int *a = (int*)fptr;
	int *b = (int *)&memory[utemp->s_index];
	//printf("\nfree%d %d\n\n",a,b);
	while(((int*)fptr)!=((int *)&memory[utemp->s_index])){
		
		utemp=utemp->next;
	}
	if(utemp->next==NULL && utemp->prev==NULL){
		usedst=NULL;
		freest=NULL;
		//printf("dd");
		return;
	}
	//
	//free from used
	//printf("%d",utemp->s_index);
	if(utemp->prev==NULL){
		usedst=usedst->next;
		usedst->prev=NULL;
	}
	else if(utemp->next==NULL){
		utemp->prev->next=NULL;
		//printf("d %d %d d",utemp->prev->next->s_index,utemp->s_index);
	}
	else{
	
	utemp->prev->next=utemp->next;
	utemp->next->prev=utemp->prev;
	}
	
	//add to free
	utemp->next=freest;
	freest->prev=utemp;
	utemp->prev=NULL;
	freest=utemp;
	
	//defrag
	sort();
	defrag();
	
}
void sort(){
	//sort the free list for defragment
	int a,b;
	for(ftemp=freest;ftemp->next!=NULL;ftemp=ftemp->next){
		for(stemp1=ftemp->next;stemp1!=NULL;stemp1=stemp1->next){
			if(stemp1->s_index<ftemp->s_index){
				a=ftemp->s_index;
				b=ftemp->size;
				ftemp->s_index=stemp1->s_index;
				ftemp->size=stemp1->size;
				stemp1->s_index=a;
				stemp1->size=b;
			}
		}
	}
}
void defrag(){
	ftemp=freest;
	while(ftemp->next!=NULL){
		if(ftemp->s_index+ftemp->size==ftemp->next->s_index){
			ftemp->size+=ftemp->next->size;
			if(ftemp->next->next==NULL){
				ftemp->next=NULL;
			}
			else{
				ftemp->next=ftemp->next->next;
				ftemp->next->prev=ftemp;
			}
		}
		ftemp=ftemp->next;
	}
}
