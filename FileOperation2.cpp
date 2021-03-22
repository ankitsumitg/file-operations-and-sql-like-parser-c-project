/*
	Author Name: Ankit Gupta
	This program demonstrate how to open and perform operatoion on files and also shows how to execute simple sql like query.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  MAX_LINE_LENGTH    256
const char NULL_CHAR = (char)0;
const char *delim = ",";
const char *delimLast = "\r\n";

struct student
{
	/* The name of student */
	int rollno;
	char   name[MAX_LINE_LENGTH];
	float  exam1;
	float  exam2;
	float  exam3;
	float  exam4;
	float avg;
	int cgpa;
};

struct studentinfo
{
	/* The info of student */
	int rollno;
	char  mob[MAX_LINE_LENGTH];
	char   add[MAX_LINE_LENGTH];
	char   city[MAX_LINE_LENGTH];
	int  pincode;
};
struct store
{
	/*This stores the student and info details.
		Maintains its curretn lenght and Max capacity	
	*/
	struct student **stud;
	struct studentinfo **info;
	int lenght1;
	int lenght2;
	int capacity1;
	int capacity2;
} *details;


/* PROTOTYPE OF FUNCTIONS */
int loadmarks();
int loadinfo();
//int length(char *name); // Extra function
void calc();
void show();
void save();
void join();
void query();
void adquery();
int contains(char *pattern, char *search);
void init();
void adquery();
float get(char* key, int i);
static int gethash(char* source);

/*
	this is intialization function to initialize the details structure
*/
void init()
{
	/*details = (struct store **)malloc(sizeof(struct store *));*/
	details= (struct store *)malloc(sizeof(struct store));
	details->capacity1 = 20;
	details->stud = (struct student **)malloc(details->capacity1*sizeof(struct student*));
	for (int i = 0; i < details->capacity1; i++)
		details->stud[i] = (struct student *)malloc(sizeof(struct student));
	details->capacity2 = 20;
	details->info = (struct studentinfo **)malloc(details->capacity2*sizeof(struct studentinfo*));
	for (int i = 0; i < details->capacity2; i++)
		details->info[i] = (struct studentinfo *)malloc(sizeof(struct studentinfo));
	details->lenght1 = 0;
	details->lenght2 = 0;
}

//Main function

int main()
{
	init();
	float average = 0.0f;
	int choice;
	while (1)
	{
		printf("1.Load Marks\n2.Load Info\n3.Calc CGPA and average\n4.Save marks info\n5.Join marks and info\n6.Show marks info\n7.ADvance query\n8.Exit\nChoice: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			loadmarks();
			break;
		case 2: loadinfo();
			break;
		case 3:calc();
			break;
		case 4:save();
			break;
		case 5:join();
			break;
		case 6:
			show();
			break;
		/*case 7:
			query();
			break;*/
		case 7:
			adquery();
			break;
		case 8:
			goto aa;
		default:
			printf("Wrong choice\n");
		}
		system("PAUSE");
		system("CLS");
	}
aa:
	return 0;
}

//It loads the marks information in the student structure and removes the duplicates 
//The current files are marks1.txt, marks2.txt, marks3.txt

