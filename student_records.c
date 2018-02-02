#include <stdio.h>
#include <stdlib.h>

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
} student_records;

node* head = NULL;


/*
 *	returns length of linked list
 */

int length() {
	int length = 0;
	node* current;
	for (current=head; current != NULL; current=(node*)(current->next)){
		length++;
	}
	return length;
}

/*
 *	starting from a given index, searches for a node that matches requi *      rement
 */

node* findID(int start, int find_id){
	if (start > length()){
		return NULL;
	} else {
		node* current = head;
		for (int i=0; i<start; i++){
			current = (node*)(current->next);
		}
		for (int i=start; i<length(); i++){
			if (current->id == find_id){
				return current;
			}		
		}	
		return NULL;
	}
}

node* findName(int start, char* find_name){
	if (start > length()){
		return NULL;
	} else {
		node* current = head;
		for (int i=0; i<start; i++){
			current = (node*)(current->next);
		}
		for (int i=start; i<length(); i++){
			if (current->last_name == find_name){
				return current;
			}		
		}
		return NULL;
	}
}

node* findMajor(int start, char* find_major){
	if (start > length()){
		return NULL;
	} else {
		node* current = head;
		for (int i=0; i<start; i++){
			current = (node*)(current->next);
		}
		for (int i=start; i<length(); i++){
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

void printList(int listType, int find_id, char* find_last_name, char* find_major){
	node* current;
	int count = 0;
	for (current=head; current!=NULL; current=(node*)(current->next)){
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

void insertNode(int new_id, char* new_first_name, char* new_last_name, float new_gpa, char* new_major){
	if (findID(0,new_id)!=NULL){
		printf("ERROR: ID NOT UNIQUE\n");
	} else {
		node* link = (node*)malloc(sizeof(struct node));
		link->id = new_id;
		link->first_name = new_first_name;
		link->last_name = new_last_name;
		link->gpa = new_gpa;
		link->major = new_major;
		node* previous=NULL;
		node* current = head;
		for (int i = 0; i < length(); i++){
			if (current->id > link->id){
				if (i == 0){
					link->next = head;
					head = link;
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
		if (head==NULL){
			head = link;
			head->next = NULL;
			head->index = 0;
		}
		else if (current==NULL){
			previous->next = link;
			link->next = NULL;
			link->index = length();
		}
	}	
}

/*
 *	delete node that matches ID
 *	if deleting node that doesn't exist aka equals NULL or
 *	no ID match,
 *	then print error "STUDENT RECORD CANNOT BE DELETED NOR UPDATED" 
 */

node* deleteNode(int id_to_delete) {
	if (length()==0){
		printf("ERROR: STUDENT RECORD CANNOT BE DELETED NOR UPDATED");
		return NULL;
	}
	if (head->id == id_to_delete){
		node* temp = head;
		head = (node*)(head->next);
		return head;
	}
	node* previous=NULL;
	node* current;
	for (current=head;current!=NULL;current=(node*)(current->next)){
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

int main(int argc, const char* argv[]){
	insertNode(1,"Shawn","Li",3.7,"CSE");
	printList(1,1,"Li","CSE");
	insertNode(2,"Eli","Zhu",3.7,"EEC");	
	printList(1,1,"Li","CSE");
	insertNode(3,"Bhawanjot","Shergill",3.2,"EEC");	
	printList(1,1,"Li","CSE");
	insertNode(4,"Tanjeel","Murad",3.5,"BUS");
	printList(1,1,"Li","CSE");
	insertNode(6,"Justin","Han",3.4,"UDC");
	printList(1,1,"Li","CSE");
	insertNode(5,"Prabjhot","Shergill",3.6,"CSE");
	printList(1,1,"Li","CSE");
	printList(5,3,"Shergill","BUS");
}
