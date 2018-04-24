#include <stdio.h>

#define MAX_LAST_NAME_SIZE 16
#define TABLE_SIZE 131072

typedef struct __PHONE_BOOK_DETAIL {
	char firstName[16];
	char email[16];
	char phone[10];
	char cell[10];
	char addr1[16];
	char addr2[16];
	char city[16];
	char state[2];
	char zip[5];


} __PHONE_BOOK_DETAIL;

typedef struct __PHONE_BOOK_ENTRY {
	char lastName[MAX_LAST_NAME_SIZE];

	__PHONE_BOOK_DETAIL *detail;

	struct __PHONE_BOOK_ENTRY *pNext;
	//__PHONE_BOOK_DETAIL *aa;

} entry;

int main()
{

	int i;

	entry  **pHead;
	entry  *e;
	pHead = (entry **) malloc(sizeof(entry *)*TABLE_SIZE + sizeof(entry)* TABLE_SIZE);

	for(i=0;i<TABLE_SIZE;i++){
		pHead[i]=  (pHead+ sizeof(entry*)*TABLE_SIZE) + sizeof(entry)*i   ;
	//	e= (pHead+ TABLE_SIZE) ;
	//	pHead[i]=&e[i];
		//printf("i=%d , phead[i]=%x &phead[i]=%x, sizeof (entry)=%d sizeof(e)=%d \n",i, pHead[i],&pHead[i],sizeof(entry),sizeof(e));
		printf("i=%d , phead[i]=%p &phead[i]=%p, sizeof (entry)=%d sizeof(e)=%d \n",i, pHead[i],&pHead[i],sizeof(entry),sizeof(e));
		//pHead[i]->pNext=NULL;
	}

	printf("Hello World");

	return 0;

}
