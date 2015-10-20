/*First Assignement Dimopoulos Grigorios */
/*Waiting queue*/
/*help.c*/
#include "fun.h"

/*ins*/
/*--------------------------------------------------------------*/
/*Synarthsh eisagwghs enos ofeileth sto systhma,tou dentrou oso kai stis dyo bohthitikes domes syndemenh lista(max to min) kai disdiastata 
sundemenh lista me bash to prefecture*/
int ins(int afm,char* name,char* surname,char* town,char* prefecture,float money)
{	
	
	record* rec;
	node * nod;
	rec=malloc(sizeof(record));
	if(rec==NULL)
	{
		printf("Failed to allocate memory.\n");
		return 0;
	}
	nod=malloc(sizeof(node));
	if(nod==NULL)
        {
                printf("Failed to allocate memory.\n");
                return 0;
        }
	rec->afm=afm;
	strcpy(rec->name,name);
	strcpy(rec->surname,surname);
	strcpy(rec->town,town);
	strcpy(rec->prefecture,prefecture);
	rec->money=money;
	rec->right=NULL;
	rec->down=NULL;
	rec->next=NULL;
	nod->money=money;
	nod->afm=afm;
	nod->left=NULL;
	nod->right=NULL;
	nod->parent=NULL;
	insert(head,nod,0);/*inserting the node at the tree with this function*/
        while((nod->parent)->money<nod->money){swap(nod->parent,nod);nod=nod->parent;} /*kane ths aparethtes allages*/ 
	record_insert(rec);/*eishgage to record sthn domh based on prefectures*/
	record_insert_max(rec);/*eishgage to record sthn domh max to min*/
	ref_the_ptrs();/*kane refresh ton bohthitiko pinaka gia mellontikh grghgorh apanthsh tou stats prefecture*/
	return 1;  
}
/*----------------------------------------------------------------------------*/
/*function for inserting the node to the tree*/
int insert(node * nod,node *nod2,int i)
{
        int k=0,flag=0;
	int l;
        node * next=head;
        while(next!=NULL)
        {
                next=next->right;
                if (next!=NULL)
                k++;
        }
        if((nod==head)&&(nod==NULL)&&(i==k))
        {
                head=nod2;
                nod2->parent=head;
		return 1 ;
        }
	else
	{
       	 	if((nod->left)!=NULL)
        	{
                	flag=1;
			l=i+1;
                	if(insert(nod->left,nod2,l))return 1;
			
        	}
        	if((nod->right)!=NULL)
        	{
			l=i+1;
                	if(insert(nod->right,nod2,l))return 1;
        	}
        	if(((nod->left)==NULL)&&(i==k))
        	{
                	nod->left=nod2;
                	nod2->parent=nod;
			return 1;
        	}
        	if(((nod->right)==NULL)&&(flag==1))
        	{
                	nod->right=nod2;
                	nod2->parent=nod;
			return 1;
        	}
	}
	return 0;
}

/*--------------------------------------------------*/
void swap(node * first,node *second)
{
        int temp;
        float temp2;
	temp=first->afm;
	first->afm=second->afm;
	second->afm=temp;
	temp2=first->money;
	first->money=second->money;
	second->money=temp2;
}

/*--------------------------------------------------*/
/*function for inscerting the record at the help structure based on prefectures*/
void record_insert(record * rec)
{
	record* cur;
	cur=left_top_p;
	if (cur!=NULL)
	{	
		while(strcmp(rec->prefecture,cur->prefecture))
		{
			if((cur->right)!=NULL)
			{
				cur=cur->right;
			}
			else
			{
				cur->right=rec;
				return;
			}
		}
		while(cur->down!=NULL)
		{
			cur=cur->down;
		}
		cur->down=rec;
		return;
	}
	else
	{
		left_top_p=rec;
		return;
	}
}
/*o tropos pou douleuei h parapanw bohthitikh domh einai oti koitaei to prefecture tou kathe stoixeiou kai analoga ftiaxnei mia domh opou sthn
prwth orizontia seira einai mia syndemenh lista pou oso pame pros ta deksia arxizontas apo panw aristera kathe epomeno stoixeio exei diaforetiko
prefecture apo ola ta prohgoumena kai an katauthasoun stoixeia me kapoio hdh uparxon stoixeio me to idio prefecture mpainoun katw apo to idh uparxon
etsi xrhsimopoiw tous deiktes right gia na phgainw deksia kai tous deiktes down gia na phgainw katw*/
/*-------------------------------------------------------------*/
/*eisagh sthn domh max to min to record 
edw xrhsimopoioume to deikth next*/
void record_insert_max(record *rec)
{
	record * cur;
	record * previous;
	cur=max_to_min;
	previous=NULL;
	if(cur!=NULL)
	{
		while((cur->money)>(rec->money))
		{
			if((cur->next)!=NULL)
			{
				previous=cur;
				cur=cur->next;
			}
			else
			{
				cur->next=rec;
				return;
			}
		}
		if(previous!=NULL)previous->next=rec;
		rec->next=cur;
		if (previous==NULL)max_to_min=rec;
	}
	else
	{
		max_to_min=rec;
		return;
	}
}


