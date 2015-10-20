
/*Second Assignement Dimopoulos Grigorios */
/*mysortapp*/
/*quick.c*/
#include "sec.h"

int main (int argc,char * argv[])
{
	int fd=atoi(argv[1]);
        FILE * inpfl=fdopen(fd,"rb");
        int atr_num=atoi(argv[2]);
        int start=atoi(argv[3]);
        int stop=atoi(argv[4]);
        int thepipe=atoi(argv[5]);
	//diabazw ta arguements mou kai ta metatrepw ston tupou pou prepei
	long lSize;
	int i,n,j,size;
	Record * rec,*table;
        double t1, t2, cpu_time;
        struct tms tb1, tb2;
        double ticspersec;
        double run_time;
        double cpu_t;
        fseek (inpfl , 0 , SEEK_END);
        lSize = ftell (inpfl);
        rewind (inpfl);
        n= (int) lSize/sizeof(Record);
	//briskw posa records exei to arxeio
        rec=malloc(n*sizeof(Record));
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
	//pernw mono auta pou mou antistixoun kai ta sortarw
	ticspersec = (double) sysconf(_SC_CLK_TCK);
        t1 = (double) times(&tb1);
	//kanw ypologismous xronismou
	quicksort(table,0,(stop-start)-1,atr_num);
	//exw sortarei hdh ta data me quicksort
	//kanw upologismous xronismou kai tous emfanizw edw ston sorter
        t2 = (double) times(&tb2);
        cpu_time = (double) ((tb2.tms_utime + tb2.tms_stime) -(tb1.tms_utime + tb1.tms_stime));
        run_time=(t2 - t1) / ticspersec;
        cpu_t=cpu_time / ticspersec;
	printf("QUICKSORT:(%d):\n \t .run time:%lf \n \t .cpu time:%lf \n \n",(int)getpid(),run_time,cpu_t);
	/*printf(" %lf %lf \n",run_time,cpu_t);
        size=sizeof(run_time);
        write(thepipe,&size,sizeof(int));
        write(thepipe,&(run_time),size);
        size=sizeof(cpu_t);
        write(thepipe,&size,sizeof(int));
        write(thepipe,&(cpu_t),size);
	*/        
	for(i=0;i<(stop-start);i++)
        {	size=sizeof(table[i].ssn);
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
	//exw hdh steilei ston patera mou ta data kai tou xw pei na stamatisei na diabazei
        free(rec);
        free(table);	
	return 0;
}
