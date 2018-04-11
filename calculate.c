#include <stdio.h>
#include <stdlib.h>

int main(void)
{

	char *fparr[]={"orig.txt","opt.txt","hash.txt"};
	int i=0;
	int j;
	char append[50], find[50];
	double sum_a[3], sum_f[3], orig_a, orig_f;
	for(j=0;j<3;j++){

		FILE *fp = fopen(fparr[j], "r");
		sum_a[j]=0;
		sum_f[j]=0;
		for (i = 0; i < 100; i++) {
			if (feof(fp)) {
				printf("ERROR: You need 100 datum instead of %d\n", i);
				printf("run 'make run' longer to get enough information\n\n");
				exit(0);
			}
			fscanf(fp, "%s %s %lf %lf\n", append, find,&orig_a, &orig_f);
			sum_a[j] += orig_a;
			sum_f[j] += orig_f;
		}
		fclose(fp);
	}

	FILE *output = fopen("output.txt", "w");
	if (!output) {
		printf("ERROR opening outputut \n");
		exit(0);
	}

	fprintf(output, "append() %lf %lf %lf\n", sum_a[0] / 100.0, sum_a[1] / 100.0, sum_a[2]/100.0);
	fprintf(output, "findName() %lf %lf %lf", sum_f[0] / 100.0, sum_f[1] / 100.0),sum_f[2]/100.0;
	fclose(output);

	/*
	   FILE *fp = fopen("orig.txt", "r");
	   FILE *output = fopen("output.txt", "w");
	   if (!fp) {
	   printf("ERROR opening input file orig.txt\n");
	   exit(0);
	   }
	   int i = 0;
	   char append[50], find[50];
	   double orig_sum_a = 0.0, orig_sum_f = 0.0, orig_a, orig_f;
	   for (i = 0; i < 100; i++) {
	   if (feof(fp)) {
	   printf("ERROR: You need 100 datum instead of %d\n", i);
	   printf("run 'make run' longer to get enough information\n\n");
	   exit(0);
	   }
	   fscanf(fp, "%s %s %lf %lf\n", append, find,&orig_a, &orig_f);
	   orig_sum_a += orig_a;
	   orig_sum_f += orig_f;
	   }
	   fclose(fp);

	   fp = fopen("opt.txt", "r");
	   if (!fp) {
	   fp = fopen("orig.txt", "r");
	   if (!fp) {
	   printf("ERROR opening input file opt.txt\n");
	   exit(0);
	   }
	   }
	   double opt_sum_a = 0.0, opt_sum_f = 0.0, opt_a, opt_f;
	   for (i = 0; i < 100; i++) {
	   if (feof(fp)) {
	   printf("ERROR: You need 100 datum instead of %d\n", i);
	   printf("run 'make run' longer to get enough information\n\n");
	   exit(0);
	   }
	   fscanf(fp, "%s %s %lf %lf\n", append, find,&opt_a, &opt_f);
	   opt_sum_a += opt_a;
	   opt_sum_f += opt_f;
	   }
	   fprintf(output, "append() %lf %lf\n",orig_sum_a / 100.0, opt_sum_a / 100.0);
	   fprintf(output, "findName() %lf %lf", orig_sum_f / 100.0, opt_sum_f / 100.0);
	   fclose(output);
	   fclose(fp);
	   */

	return 0;
}