/*del*/
/*A function that deletes the person with the biggest amount    */
/*and makes the nessecery changes to the structure and  add this*/
/*person to the invoice file returns !1 at error cases*/ 
int del(FILE * invoicefile)
{
        record egr;
	time_t timer;
    	char buffer[25];
    	struct tm* tm_info;
    	time(&timer);
	if (head!=NULL)
	{
		delete_all(head->afm,&egr);
        	if (invoicefile!=NULL)fprintf(invoicefile,"%d %s %s %s %s %f\t",egr.afm,egr.name,egr.surname,egr.town,egr.prefecture,egr.money);
		tm_info = localtime(&timer);
        	strftime(buffer, 25, "%Y:%m:%d%H:%M:%S", tm_info);
		if (invoicefile!=NULL)fprintf(invoicefile,"%s \n",buffer);
	}
	ref_the_ptrs();
        return 1;
}
/*--------------------------------------------------------------*/
/*a helping function of the del function that deletes every record and every node with afm and return its characteristics at record * re*/
void delete_all(int afm,record * re)
{
	record * cur;
	record * cur2;
	record * previous=NULL;
	cur=max_to_min;
	cur2=left_top_p;
	int flag=0;
	node * nod;
	record * previous2=NULL;
	record * previous3=NULL;
	record * cur3=left_top_p;
	while(cur->next!=NULL)
	{	
		if (cur->afm==afm)break;
		previous=cur;
		cur=cur->next;
	}
	if(cur==NULL)
	{
		printf("The record you want to delete doesn't exist .\n");
		return;
	}
	else
	{
		if (previous!=NULL){previous->next=cur->next;}
		else {max_to_min=cur->next;}
	}
	while(cur3!=NULL)
	{
		cur2=cur3;
		previous2=NULL;
		while(cur2!=NULL)
		{
			if(cur2->afm==afm)
			{
				flag=1;
				break;
			}
			previous2=cur2;
			cur2=cur2->down;	
		}
		if (flag==1){break;}
		else  
		{
			previous3=cur3;
			cur3=cur3->right;
		}
	}
	if((previous3==NULL)&&(cur2==cur3))
	{
		if(cur3->down!=NULL)
		{
			left_top_p=cur3->down;
			(cur3->down)->right=cur3->right;
		}	
		else
		{
			left_top_p=cur3->right;
		}
	}
	else if((cur2==cur3)&&(previous3!=NULL))
	{
		previous3->right=cur3->down;
		if(cur3->down!=NULL){(cur3->down)->right=cur3->right;}
		else  previous3->right=cur3->right;
	}
	else if(cur2!=cur3)
	{
		previous2->down=cur2->down;
	}
	strcpy(re->name,cur2->name);
	strcpy(re->surname,cur2->surname);
	strcpy(re->prefecture,cur2->prefecture);
	strcpy(re->town,cur2->town);
	re->afm=cur2->afm;
	re->money=cur2->money;
	last=NULL;
	/*aparethtes allages kai diagrafh sto dentro*/
	find_last(head,0);/*a function that finds the last node of the tree and give its adrees to the gloabal last pointer*/
	swap(head,last);
	if((last->parent)->right==last)last->parent->right=NULL;
	else if ((last->parent)->left==last)last->parent->left=NULL;
	if(head==last)head=NULL;
	free(last);
	free(cur2);
	nod=head;
	while(nod!=NULL)
	{
		if((nod->left!=NULL)&&(nod->right!=NULL))
		{
			if(((nod->left)->money)>(nod->money)||((nod->right)->money)>(nod->money))
        		{
                		if (((nod->left)->money)>((nod->right)->money))
                		{
                        		swap(nod,nod->left);
					nod=nod->left;          
                		}	
                		else if(((nod->left)->money)<((nod->right)->money))
                		{
                        		swap(nod,nod->right);
					nod=nod->right;
                		}
			
			}
			else break;
        	}
		else if((nod->left!=NULL)&&(nod->right==NULL))
		{
			if(((nod->left)->money)>(nod->money))
                	{
                        	swap(nod,nod->left);
				nod=nod->left;
                	}
			else break;

		}
		else if((nod->left==NULL)&&(nod->right==NULL))
		{
			break;
		}
	}
	return;
}

