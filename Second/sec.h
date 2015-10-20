/*Second Assignement Dimopoulos Grigorios */
/*mysortapp*/
/*sec.h*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <sys/times.h>
#include <math.h>
#define SIZEofBUFF 12

/*typos struct gia ta records*/

typedef struct{
	int ssn;
	char FirstName[SIZEofBUFF];
	char LastName[SIZEofBUFF];
	int  income;
}Record;

pid_t fork_ok(void);
Record ** Create_tree(int level,FILE *fl,int atr_num,int start,int stop,Record * array[]/*,double **tita[]*/);
void fprint_rec(FILE * ptr,Record *rec);
void anathesh(Record *target,Record back);
void merge(Record a[], int m, Record b[], int n, Record * sorted[],int atr_num);
void quicksort(Record * x,int first,int last,int atr_num);