int loadmarks()
{
	FILE *fp;
	char line[MAX_LINE_LENGTH];
	char name[MAX_LINE_LENGTH];
	printf("Enter MArks file name: ");
	scanf("%s", name);
	char *pTok;
	if ((fp = fopen(name, "r")) == NULL)
	{
		fprintf(stderr, "Cannot open file %s for input.\n", name);
		system("PAUSE");
		return 0;
	}
	fgets(line, MAX_LINE_LENGTH - 1, fp);
	while (fgets(line, MAX_LINE_LENGTH - 1, fp) != NULL)
	{
		if (details->lenght1 == 0)
		{
			pTok = strtok(line, delim);
			details->stud[0]->rollno = atoi(pTok);
			pTok = strtok(NULL, delim);
			if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
				continue;
			strcpy(details->stud[0]->name, pTok);
			pTok = strtok(NULL, delim);
			if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
				continue;
			details->stud[0]->exam1 = atof(pTok);
			pTok = strtok(NULL, delim);
			if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
				continue;
			details->stud[0]->exam2 = atof(pTok);
			pTok = strtok(NULL, delim);
			if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
				continue;
			details->stud[0]->exam3 = atof(pTok);
			pTok = strtok(NULL, delimLast);
			if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
				continue;
			details->stud[0]->exam4 = atof(pTok);
			details->stud[0]->avg = 0;
			details->stud[0]->cgpa = 0;
			details->lenght1 += 1;
		}
		else
		{
			pTok = strtok(line, delim);
			if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
				continue;
			int r = atoi(pTok);
			int c = 0;
			for (int i = 0; i < details->lenght1; i++)
				if (details->stud[i]->rollno == r)
				{
					c = 1;
					break;
				}
			if (c == 0)
			{
				if (details->lenght1 == details->capacity1)
				{
					details->capacity1 *= 2;
					details->stud = (struct student **)realloc(details->stud, details->capacity1*sizeof(struct student *));
					for (int i = details->lenght1; i < details->capacity1; i++)
						details->stud[i] = (struct student *)malloc(sizeof(struct student));
				}
				//pTok = strtok(line, delim);
				details->stud[details->lenght1]->rollno = r;
				pTok = strtok(NULL, delim);
				if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
					continue;
				strcpy(details->stud[details->lenght1]->name, pTok);
				pTok = strtok(NULL, delim);
				if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
					continue;
				details->stud[details->lenght1]->exam1 = atof(pTok);
				pTok = strtok(NULL, delim);
				if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
					continue;
				details->stud[details->lenght1]->exam2 = atof(pTok);
				pTok = strtok(NULL, delim);
				if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
					continue;
				details->stud[details->lenght1]->exam3 = atof(pTok);
				pTok = strtok(NULL, delimLast);
				if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
					continue;
				details->stud[details->lenght1]->exam4 = atof(pTok);
				details->stud[details->lenght1]->avg = 0;
				details->stud[details->lenght1]->cgpa = 0;
				details->lenght1 += 1;
			}
			else continue;
		}
		
	}
	fprintf(stderr, "Marks loaded\n", name);
	fclose(fp);
}

//It loads the student information in the info structure and removes the duplicates
//The current files are info1.txt, info2.txt, info3.txt

int loadinfo()
{
	FILE *fp;
	char line[MAX_LINE_LENGTH];
	char name[MAX_LINE_LENGTH];
	printf("Enter Info file name: ");
	scanf("%s", name);
	char *pTok;
	if ((fp = fopen(name, "r")) == NULL)
	{
		fprintf(stderr, "Cannot open file %s for input.\n", name);
		system("PAUSE");
		return 0;
	}
	fgets(line, MAX_LINE_LENGTH - 1, fp);
	while (fgets(line, MAX_LINE_LENGTH - 1, fp) != NULL)
	{
		if (details->lenght2 == 0)
		{
			pTok = strtok(line, delim);
			if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
				continue;
			details->info[0]->rollno = atoi(pTok);
			pTok = strtok(NULL, delim);
			if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
				continue;
			strcpy(details->info[0]->mob, pTok);
			pTok = strtok(NULL, delim);
			if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
				continue;
			strcpy(details->info[0]->add, pTok);
			pTok = strtok(NULL, delim);
			if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
				continue;
			strcpy(details->info[0]->city, pTok);
			pTok = strtok(NULL, delimLast);
			if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
				continue;
			details->info[0]->pincode = atoi(pTok);
			details->lenght2 += 1;
		}
		else
		{
			pTok = strtok(line, delim);
			if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
				continue;
			int r = atoi(pTok);
			int c = 0;
			for (int i = 0; i < details->lenght2; i++)
				if (details->info[i]->rollno == r)
				{
					c = 1;
					break;
				}
			if (c == 0)
			{
				if (details->lenght2 == details->capacity2)
				{
					details->capacity2 *= 2;
					details->info = (struct studentinfo **)realloc(details->info,details->capacity2*sizeof(struct studentinfo*));
					for (int i = details->lenght2; i < details->capacity2; i++)
						details->info[i] = (struct studentinfo *)malloc(sizeof(struct studentinfo));
				}
				//pTok = strtok(line, delim);
				details->info[details->lenght2]->rollno = r;
				pTok = strtok(NULL, delim);
				if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
					continue;
				strcpy(details->info[details->lenght2]->mob,pTok);
				pTok = strtok(NULL, delim);
				if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
					continue;
				strcpy(details->info[details->lenght2]->add, pTok);
				pTok = strtok(NULL, delim);
				if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
					continue;
				strcpy(details->info[details->lenght2]->city, pTok);
				pTok = strtok(NULL, delimLast);
				if (pTok == NULL || *pTok == NULL_CHAR || *pTok == '\n')
					continue;
				details->info[details->lenght2]->pincode = atoi(pTok);
				details->lenght2 += 1;
			}
			else continue;
		}

	}
	fprintf(stderr, "Info loaded\n", name);
	fclose(fp);
}
/*
int length(char *name)
{
	FILE *fp1;
	char buff[MAX_LINE_LENGTH];
	int realcount = 0;
	fp1 = fopen(name, "r");
	if (fp1 == NULL)
		return 0;
	else
	{
		while (fgets(buff, MAX_LINE_LENGTH - 1, fp1))
		{
			realcount++;
		}
	}
	realcount--;
	return realcount;
}*/





