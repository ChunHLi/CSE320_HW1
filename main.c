#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>

char* ADD = "ADD";
char* DELETE = "DELETE";
char* UPDATE = "UPDATE";

/*
 *	nodes used to store data in linked lists
 */

typedef struct node {
	
	int id;
	char* first_name;
	char* last_name;
	float gpa;
	char* major;

	int index;
	struct node* next;
} node;

typedef struct student_records{
	node* head;
} student_records;

void initRecords(struct student_records *srs){
	srs->head = NULL;
}


/*
 *	returns length of linked list
 */

int length(student_records *srs) {
	int length = 0;
	node* current;
	for (current=srs->head; current != NULL; current=(node*)(current->next)){
		length++;
	}
	return length;
}

/*
 *	starting from a given index, searches for a node that matches requi *      rement
 */

node* findID(int start, int find_id, student_records *srs){
	if (start > length(srs)){
		return NULL;
	} else {
		node* current = srs->head;
		int i = 0;
		for (i=0; i<start; i++){
			current = (node*)(current->next);
		}
		i = start;
		for (i=start; i<length(srs); i++){
			if (current->id == find_id){
				return current;
			}
			current = (node*)(current->next);		
		}	
		return NULL;
	}
}

node* findName(int start, char* find_name, student_records *srs){
	if (start > length(srs)){
		return NULL;
	} else {
		node* current = srs->head;
		int i = 0;
		for (i=0; i<start; i++){
			current = (node*)(current->next);
		}
		i = start;
		for (i=start; i<length(srs); i++){
			if (current->last_name == find_name){
				return current;
			}
			current = (node*)(current->next);			
		}
		return NULL;
	}
}

node* findMajor(int start, char* find_major, student_records *srs){
	if (start > length(srs)){
		return NULL;
	} else {
		node* current = srs->head;
		int i = 0;
		for (i=0; i<start; i++){
			current = (node*)(current->next);
		}
		i = start;
		for (i=start; i<length(srs); i++){
			if (current->major == find_major){
				return current;
			}
					
		}
		return NULL;
	}
}


int lengthOfString(char* src){
	int counter = 0;
	while (*(src+counter) != '\0'){
		counter += 1;
	} counter += 1;
	return counter;
}

int strEquals(char* str1, char* str2){
	int counter = 0;
	int len1 = lengthOfString(str1);
	int len2 = lengthOfString(str2);
	if (len1 != len2){
		return 0;
	} else {
		while (counter < len1){
			if (*(str1+counter) != *(str2+counter)){
				return 0;
			}
			counter += 1;
		}
		return 1;
	}
}

int lengthOfWord(char* src, int start){
	int counter = 0;
	while ((*(src+start+counter) != '\n') && (*(src+start+counter) != ' ') && (*(src+start+counter) != '\0')){
		counter += 1;
	}
	counter += 1; /*for null terminator*/
	return counter;
}

char* nextWhitespace(char* src, int *counter){
	int strCounter = 0;
	char* str = (char*)malloc(lengthOfWord(src,*counter));
	while ((*(src+*counter) != '\n') && (*(src+*counter) != ' ') && (*(src+*counter) != '\0')){
		*(str+strCounter) = *(src+*counter);
		*counter += 1;
		strCounter += 1;
	}
	*(str+strCounter) = '\0';
	return str;
}

char* nameFormat(char* src){
	int counter = 0;
	char* str = (char*)malloc(lengthOfWord(src,0));
	if (isalpha(*(src+0))==0){
		printf("FAILED TO PARSE FILE\n");
		exit(1);
	}
	*(str+0) = toupper(*(src+0));
	counter += 1;
	while ((*(src+counter) != '\n') && (*(src+counter) != ' ') && (*(src+counter) != '\0')){
		if (isalpha(*(src+counter))==0){
			printf("FAILED TO PARSE FILE\n");
			exit(1);
		}
		*(str+counter) = tolower(*(src+counter));
		counter += 1;
	}
	*(str+counter) = '\0';
	return str;
}

char* capitalize(char* src){
	int counter = 0;
	char* str = (char*)malloc(lengthOfWord(src,0));
	while ((*(src+counter) != '\n') && (*(src+counter) != ' ') && (*(src+counter) != '\0')){
		if (isalpha(*(src+counter))==0){
			printf("FAILED TO PARSE FILE\n");
			exit(1);
		}
		*(str+counter) = toupper(*(src+counter));
		counter += 1;
	}
	*(str+counter) = '\0';
	return str;
}

int allDigit(char* src){
	int counter = 0;
	while ( (*(src+counter) != '\n') && (*(src+counter) != ' ') && (*(src+counter)!='\0')){
		if ((isdigit(*(src+counter))==0)){
			return 0;
		}
		counter += 1;	
	}
	return 1;
}

