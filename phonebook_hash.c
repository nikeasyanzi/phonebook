#include <stdlib.h>
#include <string.h>

#include "phonebook_hash.h"
#define TABLE_SIZE   2^17	//estimated, since we have 349900 line in word.txt  we allocate 2^17=131072
//total size = 2^17 * 24 byte 

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
 {

 	 unsigned int idx=BKDRhash(lastname);

    /* TODO: implement */
     
     entry *ptr=&pHead[idx];
     
     while (ptr != NULL) {
        if (strcasecmp(lastname, ptr->lastName) == 0)
            return ptr;
        ptr = ptr->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
	unsigned int idx=BKDRhash(lastName);

	entry *ptr=&e[idx];
	if(ptr==NULL){
		ptr = (entry *) malloc(sizeof(entry));
	}

	else {

		while (ptr->pNext != NULL) {
			ptr=ptr->pNext;
		}
		ptr->pNext = (entry *) malloc(sizeof(entry));
		ptr=ptr->pNext;
	}
	strcpy(ptr->lastName, lastName);
	ptr->pNext = NULL;

	return e;
}

unsigned int BKDRhash(char *key)
{//BKDRhash函数
	unsigned int seed = 131;//31 131 1313 13131 131313
	unsigned int hash = 0;
	unsigned i=0;

	while(*(key+i) != '\0') {    
		hash = hash * seed + *(key+i);
		i++;
	}

	//return hash % TABLE_SIZE;
	return hash & 0X0001FFFF;
}






