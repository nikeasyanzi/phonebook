#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include IMPL

#define TABLE_SIZE   131072	//estimated, since we have 349900 line in word.txt  we allocate 2^17=131072
#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
	struct timespec diff;
	if (t2.tv_nsec-t1.tv_nsec < 0) {
		diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
		diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
	} else {
		diff.tv_sec  = t2.tv_sec - t1.tv_sec;
		diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
	}
	return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
	FILE *fp;
	int i = 0;
	char line[MAX_LAST_NAME_SIZE];
	struct timespec start, end;
	double cpu_time1, cpu_time2;

	/* check file opening */
	fp = fopen(DICT_FILE, "r");
	if (fp == NULL) {
		printf("cannot open the file\n");
		return -1;
	}


	/* build the entry */
#if defined(HASH)
	clock_gettime(CLOCK_REALTIME, &start);
	entry  *pHead;
	entry  **e=malloc(sizeof(entry *)*TABLE_SIZE );
	pHead = (entry *) malloc(sizeof(entry)* TABLE_SIZE);


	for(i=0;i<TABLE_SIZE;i++){
		e[i]=&pHead[i];
		//	printf("i=%d , phead[i]=%x &phead[i]=%x\n",i, pHead[i],&pHead[i]);
		pHead[i].pNext=NULL;
	}
	__builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry *)*TABLE_SIZE + sizeof(entry)* TABLE_SIZE);

	printf("size of entry : %lu bytes\n", sizeof(entry));
	i=0;
	while (fgets(line, sizeof(line), fp)) {
		while (line[i] != '\0')
			i++;
		line[i - 1] = '\0';
		i = 0;
		append(line, &e[i]);
	}
	clock_gettime(CLOCK_REALTIME, &end);

#else
	clock_gettime(CLOCK_REALTIME, &start);
	entry  *pHead;
	entry  *e;
	pHead = (entry *) malloc(sizeof(entry));
	e = pHead;
	e->pNext = NULL;
	printf("size of entry : %lu bytes\n", sizeof(entry));

	__builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
	while (fgets(line, sizeof(line), fp)) {
		while (line[i] != '\0')
			i++;
		line[i - 1] = '\0';
		i = 0;
		e=append(line, e);
	 }

	clock_gettime(CLOCK_REALTIME, &end);
#endif
	cpu_time1 = diff_in_second(start, end);
	/* close file as soon as possible */
	fclose(fp);


	/* the givn last name to find, here is to validate whether the find function is implement or not */
	char input[MAX_LAST_NAME_SIZE] = "zyxel";
#if defined(HASH)
	for(i=0;i<TABLE_SIZE;i++){
		e[i]=&pHead[i];
	}
	assert(findName(input, &e[0]) &&
			"Did you implement findName() in " IMPL "?");
	//e[0] = &pHead[0];
	assert(0 == strcmp(findName(input, &e[0])->lastName, "zyxel"));

#else
	e = pHead;
	assert(findName(input,e) &&
			"Did you implement findName() in " IMPL "?");
	e = pHead;
	assert(0 == strcmp(findName(input,e)->lastName, "zyxel"));

#endif

#if defined(__GNUC__)
	__builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif

	/* compute the execution time */
	clock_gettime(CLOCK_REALTIME, &start);
	findName(input, e);
	clock_gettime(CLOCK_REALTIME, &end);
	cpu_time2 = diff_in_second(start, end);

	FILE *output;
#if defined(OPT)
	output = fopen("opt.txt", "a");
#elif defined(HASH)
	output = fopen("hash.txt", "a");
#else
	output = fopen("orig.txt", "a");
#endif
	fprintf(output, "append() findName() %lf %lf\n", cpu_time1, cpu_time2);
	fclose(output);

	printf("execution time of append() : %lf sec\n", cpu_time1);
	printf("execution time of findName() : %lf sec\n", cpu_time2);

#if defined(HASH)

#else

	if (pHead->pNext) free(pHead->pNext);
	free(pHead);
#endif
	return 0;
}