int allDigitF(char* src){
	int counter = 0;
	while ( (*(src+counter) != '\n') && (*(src+counter) != ' ') && (*(src+counter)!='\0')){
		if ((isdigit(*(src+counter))==0)&&(*(src+counter)!='.')){
			return 0;
		}
		counter += 1;	
	}
	return 1;
}

int allAlpha(char* src){
	int counter = 0;
	while ( (*(src+counter) != '\n') && (*(src+counter) != ' ') && (*(src+counter)!='\0')){
		if ((isalpha(*(src+counter))==0)){
			return 0;
		}
		counter += 1;	
	}
	return 1;
}

/*
 	ways to print list:
 *	1. all students
 *	2. match id
 *	3. match last_name
 *	4. match major
 *	5. match major and last_name
 *
 *	if list is empty or in other words, no student matches the flags,
 *	then print error "STUDENT RECORD NOT FOUND"
 */

void printList(int listType, int find_id, char* find_last_name, char* find_major, student_records *srs){
	node* current;
	int count = 0;
	for (current=srs->head; current!=NULL; current=(node*)(current->next)){
		if (listType == 1){
			printf("%d %s %s %.2f %s\n",current->id,current->first_name,current->last_name,current->gpa,current->major);
			count = count + 1;
		}
		if (listType == 2){
			if (current->id==find_id){
				printf("%d %s %s %.2f %s\n",current->id,current->first_name,current->last_name,current->gpa,current->major);
				count = count + 1;
			}
		}
		if (listType == 3){
			if (strEquals(current->last_name,find_last_name)){
				printf("%d %s %s %.2f %s\n",current->id,current->first_name,current->last_name,current->gpa,current->major);		
				count = count + 1;
			}
		}
		if (listType == 4){
			if (strEquals(current->major,find_major)){
				printf("%d %s %s %.2f %s\n",current->id,current->first_name,current->last_name,current->gpa,current->major);
				count = count + 1;
			}
		}
		if (listType == 5){
			if (strEquals(current->last_name,find_last_name) && strEquals(current->major,find_major)){
				printf("%d %s %s %.2f %s\n",current->id,current->first_name,current->last_name,current->gpa,current->major);
				count = count + 1;
			}
		}
	}
	if (count == 0){
		printf("STUDENT RECORD NOT FOUND\n");
		exit(1);
	}
}

/*
 *	insert in order of ID
 *	if inserting duplicate ID, 
 *	then print error "ID NOT UNIQUE"
 */

void insertNode(int new_id, char* new_first_name, char* new_last_name, float new_gpa, char* new_major, student_records *srs){
	if (findID(0,new_id,srs)!=NULL){
		printf("ID NOT UNIQUE\n");
		exit(1);
	} else {
		node* link = (node*)malloc(sizeof(struct node));
		link->id = new_id;
		link->first_name = new_first_name;
		link->last_name = new_last_name;
		link->gpa = new_gpa;
		link->major = new_major;
		node* previous=NULL;
		node* current = srs->head;
		int i = 0;
		for (i = 0; i < length(srs); i++){
			if (current->id > link->id){
				if (i == 0){
					link->next = srs->head;
					srs->head = link;
					link->index = 0;
					node* tempLink = (node*)(link->next);
					while (tempLink != NULL){
						tempLink->index = tempLink->index + 1;
						tempLink = tempLink->next;
					}
					break;
				}
				else{
					link->next = current;
					previous->next = link;
					link->index = i;
					node* tempLink = (node*)(link->next);
					while (tempLink != NULL){
						tempLink->index = tempLink->index + 1;
						tempLink = (node*)(tempLink->next);
					}	
					break;
				}
			}
			previous = current;
			current = (node*)(current->next);
		}
		if (srs->head==NULL){
			srs->head = link;
			srs->head->next = NULL;
			srs->head->index = 0;
		}
		else if (current==NULL){
			previous->next = link;
			link->next = NULL;
			link->index = length(srs);
		}
	}	
}

/*
 *	delete node that matches ID
 *	if deleting node that doesn't exist aka equals NULL or
 *	no ID match,
 *	then print error "STUDENT RECORD CANNOT BE DELETED NOR UPDATED" 
 */

node* deleteNode(int id_to_delete, student_records *srs) {
	if (length(srs)==0){
		printf("STUDENT RECORD CANNOT BE DELETED NOR UPDATED");
		exit(1);
		return NULL;
	}
	if (srs->head->id == id_to_delete){
		node* temp = srs->head;
		srs->head = (node*)(srs->head->next);
		return srs->head;
	}
	node* previous=NULL;
	node* current;
	for (current=srs->head;current!=NULL;current=(node*)(current->next)){
		if (current->id == id_to_delete){
			node* temp = current;
			previous->next = (node*)(current->next);
			return temp;
		}
		previous = current;
	}
	printf("STUDENT RECORD CANNOT BE DELETED NOR UPDATED\n");
	exit(1);
	return NULL;
}