//It calulates the average and cgpa if marks file is loaded


void calc()
{
	if (details->lenght1 == 0)
		printf("Cant calculate the average and cgpa. NO table is loaded\n");
	else
	{

	for (int i = 0; i < details->lenght1; i++)
	{
		details->stud[i]->avg = (details->stud[i]->exam1 + details->stud[i]->exam2 + details->stud[i]->exam3 + details->stud[i]->exam4) / (float)4.0;
		details->stud[i]->cgpa = (int)details->stud[i]->avg / (int)10;
	}
	printf("average and cgpa calulated\n");
	}
	/*check3 = 1;*/
}

//It shows the student marks details incuding average and cgpa


void show()
{
	if (details->lenght1 == 0)
		printf("Marks table isnt loaded.\n");
	else
	{

	printf("RollNo	Name	Marks1		Marks2		marks3		Marks4		Average		CGPA\n");
	for (int i = 0; i < details->lenght1; i++){
		if (details->stud[i]->cgpa != 0)
			printf("%d	%s	%f	%f	%f	%f	%f	%d\n", details->stud[i]->rollno, details->stud[i]->name, details->stud[i]->exam1, details->stud[i]->exam2, details->stud[i]->exam3, details->stud[i]->exam4, details->stud[i]->avg, details->stud[i]->cgpa);
		else
			printf("%d	%s	%f	%f	%f	%f	NaN	Nan\n", details->stud[i]->rollno, details->stud[i]->name, details->stud[i]->exam1, details->stud[i]->exam2, details->stud[i]->exam3, details->stud[i]->exam4);
	}
	}

}

//It saves the student marks details incuding average and cgpa in a file. Input file name given by the user

void save()
{
	if (details->lenght1 == 0)
		printf("CAnt dave no table is loaded.\n");
	else
	{

	FILE *fp;
	printf("Enter file name to save the details:");
	char name[MAX_LINE_LENGTH];
	scanf(" %s", name);
	fp = fopen(name, "w");
	fprintf(fp, "RollNo,	Name,	Marks1,	Marks2,	marks3,	Marks4,	Average,	CGPA\n");
	for (int i = 0; i < details->lenght1; i++){
		if (details->stud[i]->cgpa != 0)
			fprintf(fp,"%d,	%s,	%f,	%f,	%f,	%f,	%f,	%d\n", details->stud[i]->rollno, details->stud[i]->name, details->stud[i]->exam1, details->stud[i]->exam2, details->stud[i]->exam3, details->stud[i]->exam4, details->stud[i]->avg, details->stud[i]->cgpa);
		else
			fprintf(fp,"%d,	%s,	%f,	%f,	%f,	%f,	NaN,	Nan\n", details->stud[i]->rollno, details->stud[i]->name, details->stud[i]->exam1, details->stud[i]->exam2, details->stud[i]->exam3, details->stud[i]->exam4);
	}
	printf("Details saved in %s\n",name);
	fclose(fp);
	}
}

//It saves the student marks details incuding average and cgpa in a file. Input file name given by the user.

