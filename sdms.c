// Required headers files for program
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// File pointers for file handling
FILE *fp, *ft;
long long recordSize;
char another;
int id,flag=0;

// Function declaration for various tasks 
void addRecord();
void displayRecord();
void modifyRecord();
void searchRecord();
void deleteRecord();

// Student structure to store various data of student
struct Student
{
	int studentId;
	int rollNO;
	char studentName[50];
	char phoneNo[11];

} s;

// main function
int main()
{	
	
	system("cls");
	int choice;
	
	// File opening and checking 
	fp= fopen("STUDENT.DAT","rb+");	
	if(fp==NULL)
	{
		fp=fopen("STUDENT.DAT","wb+");
		if(fp==NULL)
		{
			printf("Cannot open file\n");
			exit(0);
		}
	}

	recordSize=sizeof(s);
	

	// Menu for various tasks and function calling
	do
	{
		printf("\n\n=====Menu for program=====\n\n");
		printf("1. Add Records\n");
		printf("2. List Records\n");
		printf("3. Modify Records\n");
		printf("4. Search Records\n");
		printf("5. Delete Records\n");
		printf("0. Exit\n");
		printf("\nEnter your choice : ");
		scanf("%d",&choice);
		system("cls");

		switch (choice)
		{
		case 1: addRecord();
			break;
		case 2: displayRecord();
			break;
		case 3: modifyRecord();
			break;
		case 4: searchRecord();
			break;
		case 5: deleteRecord();
			break;
		case 0: fclose(fp);
			exit(0);
		default: system("cls");
			printf("\nYou have enter a wrong choice, please enter a valid choice  ");
		}

	}while(choice!=0);
	return 0;
}
// main function end

void addRecord()
{
	// To move the pointer at the end of the file
	fseek(fp,0,SEEK_END);
	another='y';
	// Loop for getting input of student data 
	while(another=='y' || another=='y')
	{
		printf("Enter id :\n");
		scanf("%d",&s.studentId);
		printf("Enter roll :\n");
		scanf("%d",&s.rollNO);
		printf("Enter full name :\n");
		getchar();
		gets(s.studentName);
		printf("Enter the phone NO :\n");
		scanf("%s",s.phoneNo);
		fwrite(&s, recordSize, 1, fp);
		printf("\nAdd another Record (Y/N) : ");
		fflush(stdin);
		another=getchar();
		system("cls");
	}
}
// addRecord function end

void displayRecord()
{
	system("cls");
	// To move the pointer at the begining of the file and checking for student data is available or not for displaying
	rewind(fp);
	if(fread(&s, recordSize, 1, fp)!=1)
	{
		system("cls");
		printf("\nNO Student data is available...");
		return;
	}
	// To move the pointer at the begining of the file and displaying it
	rewind(fp);
	printf("\n\n%-6s%-10s%-30s%-12s","ID","Rollno","Name ","PhoneNo");
	printf("\n--------------------------------------------------------------");
    while (fread(&s, recordSize, 1, fp) == 1)
	{
        printf("\n%-6d%-10d%-30s%-12s",s.studentId,s.rollNO,s.studentName,s.phoneNo);
	}
	printf("\n\n\nEnter any keys to continue.......");
    getch();
	system("cls");

}
// displayRecord function end

void modifyRecord()
{
	flag=0;
	another = 'Y';
    while (another == 'Y' || another=='y')
    {

		// To move the pointer at the begining of the file and checking for student data is available or not modification
		rewind(fp);
		if(fread(&s, recordSize, 1, fp)!=1)
		{
			system("cls");
			printf("\nNO Student data is available for modification...");
			return;
		}
		// Getting id for modification of student data
        printf("\n\nEnter id of student to modify : ");                
		scanf("%d", &id);

		// To move the pointer at the begining of the file and editing student data by rewriting the file
        rewind(fp);
        while (fread(&s, recordSize, 1, fp) == 1)
		{
        	if (s.studentId==id)
            {
				flag=1;
				printf("Enter roll ");
				scanf("%d",&s.rollNO); 
                printf("Enter full name :\n");
				getchar();
				gets(s.studentName);
				printf("Enter the phone NO :\n");
				scanf("%s",s.phoneNo);
				
                fseek(fp, -recordSize, SEEK_CUR);
                fwrite(&s, recordSize, 1, fp);
                break;
            }
        }
		if(flag==0)
			printf("\nFor given id no data is available...\n");
		flag=0;
        printf("\n\nModify another Record (Y/N) : ");
        fflush(stdin);
        another = getchar();
		system("cls");
    }
	
}
// modifyRecord function end

void searchRecord()
{
	flag=0;
	another = 'Y';
    while (another == 'Y' || another=='y')
    {

		// To move the pointer at the begining of the file and checking for student data is available or not modification
		rewind(fp);
		if(fread(&s, recordSize, 1, fp)!=1)
		{
			system("cls");
			printf("\nNO Student data is available for search...");
			return;
		}

		// Getting id for search of student data
	    printf("\nEnter id of student to search : ");                
		scanf("%d", &id);

		// To move the pointer at the begining of the file and editing student data by rewriting the file
        rewind(fp);
        while (fread(&s, recordSize, 1, fp) == 1)
		{
        	if (s.studentId==id)
            {
				flag=1;
				printf("\n\n%-6s%-10s%-30s%-12s","ID","Rollno","Name ","PhoneNo");
				printf("\n--------------------------------------------------------------");
        		printf("\n%-6d%-10d%-30s%-12s",s.studentId,s.rollNO,s.studentName,s.phoneNo);
            }
        }
		if(flag==0)
			printf("\nFor given id no data is available...\n");
        printf("\n\nSearch another Record (Y/N) : ");
        fflush(stdin);
        another = getchar();
		system("cls");
    }
}
// searchRecord function end

void deleteRecord()
{
	flag=0;
	another='y';
	while(another=='y' || another=='Y')
	{
		// To move the pointer at the begining of the file and checking for student data is available or not for deletion
		rewind(fp);
		if(fread(&s, recordSize, 1, fp)!=1)
		{
			system("cls");
			printf("\nNO Student data is available for deletion...");
			break;
		}

		// Getting id for deleting student data of particular id
		printf("\nEnter the id of student to delete : ");
		scanf("%d",&id);

		// Creating temparory file to store required student data
		ft=fopen("TEMP.DAT","wb");
		rewind(fp);
		while(fread(&s,recordSize,1,fp)==1)
		{
			if(s.studentId!=id)
				fwrite(&s,recordSize,1,ft);
			if(s.studentId==id)
				flag=1;
		}
		fclose(fp);
		fclose(ft);

		// deleting of STUDENT.DAT file and renaming TEMP.DAT file to STUDENT.DAT 
		remove("STUDENT.DAT");
		rename("TEMP.DAT","STUDENT.DAT");
		fp=fopen("STUDENT.DAT","rb+");
		if(flag==0)
			printf("\nFor given id no data is available...\n");
		printf("\nDelete another record (Y/N) ");
		fflush(stdin);
		another=getchar();
		system("cls");
	}
}
// deleteRecord function end