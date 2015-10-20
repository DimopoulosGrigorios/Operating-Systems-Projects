/*Second Assignement Dimopoulos Grigorios */
/*mysortapp*/
/*shell.c*/
#include "sec.h"
int main(int argc,char * argv[])
{
	int fd=atoi(argv[1]);
	FILE * inpfl=fdopen(fd,"rb");
	int atr_num=atoi(argv[2]);
	int start=atoi(argv[3]);
	int stop=atoi(argv[4]);
	int thepipe=atoi(argv[5]);
	//exw parei ta arguements kai ta xw metatrepsei stous swstous tupous
	int i,n,j,k,num,size;
	long lSize;
	Record tmp;
	Record * rec;
	Record	* table;
	fseek (inpfl , 0 , SEEK_END);
        double t1, t2, cpu_time;
        struct tms tb1, tb2;
        double ticspersec;
        double run_time;
        double cpu_t;
        lSize = ftell (inpfl);
        rewind (inpfl);
        n= (int) lSize/sizeof(Record);
        rec=malloc(n*sizeof(Record));
	//briskw posa records exei mesa to arxeio mou
        if (rec==NULL)
        {
                printf("Can not allocate memory.\n");
                return -1;
        }
	table=malloc((stop-start)*sizeof(Record));
	if (table==NULL)
        {
                printf("Can not allocate memory.\n");
                return -1;
        }
	for (i=0; i<n; i++)
        {
                fread(&(rec[i]), sizeof(Record), 1,inpfl);
        }	
	j=0;
	for(i=start;i<stop;i++)
	{
		anathesh(&(table[j]),rec[i]);
		j++;
	}
	//pernw auta pou mou antistixoun gia na ta sortarw
	num=stop-start;
	ticspersec = (double) sysconf(_SC_CLK_TCK);
        t1 = (double) times(&tb1);
	//kanw metriseis xronismou
	for(i=num/2; i>0; i=i/2)
	{
   		for(j=i; j<num; j++)
   		{
     			for(k=j-i; k>=0; k=k-i)
     			{	if (atr_num==0)
				{
        				if(table[k+i].ssn>=table[k].ssn)
					{
            					break;
        				}
					else
        				{
            					anathesh(&(tmp),table[k]);
            					anathesh(&(table[k]),table[k+i]);
            					anathesh(&(table[k+i]),tmp);
        				}
				}
				else if (atr_num==1)
				{
					if(strcmp(table[k+i].FirstName,table[k].FirstName)>=0)
                                        {
                                                break;
                                        }
                                        else
                                        {
                                                anathesh(&tmp,table[k]);
                                                anathesh(&(table[k]),table[k+i]);
                                                anathesh(&(table[k+i]),tmp);
                                        }

				}
				else if (atr_num==2)
				{
					if(strcmp(table[k+i].LastName,table[k].LastName)>=0)
                                        {
                                                break;
                                        }
                                        else
                                        {
                                                anathesh(&tmp,table[k]);
                                                anathesh(&(table[k]),table[k+i]);
                                                anathesh(&(table[k+i]),tmp);
                                        }

				}
				else if (atr_num==3)
				{
					if(table[k+i].income>=table[k].income)
                                        {
                                                break;
                                        }
                                        else
                                        {
                                                anathesh(&tmp,table[k]);
                                                anathesh(&(table[k]),table[k+i]);
                                                anathesh(&(table[k+i]),tmp);
                                        }

				}
     			}
   		}
 	}
	//exw hdh sortarei twn pinaka
	//kanei upologismous xronismou kai emfanizw apotelesmata edw ston sorter
	t2 = (double) times(&tb2);
        cpu_time = (double) ((tb2.tms_utime + tb2.tms_stime) -(tb1.tms_utime + tb1.tms_stime));
        run_time=(t2 - t1) / ticspersec;
        cpu_t=cpu_time / ticspersec;
       	printf("SHELLSORT:(%d):\n \t .run time:%lf \n \t .cpu time:%lf \n \n",(int)getpid(),run_time,cpu_t);
        /*size=sizeof(run_time);
        write(thepipe,&size,sizeof(int));
        write(thepipe,&(run_time),size);
        size=sizeof(cpu_t);
        write(thepipe,&size,sizeof(int));
        write(thepipe,&(cpu_t),size);
	*/
        for(i=0;i<(stop-start);i++)
        {       size=sizeof(table[i].ssn);
                write(thepipe,&size,sizeof(int));
                write(thepipe,&(table[i].ssn),size);
                size=sizeof(table[i].FirstName);
                write(thepipe,&size,sizeof(int));
                write(thepipe,(table[i].FirstName),size);
                size=sizeof(table[i].LastName);
                write(thepipe,&size,sizeof(int));
                write(thepipe,(table[i].LastName),size);
                size=sizeof(table[i].income);
                write(thepipe,&size,sizeof(int));
                write(thepipe,&(table[i].income),size);
        }
        size=0;
        write(thepipe,&size,sizeof(int));
	//exw hdh steilei ston patera mou mesw tou pipe pou xe dwsei gia na milame  ta dedomena taksinomhmena
	free(rec);
	free(table);
	return 0;
}
