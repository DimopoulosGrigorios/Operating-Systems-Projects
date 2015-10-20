/*First Assignement Dimopoulos Grigorios */
/*Waiting queue*/
/*main.c*/
#include "fun.h"
int main(int argc,char * argv[])
{
        FILE * invfl=NULL;
        FILE * inpfl=NULL;
        FILE * confl=NULL;
	FILE * lod;
	FILE * lod1;
        int i; 
        int flag=0;
	record * cur;
	record * cur2;
	node * cure;
        for(i=1;i<argc;i++)
        {
                if(!strcmp(argv[i],"-o"))
                {
                        i++;
                        invfl=fopen(argv[i],"a");
                        if (invfl==NULL)
                        {
                                printf("Can't open the file %s for writting. \n",argv[i]);
                                return -1;
                        }
                        flag=1;
                }
                else if(!strcmp(argv[i],"-i"))
                {
                        i++;
                        inpfl=fopen(argv[i],"r");
                        if (inpfl==NULL)
                        {
                                printf("Can't open the file %s for reading. \n",argv[i]);
                                return -1;
                        }
                }
                else if(!strcmp(argv[i],"-c"))
                {
                        i++;
                        confl=fopen(argv[i],"r");
                        if (confl==NULL)
                        {
                                printf("Can't open the file %s for reading. \n",argv[i]);
                                return -1;
                        }
                }
                if ((flag!=1)&&(i==argc-1))
                {
                        printf("Error you didnt gave me any invoice file. \n");
                }
        }
	if (inpfl!=NULL)
	{
		openf(inpfl,invfl,confl);
	}
	openf(stdin,invfl,confl);
	fcloseall();
	return 0;

}
