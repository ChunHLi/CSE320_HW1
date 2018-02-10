#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

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
		for (int i=0; i<start; i++){
			current = (node*)(current->next);
		}
		for (int i=start; i<length(srs); i++){
			if (current->id == find_id){
				return current;
			}		
		}	
		return NULL;
	}
}

node* findName(int start, char* find_name, student_records *srs){
	if (start > length(srs)){
		return NULL;
	} else {
		node* current = srs->head;
		for (int i=0; i<start; i++){
			current = (node*)(current->next);
		}
		for (int i=start; i<length(srs); i++){
			if (current->last_name == find_name){
				return current;
			}		
		}
		return NULL;
	}
}

node* findMajor(int start, char* find_major, student_records *srs){
	if (start > length(srs)){
		return NULL;
	} else {
		node* current = srs->head;
		for (int i=0; i<start; i++){
			current = (node*)(current->next);
		}
		for (int i=start; i<length(srs); i++){
			if (current->major == find_major){
				return current;
			}		
		}
		return NULL;
	}
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
			if (current->last_name==find_last_name){
				printf("%d %s %s %.2f %s\n",current->id,current->first_name,current->last_name,current->gpa,current->major);		
				count = count + 1;
			}
		}
		if (listType == 4){
			if (current->major==find_major){
				printf("%d %s %s %.2f %s\n",current->id,current->first_name,current->last_name,current->gpa,current->major);
				count = count + 1;
			}
		}
		if (listType == 5){
			if (current->last_name==find_last_name && current->major==find_major){
				printf("%d %s %s %.2f %s\n",current->id,current->first_name,current->last_name,current->gpa,current->major);
				count = count + 1;
			}
		}
	}
	if (count == 0){
		printf("ERROR: STUDENT RECORD NOT FOUND");
	}
	printf("\n");
}

/*
 *	insert in order of ID
 *	if inserting duplicate ID, 
 *	then print error "ID NOT UNIQUE"
 */

void insertNode(int new_id, char* new_first_name, char* new_last_name, float new_gpa, char* new_major, student_records *srs){
	if (findID(0,new_id,srs)!=NULL){
		printf("ERROR: ID NOT UNIQUE\n");
	} else {
		node* link = (node*)malloc(sizeof(struct node));
		link->id = new_id;
		link->first_name = new_first_name;
		link->last_name = new_last_name;
		link->gpa = new_gpa;
		link->major = new_major;
		node* previous=NULL;
		node* current = srs->head;
		for (int i = 0; i < length(srs); i++){
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
		printf("ERROR: STUDENT RECORD CANNOT BE DELETED NOR UPDATED");
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
	printf("ERROR: STUDENT RECORD CANNOT BE DELETED NOR UPDATED");
	return NULL;
}

void updateNode(int new_ID, char* new_first_name, char* new_last_name, float new_gpa, char* new_major, student_records *srs) {
	deleteNode(new_ID, srs);
	insertNode(new_ID, new_first_name, new_last_name, new_gpa, new_major, srs);
}

int lengthOfString(char* src){
	int counter = 0;
	while (*(src+counter) != '\0'){
		counter += 1;
	} counter += 1;
	return counter;
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
	char* str = (char*)malloc(sizeof(lengthOfWord(src,*counter)));
	while ((*(src+*counter) != '\n') && (*(src+*counter) != ' ') && (*(src+*counter) != '\0')){
		*(str+strCounter) = *(src+*counter);
		*counter += 1;
		strCounter += 1;
	}
	*(str+strCounter) = '\0';
	return str;
}

int main(int argc, char** argv) {
	int c;
	int vflag = 0;
	int oflag = 0;
	char* output = NULL;
	int iflag = 0;
	char* id = NULL;
	int fflag = 0;
	char* lastname = NULL;
	int mflag = 0;
	char* major = NULL;
	char* filename = NULL;
	if (argc < 3){
		exit(1);
	} else {
		filename = *(argv+1);
                printf("%s\n",filename);
	}
	while ((c = getopt(argc,argv,"vo:f:i:m:"))!= -1){
		switch (c) {
			case 'v' :
				/*printf("v\n");*/
				vflag++;
				break;
			case 'o' :
				/*printf("o\n");*/
				output = optarg;
				printf("%s\n",output);
				oflag++;
				break;
			case 'f' :
				/*printf("f\n");*/
				lastname = optarg;
				printf("%s\n",lastname);
				fflag++;
				break;
			case 'i' :
				/*printf("i\n");*/
				id = optarg;
				printf("%s\n",id);		
				iflag++;
				break;
			case 'm' :
				/*printf("m\n");*/
				major = optarg;
				printf("%s\n",major);
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
			printf("FAILED TO PARSE FILE");
			exit(EXIT_FAILURE);
 		}
		while ((read = getline(&line, &len, stream)) != -1) {
		
		}
 
		free(line);
		fclose(stream);
		exit(EXIT_SUCCESS);
	}
  	return 0;
}
