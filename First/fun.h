/*First Assignement Dimopoulos Grigorios */
/*Waiting queue*/
/*fun.h*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# include <stdlib.h>
# include <time.h>
typedef struct node node;
typedef struct record record;
/*typos struct gia ta nodes tou dentrou*/
struct node 
{
        int afm;
        float money;
        node * right;
        node * left;
        node * parent;
};
/*typos struct gia ta records*/
struct record
{
	char surname[26];
        char name[16];
        char town[21];
        char prefecture[4];
	int afm;
        float money;
	record *  right;
	record * down;
	record * next;
};
node * head;/*the root of the tree*/
node * last;/*last element of the tree*/
node * current;

record *left_top_p; /*prwto stoixeio ths bohthitikhs domhs gia anazhthsh bash to prefecture*/
record * max_to_min;/*prwto stoixeio gia anazhthsh max to min*/
record * prefe[70];/*bohthitikos pinakas gia thn ulopoihsh tou stats prefecture  se  O(1)*/
int ins(int afm,char* name,char* surname,char* town,char* prefecture,float money);
int insert(node * nod,node *nod2,int i);
void swap(node * first,node *second);
void record_insert(record * rec);
void record_insert_max(record *rec);
int del(FILE * invoicefile);
void delete_all(int afm,record * re);
int find_last(node * nod,int i);
void pretty_print(node * nod);
void perprint(record * rec);
void mtmprint(record * rec);
void print_s();
void top();
int afm_f(node * n,record * back,int i,int afm);
record * f_rec(int afm);
void lookup(int af);
int stats(char * pre,float * sum);
void sumstats();
void print_t();
void exit_n(FILE * ptr);
void load(FILE * ptr);
int next_word(FILE * fp,char *s);
void append(char* s, char c);
void top_pr(float percentile);
int kanonik(char * pre);
void ref_the_ptrs();
int openf(FILE * fp,FILE *ip,FILE *df);
