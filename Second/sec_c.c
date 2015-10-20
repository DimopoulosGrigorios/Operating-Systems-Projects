/*Second Assignement Dimopoulos Grigorios */
/*mysortapp*/
/*sec_c.c*/
#include "sec.h"
/*GIA NA MHN TO GRAFW SYNEXEIS:osa merh kwdika einai sxoliasmena htan o kwdikas mou gia na epistrefw ta apotelesmata
xronismou twn sorters(pros ta panw sto dentro ws ton root) kai apla den mou douleue epsaxna 2 meres alla den mporesa na brw gia pion logo den douleuei
apla to afhnw gia na to deite eseis mhpws mporesetai kai mou peite giati me exei faei h periergeia*/

/*______________________________________________________________________________________________________________________*/
/*Anadromikh synarthsh pou xwrizetai sta tria,sto kommati tou patera ,tou aristerou paidiou kai tou deksiou
to kommati tou patera einai to idio process id me auto apo to opoio kalestike h synarthsh create_tree kai to kommati tou paidiou
aristerou h deksiou exei koino process id me ton patera xamhloterou epipedou sto disdiastato dentro apo auto   afou mesa apo ta childs
kaleitai anadromika h sunarthsh create_tree me meiwmeno to bathos kata ena.H epikoinwnia metaksy paidiou kai patera ginetai mesw pipes
,gia thn akribeia duo zeugaria pipes ena gia to aristero paidi kai ena gia to deksi.Otan brethoume sto level=1 dhladh sthn proteleutea seira
tou dyadikou dentrou diadikasiwn tote kaloume analoga me execl dyo alla programmata to Quick pou einai mia quicksort kai to Shell pou einai mia
shellsort analoga an eimaste sto deksi h sto aristero paidi antistoixa tou teleutaiou epipedou.Ta dyo programmata auta kanoun sorting sta kommatia
tou pinaka pou telika exoun ftasei se auta kai stelnoun ta apotelesmata pisw ston patera diamesou pipes(aplwn) dioti mporei na apoteloun alla ekte
lesima alla den pauei to process enveroment pou trexoun na xei klhronwmithei apo ton patera tous.Epeita o pateras dexetai mesw pipes dyo sortarism
enous pinakes apo to aristero kai apo to deksi paidi tou pou tous kanei merge kai epistrefei sto paidi apo opou kalestike twn neo mergarismeno 
pinaka opou autos stelnetai apo ta children ston patera tou children pali mesh pipe kai meta ksana ginetai merge kai olo kai megalwnei o pinakas
enwnontas olo kai pio pollous pinakes aristerwn kai deksiwn paidiwn kai olo ftanei pio panw se level mexri na ftasoume sto root node apo opou
kai prwto kalestike h synarthsh*/ 
Record ** Create_tree(int level,FILE *fl,int atr_num,int start,int stop,Record * array[]/*,double ***tita*/)
{
	int i;
	int pipe_left[2];
	int pipe_right[2];
	int ret;   
	pid_t left_child,right_child;	
	ret=pipe(pipe_left);
	if (ret==-1)
	{
		printf("Creation of pipes attempted but failed.\n");
		return NULL;
	}
	ret=pipe(pipe_right);
        if (ret==-1)
        {
                printf("Creation of pipes attempted but failed.\n");
                return NULL;
        }
    	left_child = fork_ok( );
    	if(left_child != 0)        
    	{
		pid_t right_child;
        	right_child = fork_ok();
        	if(right_child == 0)//right child
		{
			close(pipe_right[0]);
			close(pipe_left[1]);
			close(pipe_left[0]);
			Record * tbl2;
			Record ** back2;
			//double **tita2;
			int size_r,j;
			if(level==1)
			{
				int fd1=fileno(fl);
				char kat1[PATH_MAX+1];
				char pointer1[100];
				char fdi1[100];
				char atr_numi1[100];
				char starti1[100];
				char stopi1[100];
				realpath("Quick",kat1);
				sprintf(pointer1,"%d",pipe_right[1]);
				sprintf(starti1,"%d",(start+(stop-start)/2));
				sprintf(atr_numi1,"%d",atr_num);
				sprintf(stopi1,"%d",stop);	
				sprintf(fdi1,"%d",fd1);
				execl(kat1,"Quick",fdi1,atr_numi1,starti1,stopi1,pointer1,NULL);
				printf("(Quick)Exec failed %s \n",strerror(errno));
				//return ;
			}
			tbl2=malloc((stop-(stop-start)/2-start)*sizeof(Record));
   		        if (tbl2==NULL)
                	{
                        	printf("Can not allocate memory with malloc tbl2.\n");
                        	return NULL;
                	}
			/*tita2=malloc(2*sizeof(double*));
    			for(i=0;i<2; i++)
        		{
        			tita2[i] = malloc(pow(2.0,(double)(level-1))*sizeof(double));
        			if(tita2[i] == NULL)
            			{
            				printf("Can not allocate memory with malloc tbl2.\n");
                                	return NULL;
            			}
        		}*/
            		back2=Create_tree(level-1,fl,atr_num,(start+(stop-start)/2),stop,&tbl2/*,&tita2*/);
			//
			/*for(i=0;i<pow(2.0,(double)(level-1));i++)
			{
				for(j=0;j<2;j++)
				{
					size_r=sizeof(tita2[i][j]);
					write(pipe_right[1],&size_r,sizeof(int));
					write(pipe_right[1],&(tita2[i][j]),size_r);
				}
			}*/
			//stelnw ta data pou phra apo ta paidia mou ston patera mou
			for(i=0;i<((stop-(stop-start)/2-start));i++)
        		{       
				anathesh(&(tbl2[i]),(*back2)[i]);
				size_r=sizeof(tbl2[i].ssn);
                		write(pipe_right[1],&size_r,sizeof(int));
                		write(pipe_right[1],&(tbl2[i].ssn),size_r);
                		size_r=sizeof(tbl2[i].FirstName);
                		write(pipe_right[1],&size_r,sizeof(int));
                		write(pipe_right[1],(tbl2[i].FirstName),size_r);
                		size_r=sizeof(tbl2[i].LastName);
                		write(pipe_right[1],&size_r,sizeof(int));
                		write(pipe_right[1],(tbl2[i].LastName),size_r);
               			size_r=sizeof(tbl2[i].income);
                		write(pipe_right[1],&size_r,sizeof(int));
                		write(pipe_right[1],&(tbl2[i].income),size_r);
        		}
        		size_r=0;
        		write(pipe_right[1],&size_r,sizeof(int));//pes ston patera na mhn diabasei allo
			free(tbl2);
			//free(tita2);
			return NULL;
    		}
		else//parent
		{
			close(pipe_left[1]);
        		close(pipe_right[1]);
			Record * r_tbl2,* r_tbl1;
			int size,sizel,k,l,j;
			//gia ta dedomena apo to deksi paidi
			r_tbl2=malloc((stop-(stop-start)/2-start)*sizeof(Record));
			if (r_tbl2==NULL)
                        {
                                printf("Can not allocate memory with malloc r_tbl2.\n");
                                return NULL;
                        }
			//gia ta dedomena apo to aristero paidi
			r_tbl1=malloc(((stop-start)/2)*sizeof(Record));
                        if (r_tbl1==NULL)
                        {
                                printf("Can not allocate memory with malloc r_tbl1.\n");
                                return NULL;
                     	}
			waitpid(left_child, &k, 0);//perimene kai to aristero kai to deksi paidi
			waitpid(right_child, &l, 0);
			/*for(i=pow(2.0,(double)(level-1));i<pow(2.0,(double)(level));i++)
                        {
                                for(j=0;j<2;j++)
                                {
                                       	read(pipe_right[0],&size,sizeof(int));
                                      	//if (!size)break;
                                	read(pipe_right[0],&((*tita)[i][j]),size);
					printf("right[%d][%d] %lf .\n",i,j,(*tita)[i][j]);
                                }
                        } */
			i=0;
			//diabase ti sou stelnei to paidi sou kai balta ston katalhlo pinaka
			while(1)
                        {
				
				read(pipe_right[0],&size,sizeof(int));
				if (!size)break;
                		read(pipe_right[0],&(r_tbl2[i].ssn),size);
				read(pipe_right[0],&size,sizeof(int));
                                if (!size)break;
				read(pipe_right[0],(r_tbl2[i].FirstName),size);
				read(pipe_right[0],&size,sizeof(int));
                                if (!size)break;
				read(pipe_right[0],(r_tbl2[i].LastName),size);
				read(pipe_right[0],&size,sizeof(int));
                                if (!size)break;
				read(pipe_right[0],&(r_tbl2[i].income),size);
				i++;
                        }
			/*for(i=0;i<pow(2.0,(double)(level-1));i++)
                        {
                                for(j=0;j<2;j++)
                                {
                                        read(pipe_left[0],&size,sizeof(int));
                                        //if (!size)break;
                                        read(pipe_left[0],&((*tita)[i][j]),size);
					printf("left[%d][%d] %lf .\n",i,j,(*tita)[i][j]);
                                }
                        }*/
			i=0;
			while(1)
                        {
                                
                                read(pipe_left[0],&sizel,sizeof(int));
                                if (!sizel)break;
                                read(pipe_left[0],&(r_tbl1[i].ssn),sizel);
                                read(pipe_left[0],&sizel,sizeof(int));
                                if (!sizel)break;
                                read(pipe_left[0],(r_tbl1[i].FirstName),sizel);
                                read(pipe_left[0],&sizel,sizeof(int));
                                if (!sizel)break;
                                read(pipe_left[0],(r_tbl1[i].LastName),sizel);
                                read(pipe_left[0],&sizel,sizeof(int));
                                if (!sizel)break;
                                read(pipe_left[0],&(r_tbl1[i].income),sizel);
				i++;
                        }
			//kane merge tous dyo pinakes
			merge(r_tbl1,((stop-start)/2),r_tbl2,(stop-(stop-start)/2-start),array,atr_num);
			return array;//epestrepse ton mergarismeno pinaka
		}
	}
    	else//left child
    	{
		close(pipe_left[0]);
                close(pipe_right[1]);
                close(pipe_right[0]);
		Record * tbl1;
		Record ** back1;
		//double **tita1;
		int size_rl,j;		
		if (level==1)
		{
			int fd2=fileno(fl);
			char kat2[PATH_MAX+1];
			char pointer2[100];
			char fdi2[100];
                        char atr_numi2[100];
                        char starti2[100];
                        char stopi2[100];
			realpath("Shell",kat2);
			sprintf(pointer2,"%d",pipe_left[1]);
			sprintf(starti2,"%d",start);
                        sprintf(atr_numi2,"%d",atr_num);
                        sprintf(stopi2,"%d",(start+((stop-start)/2)));
                        sprintf(fdi2,"%d",fd2);
			execl(kat2,"Shell",fdi2,atr_numi2,starti2,stopi2,pointer2,NULL);
			printf("(Shell)Exec failed %s \n",strerror(errno));
			//return ;
		}
		tbl1=malloc(((stop-start)/2)*sizeof(Record));
		if (tbl1==NULL)
		{
			printf("Can not allocate memory with malloc tbl1.\n");
			return NULL;
		}
                /*tita1=malloc(2*sizeof(double*));
                for(i=0;i<2; i++)
               	{
                	tita1[i] = malloc(pow(2.0,(double)(level-1))*sizeof(double));
                        if(tita1[i] == NULL)
                        {
                        	printf("Can not allocate memory with malloc tbl2.\n");
                                return NULL;
                        }
                }
                */
        	back1=Create_tree(level-1,fl,atr_num,start,(start+((stop-start)/2)),&tbl1/*,&tita1*/);
		/*for(i=0;i<pow(2.0,(double)(level-1));i++)
                {
                        for(j=0;j<2;j++)
                        {
                                size_rl=sizeof(tita1[i][j]);
                               	write(pipe_left[1],&size_rl,sizeof(int));
                       		write(pipe_left[1],&(tita1[i][j]),size_rl);
               		}
                }*/
		//Stelnw ston patera mou ta dedomena apo ta paidi amou mesw pipes
		for(i=0;i<((stop-start)/2);i++)
                {       
			anathesh(&(tbl1[i]),(*back1)[i]);//
                	size_rl=sizeof(tbl1[i].ssn);
                        write(pipe_left[1],&size_rl,sizeof(int));
                        write(pipe_left[1],&(tbl1[i].ssn),size_rl);
                        size_rl=sizeof(tbl1[i].FirstName);
                        write(pipe_left[1],&size_rl,sizeof(int));
                        write(pipe_left[1],(tbl1[i].FirstName),size_rl);
                        size_rl=sizeof(tbl1[i].LastName);
                        write(pipe_left[1],&size_rl,sizeof(int));
                        write(pipe_left[1],(tbl1[i].LastName),size_rl);
                        size_rl=sizeof(tbl1[i].income);
                        write(pipe_left[1],&size_rl,sizeof(int));
                        write(pipe_left[1],&(tbl1[i].income),size_rl);
              	}
               	size_rl=0;
               	write(pipe_left[1],&size_rl,sizeof(int));//lew ston patera mou na stamatisei na diabazei
		free(tbl1);
		//free(tita1);
		return NULL;
   	}
	//return;
}
/*_________________________________________*/
//Synarthsh fork me prosarmosemeno elegxo gia failure
pid_t fork_ok(void)
{
	pid_t pid;
    	if ((pid = fork()) < 0)
    	{
        	fprintf(stderr, "Fork failure in pid %d\n", (int)getpid());
        	exit(1);
    	}
    	return pid;
}
/*___________________________________________*/
//Synarthsh gia na tupwneis record h se arxeio h sto stdout
void fprint_rec(FILE * ptr,Record *rec)
{
	if (ptr==NULL)
	{
		printf("_________________________________\n");
		printf("Ssn:%d \n",rec->ssn);
		printf("FirstName: %s \n",rec->FirstName);
		printf("LastName: %s \n",rec->LastName);
		printf("Income: %d \n",rec->income);
		printf("_________________________________\n");
	}
	else
	{
		fprintf(ptr,"_________________________________\n");
                fprintf(ptr,"Ssn:%d \n",rec->ssn);
                fprintf(ptr,"FirstName: %s \n",rec->FirstName);
                fprintf(ptr,"LastName: %s \n",rec->LastName);
                fprintf(ptr,"Income: %d \n",rec->income);
                fprintf(ptr,"_________________________________\n");
	}
}
/*___________________________________________*/
//Synarthsh anathesh gia records
void anathesh(Record *target,Record back)
{
	target->ssn=back.ssn;
	strcpy(target->FirstName,back.FirstName);
	strcpy(target->LastName,back.LastName);
	target->income=back.income;
}
/*__________________________________________*/
//Synarthsh merge sort
void merge(Record a[], int m, Record b[], int n, Record * sorted[],int atr_num) 
{
	int i, j, k;
 	j = k = 0;
  	for (i = 0; i < m + n;) 
	{
    		if (j < m && k < n) 
		{	
			if (atr_num==0)
			{
      				if (a[j].ssn < b[k].ssn) 
				{
        				anathesh(&((*sorted)[i]),a[j]);
        				j++;
      				}
      				else 
				{
        				anathesh(&((*sorted)[i]),b[k]);
        				k++;
      				}
      				i++;
			}
			else if (atr_num==1)
			{
				if (strcmp(a[j].FirstName, b[k].FirstName)<0)
                                {
                                        anathesh(&((*sorted)[i]),a[j]);
                                        j++;
                                }
                                else
                                {
                                        anathesh(&((*sorted)[i]),b[k]);
                                        k++;
                                }
                                i++;

			}
			else if (atr_num==2)
			{
				if (strcmp(a[j].LastName, b[k].LastName)<0)
                                {
                                        anathesh(&((*sorted)[i]),a[j]);
                                        j++;
                                }
                                else
                                {
                                        anathesh(&((*sorted)[i]),b[k]);
                                        k++;
                                }
                                i++;
				
			}
			else if (atr_num==3)
			{
				 if (a[j].income< b[k].income)
                                {
                                        anathesh(&((*sorted)[i]),a[j]);
                                        j++;
                                }
                                else
                                {
                                        anathesh(&((*sorted)[i]),b[k]);
                                        k++;
                                }
                                i++;
				
			}
    		}
    		else if (j == m) 
		{
      			for (; i < m + n;) 
			{
        			anathesh(&((*sorted)[i]),b[k]);
        			k++;
        			i++;
      			}
    		}
    		else 
		{
     	 		for (; i < m + n;) 
			{
        			anathesh(&((*sorted)[i]),a[j]);
        			j++;
        			i++;
      			}
    		}
  	}
}
/*__________________________________________*/
//Synarthsh quick sort gia na mporesei na thn xrhsimopoihsei h quick.c anadromika
void quicksort(Record * x,int first,int last,int atr_num)
{
    	int pivot,j,i;
	Record temp;
     	if(first<last)
	{
         	pivot=first;
         	i=first;
         	j=last;
         	while(i<j)
		{	if (atr_num==0)
			{
             			while(x[i].ssn<=x[pivot].ssn&&i<last)
				{
                 			i++;
				}
             			while(x[j].ssn>x[pivot].ssn)
                 		{
					j--;
				}
             			if(i<j)
				{
                 			anathesh(&temp,x[i]);
                 		 	anathesh(&(x[i]),x[j]);
                  			anathesh(&(x[j]),temp);
             			}
			}
			else if(atr_num==1)
			{
				while((strcmp(x[i].FirstName,x[pivot].FirstName)<=0)&&i<last)
                                {
                                        i++;
                                }
                                while(strcmp(x[j].FirstName,x[pivot].FirstName)>0)
                                {
                                        j--;
                                }
                                if(i<j)
                                {
                                        anathesh(&temp,x[i]);
                                        anathesh(&(x[i]),x[j]);
                                        anathesh(&(x[j]),temp);
                                }

			}
			else if(atr_num==2)
                        {
				while((strcmp(x[i].LastName,x[pivot].LastName)<=0)&&i<last)
                                {
                                        i++;
                                }
                                while(strcmp(x[j].LastName,x[pivot].LastName)>0)
                                {
                                        j--;
                                }
                                if(i<j)
                                {
                                	anathesh(&temp,x[i]);
                                        anathesh(&(x[i]),x[j]);
                                        anathesh(&(x[j]),temp);
                                }

                        }
			else if(atr_num==3)
                        {
				while(x[i].income<=x[pivot].income&&i<last)
                                {
                                        i++;
                                }
                                while(x[j].income>x[pivot].income)
                                {
                                        j--;
                                }
                                if(i<j)
                                {
                                	anathesh(&temp,x[i]);
                                        anathesh(&(x[i]),x[j]);
                                        anathesh(&(x[j]),temp);
                                }

                        }
         	}
         	anathesh(&temp,x[pivot]);
         	anathesh(&(x[pivot]),x[j]);
         	anathesh(&(x[j]),temp);
         	quicksort(x,first,j-1,atr_num);
         	quicksort(x,j+1,last,atr_num);
    	}
}
/*_________________________________________*/