/*--------------------------------------------------*/

int  find_last(node * nod,int i)
{

        int k=0,flag=0;
	int num;
        node * next;
	next=head;
        while(next!=NULL)
        {
                next=next->left;
                if (next!=NULL)
                k++;
        }
        if((nod==head)&&(nod==NULL)&&(i==k))
        {
                last=head;
		return 1;
        }
        if((nod->right)!=NULL)
        {
                flag=1;
		num=i+1;
                if (find_last(nod->right,num)==1)return 1;
        }
        if((nod->left)!=NULL)
        {
		num=i+1;
                if (find_last(nod->left,num)==1)return 1;
        }
        if(((nod->right)==NULL)&&(i==k)&&((nod->left)==NULL))
        {
                last=nod;
		return 1;
        }
	return 0;
}
/*------------------------------------------------------------------*/
/*FUNCTIONS USED FOR DEBUGGING,PRINTING SOMEHOW THE TREE AND THE OTHER HELPING STUCTS!!!NOT A PART OF THE ASSIGNEMENT!!!*/
/*IF ITS A PROBLEM FOR YOU JUST ERASE THEM*/
/*=================================================================================*/
/*__________________________________________________________________________________*/
/*
void print_s()
{
	record* cur;
	node * nod;
	nod=head;
	cur=left_top_p;
	printf("\n\n");
	printf("__________________________________________________________________\n");
	printf("||The tree structure is like this.||\n\n");
	pretty_print(head);
	printf("\n\n");
	printf("||The prefecture list is like this.||\n\n");
	perprint(left_top_p);
	printf("\n\n");
	printf("||The max to min list is like this.||\n\n");
	mtmprint(max_to_min);
	printf("\n\n");
	printf("__________________________________________________________________\n");
}

void pretty_print(node * nod)
{
	if (nod!=NULL)printf("%d.\n",nod->afm);
	if(nod!=NULL)
	{
		printf("LEFT.\n");
		if (nod->left!=NULL)pretty_print(nod->left);
		printf("RIGHT.\n");
		if (nod->right!=NULL)pretty_print(nod->right);
	
	}
	return;
}
void perprint(record * rec)
{
	record * reco;
	reco=left_top_p;
	int flag=0;
	int flag2=0;
	if (rec==NULL)return;
	if (reco!=NULL)
	{
		while(reco!=NULL)
		{
			if (reco==rec)flag=1;
			reco=reco->down;
			if (reco==NULL)break;
		}
	}	
	if(rec!=NULL)printf("-%d-",rec->afm);
	if (rec->right!=NULL)
	{
		flag2=1;
		perprint(rec->right);
	}
	if((flag)||((((rec->right)==NULL)||flag2)&&(rec->down!=NULL)))
	{
		printf("\n");
		perprint(rec->down);
	}
	else
	{
		printf(" ");
	}
	return;
}
void mtmprint(record * rec)
{
	while(rec!=NULL)
	{
		printf("%d--",rec->afm);
		rec=rec->next;
	}
	printf("\n\n");
}
*/
/*FUNCTIONS USED FOR DEBUGGING,PRINTING SOMEHOW THE TREE AND THE OTHER HELPING STUCTS!!!NOT A PART OF THE ASSIGNEMENT!!!*/
/*IF ITS A PROBLEM FOR YOU JUST ERASE THEM*/
/*=================================================================================*/
/*__________________________________________________________________________________*/

