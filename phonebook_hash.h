#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define HASH 1


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
} entry;

entry *findName(char lastname[], entry **pHead);
entry *append(char lastName[], entry *e[]);
unsigned int BKDRhash(char *key);

#endif
