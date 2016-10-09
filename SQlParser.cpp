#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct def
{
	int num;
        char head[10][10];
};
struct row
{
	char field[10][10];
};
void create_table(char *ptr[])
{
        char name[10],n[20];
	strcpy(name,ptr[0]);
	strcat(name,".dat");
	FILE *fp;
        FILE *fout=fopen("table.txt","a+");
        rewind(fout);
	fscanf(fout,"%s",n);
        if(fout==NULL)
        {
                printf("\nUnbale to open the file.\n");
	        exit(0);
        }
        do
        {
                if(!strcasecmp(name,n))
                {
                        printf("\n\t\tTable already exists.\n\n");
                        exit(0);
                }
		fscanf(fout,"%s",n);
        }while(!feof(fout));
	fprintf(fout,"%s",name);
        printf("\n\t\tTable successfully created.\n\n");
        fputc('\n',fout);
        fp=fopen(name,"w");
	fprintf(fp,"%d",0);
        fclose(fout);
	fclose(fp);
}
void assign_table(int a,char *q[])
{
	char name[10];
	strcpy(name,q[0]);
	strcat(name,".dat");
	FILE *fin=fopen(name,"r+");
	struct def col;
	int ctr=0,i=1,chk;
	if(fin==NULL)
 	{
        	printf("\n\t\tTable does not exist.\n");
		exit(0);
	}
	fscanf(fin,"%d",&chk);
	if(!feof(fin))
	{
		printf("\n\t\tTable cannot be redefined.\n");
		exit(0);
	}
	while(i<(a-4))
    	{
		strcpy(col.head[ctr],q[i]);
		ctr++;
		i++;
    	}
	col.num=ctr;
	fprintf(fin,"%d",1);
	fwrite(&col,sizeof(struct def),1,fin);
	fclose(fin);
	printf("\n\t\tTable has been defined.\n");
}
void insert_into(int a,char *q[])
{
	char name[10];
        strcpy(name,q[0]);
        strcat(name,".dat");
        FILE *fin;
	fin=fopen(name,"r+");
        struct row r;
	struct def d;
        int ctr=0,i=1,chk;
        if(fin==NULL)
        {
                printf("\n\t\tTable does not exist.\n");
                exit(0);
        }
	fclose(fin);
	fin=fopen(name,"a+");
	fscanf(fin,"%d",&chk);
	if(!chk)
	{
		printf("\n\t\tTable has not been defined.\n");
		exit(0);
	}
	fread(&d,sizeof(struct def),1,fin);
	if((a-5)!=d.num)
	{
		printf("\n\t\tIncompatible number of entries.\n");
		exit(0);
	}
	for(;i<=d.num;i++)
		strcpy(r.field[ctr++],q[i]);
	fwrite(&r,sizeof(struct row),1,fin);
	printf("\n\t\t1 row has been added.\n");
	fclose(fin);
}
void display_table(char *q[])
{
	char name[10];
        strcpy(name,q[0]);
        strcat(name,".dat");
        FILE *fin;
	fin=fopen(name,"r+");
        struct row r;
        struct def d;
        int ctr=0,i;
        if(fin==NULL)
        {
                printf("\n\t\tTable does not exist.\n");
                exit(0);
        }
	fclose(fin);
	fin=fopen(name,"a+");
	fscanf(fin,"%d",&i);
	fread(&d,sizeof(struct def),1,fin);
	printf("\n\t\t");
	for(i=0;i<d.num;i++)
		printf("%s\t\t",d.head[i]);
	printf("\n\t\t");
	for(i=0;i<d.num;i++)
		printf("_____\t\t");
	while(1)
	{
		fread(&r,sizeof(struct row),1,fin);
		if(feof(fin))
			break;
		printf("\n\t\t");
		for(i=0;i<d.num;i++)
			printf("%s\t\t",r.field[i]);
		ctr++;
	}
	if(ctr==1)
	{
		printf("\n\n\t\t%d row selected.\n",ctr);
	        fclose(fin);
	}
	else
	{
		printf("\n\n\t\t%d rows selected.\n",ctr);
		fclose(fin);
	}
}
void drop_table(char *q[])
{
	char name[10],n[10];
        strcpy(name,q[0]);
        strcat(name,".dat");
        FILE *fin,*fout;
        fin=fopen(name,"r+");
        if(fin==NULL)
        {
                printf("\n\t\tTable does not exist.\n");
                exit(0);
        }
	remove(name);
	fclose(fin);
	fout=fopen("table.txt","r");
	fin=fopen("dummy.txt","w");
	fscanf(fout,"%s",n);
        if(fout==NULL)
        {
                printf("\nUnbale to open the file.\n");
                exit(0);
        }
        do
        {
                if(strcasecmp(name,n))
                {
                        fprintf(fin,"%s",n);
                        fputc('\n',fin);
                }
                fscanf(fout,"%s",n);
        }while(!feof(fout));
	remove("table.txt");
	rename("dummy.txt","table.txt");
	printf("\n\t\tTable %s has been dropped.\n",q[0]);
	fclose(fout);
	fclose(fin);
}
void show_all()
{
	FILE *fp=fopen("table.txt","r+");
	if(fp==NULL)
	{
		printf("\n\t\tUnable to access database.\n");
		exit(0);
	}
	char tab[10];
	printf("\n\t\tTABLES PRESENT\n");
	printf("\t\t______________________\n");
	fscanf(fp,"%s",tab);
	if(!ftell(fp))
	{
		printf("\n\t\tNo tables.\n");
		exit(0);
	}
	do
	{
		printf("\n\t\t%s",tab);
		fscanf(fp,"%s",tab);
	}while(!feof(fp));
	printf("\n");
	fclose(fp);
}
void welcome_page()
{
	system("clear");
	printf("\t\t____________________________________________\n");
        printf("\t\t\tWELCOME TO SQL DATABASE\n");
        printf("\n\t\t\t\tUSER MANUAL\n");
	printf("\t\t____________________________________________\n\n");
        printf("\tCREATE TABLE : Creates a table in the database.\n");
	printf("\tSyntax : CREATE TABLE <table name> .\n\n");
	printf("\tASSIGN TABLE : Defines the columns of the table.\n");
	printf("\tSyntax : ASSIGN TABLE <table name> <column name> <column name>... .\n\n");
	printf("\tINSERT INTO : Inputs data to the table row by row.\n");
	printf("\tSyntax : INSERT INTO <table name> <value1> <value2>... .\n\n");
	printf("\tDISPLAY TABLE : Displays the table\n");
	printf("\tSyntax : DISPLAY TABLE <table name> .\n\n");
	printf("\tDROP TABLE : Deletes the table from the database.\n");
	printf("\tSyntax : DROP TABLE <table name> .\n\n");
	printf("\tSHOW ALL : Displays all the tables present in the database\n");
	printf("\tSyntax : SHOW ALL.\n\n");
	printf("\t-> Each query must start with './a.out' and end with '.'\n\n");
}
int main(int args, char *query[])
{
	if(!strcmp(query[0],"./a.out")&&(args==1))
	{
		welcome_page();
		exit(0);
	}
        if(strcmp(query[args-1],"."))
        {
                printf("\n\t\tQuery not terminated properly.\n");
                exit(0);
        }
	if(!strcasecmp(query[1],"show")&&!strcasecmp(query[2],"all"))
        {
                if(args!=4)
                {
                        printf("\n\t\tInvalid query.\n");
                        exit(0);
                }
                show_all();
		exit(0);
        }
	if(args<5)
        {
                printf("\n\t\tInvalid query.\n");
                exit(0);
        }

	if(!strcasecmp(query[1],"create")&&!strcasecmp(query[2],"table"))
        {
                if(args>5)
                {
                        printf("\n\t\tInvalid query.\n");
                        exit(0);
                }
                create_table(&query[3]);
        }
        else if(!strcasecmp(query[1],"assign")&&!strcasecmp(query[2],"table"))
                assign_table(args,&query[3]);
	else if(!strcasecmp(query[1],"display")&&!strcasecmp(query[2],"table"))
	{
		if(args!=5)
                {
                        printf("\n\t\tInvalid query.\n");
                        exit(0);
                }
		display_table(&query[3]);
	}
	else if(!strcasecmp(query[1],"insert")&&!strcasecmp(query[2],"into"))
                insert_into(args,&query[3]);
	else if(!strcasecmp(query[1],"drop")&&!strcasecmp(query[2],"table"))
	{
		if(args!=5)
                {
                        printf("\n\t\tInvalid query.\n");
                        exit(0);
                }
		drop_table(&query[3]);
	}
	else
	{
		printf("\n\t\tInvalid query.\n");
		exit(0);
	}
}