void join()
{
	if (details->lenght1 == 0)
		printf("CAnt dave no table is loaded.\n");
	else
	{
	printf("RollNo	Name	Marks1		Marks2		marks3		Marks4		Average		CGPA	MobileNo	ADDress		City	Pincode\n");
	if (details->lenght1 == 0)
		return;
	int check5;
	for (int i = 0; i < details->lenght1; i++)
	{
		check5 = 0;
		if (details->lenght2 == 0)
		{
			if (details->stud[i]->cgpa != 0)
			{
				printf("%d	%s	%f	%f	%f	%f	%f	%d	NaN	NaN	NaN	NaN\n", details->stud[i]->rollno, details->stud[i]->name, details->stud[i]->exam1, details->stud[i]->exam2, details->stud[i]->exam3, details->stud[i]->exam4, details->stud[i]->avg, details->stud[i]->cgpa);
				continue;
			}
			else
			{
				printf("%d	%s	%f	%f	%f	%f	NaN	Nan	NaN	NaN	NaN	NaN\n", details->stud[i]->rollno, details->stud[i]->name, details->stud[i]->exam1, details->stud[i]->exam2, details->stud[i]->exam3, details->stud[i]->exam4);
				continue;
			}
		}
		else
			for (int j = 0; j < details->lenght2; j++)
			{
				if (details->stud[i]->cgpa != 0)
				{

					if (details->stud[i]->rollno == details->info[j]->rollno){

						printf("%d	%s	%f	%f	%f	%f	%f	%d	%s	%s	%s	%d\n", details->stud[i]->rollno, details->stud[i]->name, details->stud[i]->exam1, details->stud[i]->exam2, details->stud[i]->exam3, details->stud[i]->exam4, details->stud[i]->avg, details->stud[i]->cgpa, details->info[j]->mob, details->info[j]->add, details->info[j]->city, details->info[j]->pincode);
						check5 = 1;
						break;
					}
					else
					{
						continue;
					}
				}
				else
				{
					if (details->stud[i]->rollno == details->info[j]->rollno){

						printf("%d	%s	%f	%f	%f	%f	NaN		NaN		%s	%s	%s	%d\n", details->stud[i]->rollno, details->stud[i]->name, details->stud[i]->exam1, details->stud[i]->exam2, details->stud[i]->exam3, details->stud[i]->exam4, details->info[j]->mob, details->info[j]->add, details->info[j]->city, details->info[j]->pincode);
						check5 = 1;
						break;
					}
					else
					{
						continue;
					}
				}

			}
		if (check5 == 0)
		{

			if (details->stud[i]->cgpa != 0)
			{
				printf("%d	%s	%f	%f	%f	%f	%f	%d	NaN		NaN		NaN		NaN	\n", details->stud[i]->rollno, details->stud[i]->name, details->stud[i]->exam1, details->stud[i]->exam2, details->stud[i]->exam3, details->stud[i]->exam4, details->stud[i]->avg, details->stud[i]->cgpa);
			}
			else
			{
				printf("%d	%s	%f	%f	%f	%f	NaN		NaN		Nan		NaN		NaN		NaN		NaN\n", details->stud[i]->rollno, details->stud[i]->name, details->stud[i]->exam1, details->stud[i]->exam2, details->stud[i]->exam3, details->stud[i]->exam4, details->stud[i]->avg, details->stud[i]->cgpa);
			}
		}
	}
	}
}
// simple function to chck wheter a substring exist or not. Used in contains query

