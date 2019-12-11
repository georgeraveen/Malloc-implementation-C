

#include<stdio.h>
#include "mymalloc.c"

int prlist(){
	//print lists
	if(usedst==NULL){
		printf("mem free\n");
		return 1;
	}
	utemp=usedst;
	ftemp=freest;
	printf("\nused\n%d %d\n",utemp->s_index,utemp->size);
	while(utemp->next!=NULL){
		utemp=utemp->next;
		printf("%d %d\n",utemp->s_index,utemp->size);
	}
	printf("free\n%d %d\n",ftemp->s_index,ftemp->size);
	while(ftemp->next!=NULL){
		ftemp=ftemp->next;
		printf("%d %d\n",ftemp->s_index,ftemp->size);
	}
}
int main(){
	
	
	int *p,*t,*q,*r;
	float *w;
	p= (int*)MyMalloc(3);
	//prlist();
	
	//prlist();
	q= (int*)MyMalloc(4);
	//printf("dd");
	//prlist();
	//*q=598;
//	*p=78;
//	printf("%d\n",*p);
	//printf("\n %d %d \n %d %d\n\n\n",*p,(p),*q,q);
	
	//prlist();
	r= (int*)MyMalloc(5);
	//prlist();
	MyFree(q);
	prlist();
	MyFree(p);
	prlist();
	w= (float*)MyMalloc(sizeof(float));
	
	*w=123.45;
//	*r=34;
	printf("\n %d %d \n %f %d\n\n\n",*r,(r),*w,w);
	
	//prlist();
	
	
	p= (int*)MyMalloc(6);
	//*p=12345;
	//printf("%d\n",*p);
	
	//printf("hh");
	prlist();
	//printf("%d",sizeof(struct track));
	
	
	
	
	
	
	return 0;
}