void updateNode(int new_ID, char* new_first_name, char* new_last_name, float new_gpa, char* new_major, student_records *srs) {
	deleteNode(new_ID, srs);
	insertNode(new_ID, new_first_name, new_last_name, new_gpa, new_major, srs);
}



int main(int argc, char** argv) {
	int c;
	int vflag = 0;
	int oflag = 0;
	char* output = NULL;
	int iflag = 0;
	int id = 0;
	int fflag = 0;
	char* lastname = NULL;
	int mflag = 0;
	char* major = NULL;
	char* filename = NULL;
	if (argc < 3){
		printf("NO QUERY PROVIDED\n");
		exit(1);
	} else {
		filename = *(argv+1);
	}
	while ((c = getopt(argc,argv,"vo:f:i:m:"))!= -1){
		switch (c) {
			case 'v' :
				vflag++;
				break;
			case 'o' :
				output = optarg;
				oflag++;
				struct stat st;
    				int result = stat(output, &st);
    				if (result == 0) {
					printf("File already exists...\n");
					printf("Do you wish to override existing file?\n");
					char ch = 0;
					while (ch != 'y' && ch != 'n' && ch != 'Y' && ch != 'N'){
						printf("Input 'y' or 'n':");
						if (ch != 0) {
							printf("%c is not a valid option",ch);
						}
						ch = getchar();
						getchar();
					} 
					if (ch == 'y' || ch == 'Y') {
						printf("%s was overwritten\n",output);
					} else {
						printf("%s was not overwritten\n", output);
						exit(1);
					}
				}
				break;
			case 'f' :
				lastname = optarg;
				if (allAlpha(lastname)==0){
					printf("OTHER ERROR\n");
					exit(1);
				}
				fflag++;
				break;
			case 'i' :
				if (allDigit(optarg)==0){
					printf("OTHER ERROR\n");
					exit(1);
				}
				id = atoi(optarg);		
				iflag++;
				break;
			case 'm' :
				major = optarg;
				if (allAlpha(major)==0){
					printf("OTHER ERROR\n");
					exit(1);
				}
				mflag++;
				break;
			default:
				break;
		}	
	}
	if (!(vflag || oflag || iflag || fflag || mflag)) {
		printf("NO QUERY PROVIDED\n");
	} else if ((vflag && (iflag || fflag || mflag))||
			(oflag && !(vflag || iflag || fflag || mflag))){
		printf("OTHER ERROR\n");
	} else {
		FILE *stream;
		char *line = NULL;
		size_t len = 0;
		ssize_t read;
 
		stream = fopen(filename, "r");
		if (stream == NULL){
			printf("FAILED TO PARSE FILE\n");
			exit(EXIT_FAILURE);
 		}
		struct student_records *srs = malloc(sizeof(struct student_records));
		initRecords(srs);
		while ((read = getline(&line, &len, stream)) != -1) {
			int counter = 0;
			char* function = nextWhitespace(line, &counter);
			counter += 1;
			if (strEquals(function,ADD) || strEquals(function,UPDATE)){
				char* str_given_id = nextWhitespace(line, &counter);
				if (!allDigit(str_given_id)){
					printf("FAILED TO PARSE FILE\n");
					exit(1);
				}
				int given_id = atoi(str_given_id);
				counter += 1;
				char* given_first_name = nameFormat(nextWhitespace(line, &counter));
				counter += 1;
				char* given_last_name = nameFormat(nextWhitespace(line, &counter));
				counter += 1;
				char* str_given_gpa = nextWhitespace(line,&counter);
				if (!allDigitF(str_given_gpa)){
					printf("FAILED TO PARSE FILE\n");
					exit(1);
				}
				double given_gpa = atof(str_given_gpa);
				counter += 1;
				char* given_major = capitalize(nextWhitespace(line,&counter));
				if (strEquals(function,ADD)){
					insertNode(given_id,given_first_name,given_last_name,given_gpa,given_major,srs);
				} else {
					updateNode(given_id,given_first_name,given_last_name,given_gpa,given_major,srs);	
				}
			} else if (strEquals(function,DELETE)){
				int given_id = atoi(nextWhitespace(line, &counter));
				deleteNode(given_id, srs);
			} else {
				printf("FAILED TO PARSE FILE\n");
				free(line);
				fclose(stream);
				exit(EXIT_SUCCESS);
			}		
		}
		
		if (oflag) {
			freopen (output,"w",stdout);	
		}
		if (vflag) {
			printList(1,id,lastname,major,srs);
		} else if (iflag) {
			printList(2,id,lastname,major,srs);
		} else if (mflag && fflag) {
			printList(5,id,lastname,major,srs);
		} else if (mflag) {
			printList(4,id,lastname,major,srs);
		} else if (fflag) {
			printList(3,id,lastname,major,srs);
		} else {
			printf("OTHER ERROR\n");
			exit(1);
		}
		if (oflag) {
			fclose (stdout);
		} 

		free(line);
		fclose(stream);
		exit(EXIT_SUCCESS);
		
	}
  	return 0;
}
