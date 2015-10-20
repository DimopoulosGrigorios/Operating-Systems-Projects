/*Second Assignement Dimopoulos Grigorios */
/*mysortapp*/
/*sec.c*/
#include "sec.h"
int main(int argc,char * argv[])
{
        FILE * inpfl=NULL;
        int tree_depth=0; 
        int atr_num=0;
	int flag1=0,flag2=0,flag3=0;
   	int i,n;
	long lSize;
	int mypipe[2];
	int ret=pipe(mypipe);//creating the pipe for comunication between child and parent
	pid_t child;           
	if (ret==-1)
	{
		printf("Creation of pipes attempted but failed.\n");
		return -1;
	}
	/*---------------------------------------------------------------------------------*/
	/*Tsekarw ta arguements pou erxontai gia to bathos to atribute number kai to arxeio*/
        for(i=1;i<argc;i++)
        {
                if(!strcmp(argv[i],"-d"))
                {
                        i++;
                        tree_depth=atoi(argv[i]);
			while((tree_depth>6)||(tree_depth<1))
			{
				printf("The depth of the tree should be between 1 and 6.\n");
				printf("Give me a valid depth of the tree.\n");
				scanf("%d",&tree_depth);
			}
			flag1=1;
                }
                else if(!strcmp(argv[i],"-f"))
                {
                        i++;
                        inpfl=fopen(argv[i],"rb");
                        if (inpfl==NULL)
                        {
                                printf("Can't open the file %s for reading. \n",argv[i]);
                                return -1;
                        }
			flag2=1;
                }
                else if(!strcmp(argv[i],"-a"))
                {
                        i++;
                        atr_num=atoi(argv[i]);
			while ((atr_num>3)||(atr_num<0))
			{
				printf("The attribute number  should be between 0 and 3.\n");
                                printf("Give me a valid attribute number.\n");
                                scanf("%d",&atr_num);
			}
                }
		flag3=1;
        }
	if(!(flag1&&flag2&&flag3))
	{
		printf("Not enough resourses to run the program.\n");
		return -1;
	}
	/*------------------------------------------------------------------------*/
	fseek (inpfl , 0 , SEEK_END);
        lSize = ftell (inpfl);
        rewind (inpfl);
        n= (int) lSize/sizeof(Record);
	/*Briskw to megethos tou binary arxeiou kai poses eggrafes exei*/
	child=fork_ok();
	/*Kanw fork gia na adhmiourghsw ton kombo root*/
	if (child==0)/*mesa ston kombo(process root)*/
	{
		Record * rec;
		Record ** backb;
		int size_r,j;
		close(mypipe[0]);//kleinw ta pipe pou den xreiazomai
		//double **tita;	//enas disdiastatos pinakas pou xrisimopoihte gia thn epistrofh twn time tables apo tous sorters
        	rec=malloc(n*sizeof(Record));
        	if (rec==NULL)
        	{
                	printf("Can not allocate memory child main.\n");
                	return -1;
        	}
/*---------------------------------------------------------------------------------------------------------------------------*/
/*Kommati kwdika pou den mou douleuei .To afhnw gia na to deite.Xrhsimeuei sthn  epistrofh ston arxaiotero patera twn  apotelesmatwn xronismou
twn sorters apo paidi se paidi,eksigw thn idea ths epistrofhs twn apotelesmatwn xronismou apo tous sorters pio analytika sto read me*/
                /*tita=malloc(2*sizeof(double*));
                for(i=0;i<2; i++)
                {
               		(tita)[i] = malloc(pow(2.0,(double)(tree_depth))*sizeof(double));
                        if((tita)[i] == NULL)
                        {
                      		printf("Can not allocate memory with malloc tbl2.\n");
                                return -1;
                        }
               	}*/
/*------------------------------------------------------------------------------------------------------------------------*/
		backb=Create_tree(tree_depth,inpfl,atr_num,0,n,&rec/*,&tita*/);
		/*Dhmiourgw to dentro me thn pio panw anadromikh synarthsh*/
		/*An thelisete na testarete ton tropo epistrofhs xronismou apo paidi se paidi ston arxaitero patera pou den mou douleuei*/
		/*parakalw aposxoliasth kai to teleutaio arguement ths Create_treee*/
/*---------------------------------------------------------------------------------------------------------------------------*/
/*Kommati kwdika pou den mou douleuei .To afhnw gia na to deite.Xrhsimeuei sthn  epistrofh ston arxaiotero patera twn  apotelesmatwn xronismou
twn sorters apo paidi se paidi,eksigw thn idea ths epistrofhs twn apotelesmatwn xronismou apo tous sorters pio analytika sto read me*/
		/*for(i=0;i<pow(2.0,(double)(tree_depth));i++)
                {
                	for(j=0;j<2;j++)
                       	{
                    		size_r=sizeof((tita)[i][j]);
                            	write(mypipe[1],&size_r,sizeof(int));
                          	write(mypipe[1],&((tita)[i][j]),size_r);
                        }
                } */
/*---------------------------------------------------------------------------------------------------------------------------*/
		for(i=0;i<n;i++)
                {     
			anathesh(&(rec[i]),(*backb)[i]);  
                	size_r=sizeof(rec[i].ssn);
                        write(mypipe[1],&size_r,sizeof(int));
                        write(mypipe[1],&(rec[i].ssn),size_r);
                        size_r=sizeof(rec[i].FirstName);
                        write(mypipe[1],&size_r,sizeof(int));
                        write(mypipe[1],(rec[i].FirstName),size_r);
                        size_r=sizeof(rec[i].LastName);
                        write(mypipe[1],&size_r,sizeof(int));
                        write(mypipe[1],(rec[i].LastName),size_r);
                        size_r=sizeof(rec[i].income);
                        write(mypipe[1],&size_r,sizeof(int));
                        write(mypipe[1],&(rec[i].income),size_r);
           	}
		/*Grafw ston parent auta pou phra apo ta paidia tou root node*/
                size_r=0;
                write(mypipe[1],&size_r,sizeof(int));//lew ston patera na stamathsei na diabasei me to sunthimatiko size_r=0
		free(rec);
		//free(tita);
	}
	else//pateras
	{
		Record * rec_t;
		int size,j;
		//double ** tt; //pinakas gia thn epistrofh twn timetables  twn sorters
		rec_t=malloc(n*sizeof(Record));
                if (rec_t==NULL)
                {
                        printf("Can not allocate memory father main.\n");
                        return -1;
                }
/*---------------------------------------------------------------------------------------------------------------------------*/
/*Kommati kwdika pou den mou douleuei .To afhnw gia na to deite.Xrhsimeuei sthn  epistrofh ston arxaiotero patera twn  apotelesmatwn xronismou
twn sorters apo paidi se paidi,eksigw thn idea ths epistrofhs twn apotelesmatwn xronismou apo tous sorters pio analytika sto read me*/
		/*tt=malloc(2*sizeof(double*));
                for(i=0;i<2; i++)
                {
                        tt[i] = malloc(pow(2.0,(double)(tree_depth))*sizeof(double));
                        if(tt[i] == NULL)
                        {
                                printf("Can not allocate memory with malloc tbl2.\n");
                                return -1;
                        }
                }*/
/*---------------------------------------------------------------------------------------------------------------------------*/
		close(mypipe[1]);//kleinw ta mh xrhsimopoioumena pipes
                waitpid(child, NULL, 0); //prin diabasa perimenw to paidi mou na teleiwsei tis ergasies tou
/*---------------------------------------------------------------------------------------------------------------------------*/
/*Kommati kwdika pou den mou douleuei .To afhnw gia na to deite.Xrhsimeuei sthn  epistrofh ston arxaiotero patera twn  apotelesmatwn xronismou
twn sorters apo paidi se paidi,eksigw thn idea ths epistrofhs twn apotelesmatwn xronismou apo tous sorters pio analytika sto read me*/
		/* for(i=0;i<pow(2.0,(double)(tree_depth));i++)
             	{
                       	for(j=0;j<2;j++)
                        {
                               	read(mypipe[0],&size,sizeof(int));
                                if (!size)break;
                        	read(mypipe[0],&(tt[i][j]),size);
                	}
			if (i%2) printf("QUICKSORT(%d):\n \t .run time:%lf \n \t .cpu time:lf \n \n",i/2,tt[i][0],tt[i][1]);
                        else	printf("SHELLSORT(%d):\n \t .run time:%lf \n \t .cpu time:lf \n \n",i/2,tt[i][0],tt[i][1]);

                } */
/*---------------------------------------------------------------------------------------------------------------------------*/
		i=0;
                while(1)
                {
			read(mypipe[0],&size,sizeof(int));
                        if (!size)break;
                        read(mypipe[0],&(rec_t[i].ssn),size);
                        read(mypipe[0],&size,sizeof(int));
                        if (!size)break;
                       	read(mypipe[0],(rec_t[i].FirstName),size);
                        read(mypipe[0],&size,sizeof(int));
                        if (!size)break;
                       	read(mypipe[0],(rec_t[i].LastName),size);
                        read(mypipe[0],&size,sizeof(int));
                        if (!size)break;
                        read(mypipe[0],&(rec_t[i].income),size);
                      	fprint_rec(NULL,&(rec_t[i]));
                	printf("%d.\n",i);
                	i++;
                }
		free(rec_t);
		//free(tt);
	}
}