/*Printing the person at the top of the tree*/
void top()
{
        if(max_to_min!=NULL)
	printf("%d %s %s %s %s %f\n",max_to_min->afm,max_to_min->name,max_to_min->surname,max_to_min->town,max_to_min->prefecture,max_to_min->money);
}
/*A helping struct that gives you all the data about the person with afm*/
int afm_f(node * n,record * back,int i,int afm)
{

        int k=0;
        if (n==NULL)
        {
                return -1;
        }
        else if(n->afm==afm)
        {
                back=f_rec(n->afm);
		if(back!=NULL)printf("%d %s %s %s %s %f\n",back->afm,back->name,back->surname,back->town,back->prefecture,back->money);
                else printf("Error cant find the record .\n");
                return i;
        }
        k=afm_f(n->left,back,++i,afm);
	i--;
        if(k<=0)
        k=afm_f(n->right,back,++i,afm);
	i--;
        return k;
}
/*a function that finds the record with afm */
record * f_rec(int afm)
{
	record * cur;
	cur=max_to_min;
	while(cur!=NULL)
	{
		if(cur->afm==afm)return cur;
		cur=cur->next;
	}
	return NULL;
}
/*printing the person with afm=af and returns its height from the root of the tree*/
void lookup(int af)
{
        record *back;
        int level;
        level=afm_f(head,back,0,af);
        if (level==-1)
        {
                printf("The person doesn't exist.\n");
                return;
        }
        else
        {
                printf("The person with afm %d is at height %d from the root.\n",af,level);
		return;
        }
}
/*Printing the persons starting from max that they have together precentile */
void top_pr(float percentile)
{
	float tmp;
	float	sum=0;
	record * temp=max_to_min;
	while(temp!=NULL){sum=sum+temp->money;temp=temp->next;}
	temp=max_to_min;
	tmp=percentile;
	if (sum!=0)tmp=tmp-(temp->money)/sum;
	while (tmp>0)
	{
		printf("%d %s %s %s %s %f\n",temp->afm,temp->name,temp->surname,temp->town,temp->prefecture,temp->money);
                temp=temp->next;
		if (temp==NULL)break;
		if (sum>0)tmp=tmp-(temp->money)/sum;		
	}	
	return;
}
/*Give the stats for the prefecture pre*/
int stats(char * pre,float * sum)
{
	record * cur= prefe[kanonik(pre)];
	int i=0;
	float aver=0;
	printf("Prefecture : %s .\n",pre);
	while(cur!=NULL)
	{
		(*sum)=(*sum)+cur->money;
		i++;
		printf("	");
		printf("%d:",i);
		printf("%d %s %s %s %s %f\n",cur->afm,cur->name,cur->surname,cur->town,cur->prefecture,cur->money);
		cur=cur->down;
	}
	if (i!=0)aver=((*sum)/i);
	else {printf("No data for the given prefecture .\n");return i;}
	printf("The average amount of money that we are going to gather per person is %f .\n",aver);
	printf("The population at this prefecture is %d .\n",i);
	return i;
}
/*Give stats from all the prefectures*/
void sumstats()
{
	record * cur=left_top_p;
	float sum_f=0;
	float sum=0;
	int pop=0;
	while(cur!=NULL)
	{
		pop=pop+stats(cur->prefecture,&sum);
		sum_f=sum_f+sum;
		printf("At prefecture: %s  the overall amount of money is %f .\n",cur->prefecture,sum);
		sum=0;
		cur=cur->right;
	}
	printf("The overall amount of money is %f and the population of the people in the system is %d .\n",sum_f,pop);
	return;
}
/*Print tree*/
void print_t()
{
	record * cur=max_to_min;
	int i=0;
	record *back;
        int level;
	printf("Printing all contents of the tree(max to min).\n");
	printf("...\n");
	while(cur!=NULL)
	{
		i++;
		level=afm_f(head,back,0,cur->afm);
		printf("+-------------------------(%d)--------------------------------+\n",i);
		printf("\t (AFM):%d.\n",cur->afm);
		printf("\t (AMOUNT OF MONEY):%f.\n",cur->money);
		printf("\t (LEVEL AT THE TREE):%d.\n",level);
		printf("+-------------------------(%d)--------------------------------+\n",i);
		cur=cur->next;
	}
}
/*exit the program and save or not at a file for future load*/
void exit_n(FILE * ptr)
{
	record * cur=max_to_min;
	while(cur!=NULL)
	{
		if(ptr!=NULL)
		{
			fprintf(ptr,"%d %s %s %s %s %f\n",cur->afm,cur->name,cur->surname,cur->town,cur->prefecture,cur->money);
		}
		cur=cur->next;
               	del(NULL);
	}
	return;
}
/*load from a file saved data */
void load(FILE * ptr)
{
	char s[50];
	record tmp;
	int i=0;
	while(next_word(ptr,s))
	{
	
		tmp.afm=atoi(s);
		next_word(ptr,s);
		strcpy(tmp.name,s);
		next_word(ptr,s);
		strcpy(tmp.surname,s);
		next_word(ptr,s);
		strcpy(tmp.town,s);
		next_word(ptr,s);
                strcpy(tmp.prefecture,s);
		next_word(ptr,s);
		tmp.money=atof(s);
		ins(tmp.afm,tmp.name,tmp.surname,tmp.town,tmp.prefecture,tmp.money);		
		i++;
	}
	return;
}
/*give the next word of a stream at s*/
int next_word(FILE * fp,char *s)
{
	char c;
	char som[50];
	strcpy(som,"");
	strcpy(s,som);
        do
        {
		if (fp==stdin) c=getchar();
		else c=fgetc(fp);
                if((int)c==EOF){return 0;}
                else if((c==' ')||(c=='\t')){return 1;}
		else if(c=='\n'){return 2;}
                append(s,c);

        }while(1);
}
/*put a character at the end of a string*/
void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}
/*refresh the helping table of prefectures for fast finding results at stats prefecture command*/
void ref_the_ptrs()
{
	record *  temp=left_top_p;
	while(temp!=NULL)
	{
		prefe[kanonik(temp->prefecture)]=temp;
		temp=temp->right;
	}
}
/*dwse mou thn thesh ston pinaka pou tha mpei to prwto stoixeio ths katakoryfhs listas ths bohthitikhs domhs gia ta prefecture tou prefecture pre*/
int kanonik(char * pre)
{
	int len=strlen(pre);
	int i;
	int sum=0;
	int tmp=1;
	int k;
	int final;
	for(i=1;i<=len;i++)
	{
		for(k=0;k<i-1;k++)
		tmp=tmp*10;	
		sum=sum+(int)pre[i-1]*tmp;	
	}
	final=sum%70;
	return final;
}
/*---------------------------------------------------------------*/
/*Run the commands from a stream*/
int openf(FILE * fp,FILE *ip,FILE *df)
{
	int i,p;
	char s[100];
	record  rec;
	FILE * ptr;
	FILE * ptr2;
	int co=0;
	while(i=next_word(fp,s))
	{
		if(!strcmp(s,"ins"))
		{
			next_word(fp,s);
			rec.afm=atoi(s);
			next_word(fp,s);
			strcpy(rec.name,s);
			next_word(fp,s); 
			strcpy(rec.surname,s);
			next_word(fp,s); 
			strcpy(rec.town,s);
			next_word(fp,s); 
			strcpy(rec.prefecture,s);
			next_word(fp,s); 	
			rec.money=atof(s);
			ins(rec.afm,rec.name,rec.surname,rec.town,rec.prefecture,rec.money);	
		}
		else if(!strcmp(s,"sumstats"))
		{
			sumstats();
		}
		else if (!strcmp(s,"lookup"))
		{
			i=next_word(fp,s);
			lookup(atoi(s));			
		}
		else if (!strcmp(s,"print"))
		{
			print_t();
		}
		else if (!strcmp(s,"del"))
		{	
			del(ip);
		}
		else if (!strcmp(s,"top"))
		{
			i=next_word(fp,s);
                        if( strcmp(s,"ins")&&strcmp(s,"sumstats")&&strcmp(s,"lookup")&&strcmp(s,"print")&&strcmp(s,"del")&&strcmp(s,"top")&&strcmp(s,"exit")&&strcmp(s,"stats")&&strcmp(s,"load"))
			{
				i=next_word(fp,s);
				top_pr(atof(s));
			}
			else
			{
				p=(-1)*(strlen(s)+1);
				fseek(fp,p,SEEK_CUR);
				top();
			}
		}
		else if (!strcmp(s,"stats"))
		{
			float sum;
			i=next_word(fp,s);
			stats(s,&sum);
		}
		else if (!strcmp(s,"exit"))
		{
			i=next_word(fp,s);
			if(s!=NULL)
                    	{
				ptr=fopen(s,"a");
                                exit_n(ptr);
                        }
                        else
                        {
				exit_n(NULL);
                        }
			return 0;
		}
		else if(!strcmp(s,"load"))
		{
			i=next_word(fp,s);
			ptr2=fopen(s,"r");
			load(ptr2);
		}
		else
		{
			if(strcmp(s," ")&&strcmp(s,"	")&&strcmp(s,"\n"))
			{
				printf("Wrong command ,check the mannual again or your input file.\n");
				printf("Wrong input is this:%s .\n",s);
				return -1;
			}
		}
	}
	return 0;
}