int contains(char *str, char *search)
{
	int count1 = strlen(str);
	int count2 = strlen(search);
	int i, j, flag;

	for (i = 0; i <= count1 - count2; i++)
	{
		for (j = i; j < i + count2; j++)
		{
			flag = 1;
			if (str[j] != search[j - i])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
			break;
	}
	if (flag == 1)
		return 1;
	else
		return 0;
}

//Simple query checker wheter its valid or not.


int querychecker(char* query)
{
	char standard[MAX_LINE_LENGTH];
	strcpy(standard, "select {display} from {tablename} where {attribute} {option} {value}");
	char* tok1;
	char* tok2;
	char* tok3;
	tok1 = strtok(query, " ");
	strtok(NULL, " ");
	tok2 = strtok(NULL, " ");
	strtok(NULL, " ");
	tok3 = strtok(NULL, " ");
	char* tok4;
	char* tok5;
	char* tok6;
	tok4 = strtok(standard, " ");
	strtok(NULL, " ");
	tok5 = strtok(NULL, " ");
	strtok(NULL, " ");
	tok6 = strtok(NULL, " ");
	if (strcmp(tok1, tok4) == 0 && strcmp(tok2, tok5) == 0 && strcmp(tok3, tok6) == 0)
		return 1;
	else return 0;
}

//Query execution
/*
	Simple query handler
	Query format example: select * from student where exam1 gt 50

	Note1:For now only works with student structure and query whould in proper format with no extra spaces
	Note2:CAn only display single or total columns at a time based on query
	Note3:Before query execution load marks table and calculate the avg and cgpa
	table name: student
	Columns available: 
					rollno
					name
					exam1
					exam2
					exam3
					exam4
					avg
					cgpa
			For all: *
		options are:
					gt : greater than
					select * from student where exam1 gt 50

					eq : equal
					select * from student where rollno eq 8

					lt : less than
					select * from student where exam3 lt 50

					ge : greater than or qual to
					select * from student where exam4 ge 50

					le : less than or equal to
					select * from student where avg le 50

					contains : contains name
					select * from student where name contains ll

					startswith : name startstih 
					select * from student where name startswith G

		Insteas of star we can use any columns name like name, rollno etc


*/

void adquery()
{
	printf("Enter query: ");
	char query[MAX_LINE_LENGTH];
	//gets(query);
	//fgets(query, MAX_LINE_LENGTH, stdin);
	scanf(" %[^\n]", query);
	char query2[MAX_LINE_LENGTH];
	strcpy(query2, query);
	if (querychecker(query))
	{

	char* tok1;
	char* tok2;
	char* tok3;
	strtok(query2, " ");
	tok1 = strtok(NULL, " ");
	strtok(NULL, " ");
	tok2 = strtok(NULL, " ");
	strtok(NULL, " ");
	tok3 = strtok(NULL, delimLast);
	int index[30];
	int len = 0;
	void getind(char* tok, int* index, int *len);
	getind(tok3, index, &len);
	void printans(char* tok, int* index, int *len);
	printans(tok1, index, &len);
	}
	else printf("Wrong query\n");
	//scanf("%256[^\n]", query);
}

//Finds all the indices which mathch the subquery

void getind(char* tok, int* index,int *len)
{
	float get(char* key, int i);
	char* tok1;
	char* tok2;
	char* tok3;
	tok1 = strtok(tok, " ");
	tok2 = strtok(NULL, " ");
	tok3 = strtok(NULL, delimLast);
	if (strcmp(tok2, "startswith") == 0 || strcmp(tok2, "contains") == 0)
	{
		char name[MAX_LINE_LENGTH];
		if (strcmp(tok2, "startswith") == 0)
		{
			for (int i = 0; i < details->lenght1; i++)
			{
				if (details->stud[i]->name[0] == tok3[0])
				{
					index[*len] = i;
					(*len)++;
				}
			}
		}
		else if (strcmp(tok2, "contains") == 0)
		{
			for (int l = 0; l < details->lenght1; l++)
			{
				if (contains(details->stud[l]->name,tok3))
				{
					index[*len] = l;
					(*len)++;

				}
			}
		}
		else printf("Wrong query");

	}
	else
	{
			if (strcmp(tok2, "lt") == 0)
			{
				for (int i = 0; i < details->lenght1; i++)
					if (get(tok1,i) < atoi(tok3))
					{
						index[*len] = i;
						(*len)++;
					}
			}
			else if (strcmp(tok2, "eq") == 0)
			{
				for (int i = 0; i < details->lenght1; i++)
					if (get(tok1, i) == atoi(tok3))
					{
						index[*len] = i;
						(*len)++;
					}
			}
			else if (strcmp(tok2, "gt") == 0)
			{
				for (int i = 0; i < details->lenght1; i++)
					if (get(tok1, i) > atoi(tok3))
					{
						index[*len] = i;
						(*len)++;
					}
			}
			else if (strcmp(tok2, "le") == 0)
			{
				for (int i = 0; i < details->lenght1; i++)
					if (get(tok1, i) <= atoi(tok3))
					{
						index[*len] = i;
						(*len)++;
					}
			}
			else if (strcmp(tok2, "ge") == 0)
			{
				for (int i = 0; i < details->lenght1; i++)
					if (get(tok1, i) >= atoi(tok3))
					{
						index[*len] = i;
						(*len)++;
					}
			}
			else printf("Wrong query");
		}
}

//Function contains all tha hash value of constant columns name

int getcoldetail(int i){
	int a[9] = { gethash("exam1"), gethash("exam2"), gethash("exam3")+1, gethash("exam3"), gethash("avg"), gethash("cgpa"), gethash("rollno"), gethash("name"),gethash("*") };
	return a[i];
}

//returns the value that matches the hash value mapped coumns name


float get(char* key,int i)
{
	int x = gethash(key);
	if (x == getcoldetail(0))
		return details->stud[i]->exam1;
	else if (x == getcoldetail(1))
		return details->stud[i]->exam2;
	else if (x == getcoldetail(2))
		return details->stud[i]->exam3;
	else if (x == getcoldetail(3))
		return details->stud[i]->exam4;
	else if (x == getcoldetail(4))
		return details->stud[i]->avg;
	else if (x == getcoldetail(5))
		return details->stud[i]->cgpa;
	else if (x == getcoldetail(6))
		return details->stud[i]->rollno;
}

//FOr printing the query output

void printans(char* tok, int* index, int *len)
{
	if (*len == 0)
		printf("No ouput.May be synatax error in query or wrong query\n");
	else{

	int x = gethash(tok);
	if (x == getcoldetail(8))
	{
		for (int i = 0; i < (*len); i++)
			printf("%d	%s	%f	%f	%f	%f	%f	%d\n", details->stud[index[i]]->rollno, details->stud[index[i]]->name, details->stud[index[i]]->exam1, details->stud[index[i]]->exam2, details->stud[index[i]]->exam3, details->stud[index[i]]->exam4, details->stud[index[i]]->avg, details->stud[index[i]]->cgpa);
		return;
	}
	else if (x == getcoldetail(0))
		for (int i = 0; i < (*len); i++)
		printf("%f\n", details->stud[index[i]]->exam1);
	else if (x == getcoldetail(1))
		for (int i = 0; i < (*len); i++)
		printf("%f\n", details->stud[index[i]]->exam2);
	else if (x == getcoldetail(2))
		for (int i = 0; i < (*len); i++)
		printf("%f\n", details->stud[index[i]]->exam3);
	else if (x == getcoldetail(3))
		for (int i = 0; i < (*len); i++)
		printf("%f\n", details->stud[index[i]]->exam4);
	else if (x == getcoldetail(4))
		for (int i = 0; i < (*len); i++)
		printf("%f\n", details->stud[index[i]]->avg);
	else if (x == getcoldetail(5))
		for (int i = 0; i < (*len); i++)
		printf("%d\n", details->stud[index[i]]->cgpa);
	else if (x == getcoldetail(6))
		for (int i = 0; i < (*len); i++)
		printf("%d\n", (int)details->stud[index[i]]->rollno);
	else if (x == getcoldetail(7))
		for (int i = 0; i < (*len); i++)
		printf("%s\n", details->stud[index[i]]->name);
	else printf("Wrong cloumn. \n");
	}
	/*tok2 = strtok(NULL, ",");
	else{
		for (int i = 0; i < (*len); i++)
		{
			char tok1[MAX_LINE_LENGTH];
			strcpy(tok1, tok);
			char* tok2;
			tok2 = strtok(tok1, ",");
			while (tok2 != NULL)
			{
				int x = gethash(tok2);
				if (x == getcoldetail(0))
					printf("%f", details->stud[index[i]]->exam1);
				else if (x == getcoldetail(1))
					printf("%f", details->stud[index[i]]->exam2);
				else if (x == getcoldetail(2))
					printf("%f", details->stud[index[i]]->exam3);
				else if (x == getcoldetail(3))
					printf("%f", details->stud[index[i]]->exam4);
				else if (x == getcoldetail(4))
					printf("%f", details->stud[index[i]]->avg);
				else if (x == getcoldetail(5))
					printf("%f", details->stud[index[i]]->cgpa);
				else if (x == getcoldetail(6))
					printf("%f", details->stud[index[i]]->rollno);
				else if (x == getcoldetail(7))
					printf("%f", details->stud[index[i]]->name);
				tok2 = strtok(NULL, ",");
			}
		}*/
		
	//}
	
}

// Hash function

static int gethash(char* source)
{
	if (source == NULL) {
		return 0;
	}

	long long hash = 0;
	while (*source != '\0') {
		char c = *source++;
		int a = c - '0';
		hash = (hash * 59) + a;
	}
	return hash%61;
}