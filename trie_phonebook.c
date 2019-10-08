#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>  
#define size 26 
  
// Converts character into corresponding index  
int charToIndex(char c){
	return ((int)c-(int)'a');
}
  
// trie node 
typedef struct node { 
    struct node *children[size]; 
    int isEndOfWord;
	char number[10]; 
}node; 
  
// Returns new trie node 
node *getNode() { 
	int i;
    node *newrec; 
  	newrec = (node *)malloc(sizeof(node)); 
    newrec->isEndOfWord = 0; 
  	for (i = 0; i < size; i++) 
    	newrec->children[i] = NULL; 
  	return newrec; 
} 
  
// If not present, inserts key into trie  
void insert(node *root, char *a, char *num) { 
    int level; 
    int length = strlen(a); 
    int index; 
	node *p= root; 
	for (level = 0; level < length; level++){ 
        index = charToIndex(a[level]); 
        if (p->children[index]==NULL) 
            p->children[index] = getNode(); 
  		p = p->children[index]; 
    } 
  	// mark last node as leaf and copy mobile number into it
    p->isEndOfWord = 1; 
    strcpy(p->number,num);
} 
  
// Returns 1 and gives the number if term presents in trie, otherwise 0 
int search(node *root, char *a, char *result) { 
    int level; 
    int length = strlen(a); 
    int index; 
    node *p = root; 
  
    for (level = 0; level < length; level++) { 
        index = charToIndex(a[level]); 
  		if (p->children[index]==NULL) 
            return 0; 
		p = p->children[index]; 
    } 
	if(p==NULL || p->isEndOfWord==0)
		return 0;
	else{
		strcpy(result,p->number);
		return 1;
	}	
} 
  
int main() 
{ 
	FILE *fp;
	int ch,t;
	char name[50],number[10];
	node *root = getNode();
	fp = fopen("phonebook.txt","a+");
	while(feof(fp)==0){
		fscanf(fp,"%s",name);
		fscanf(fp,"%s",number);
		insert(root,name,number);
	}
	while(1){
		printf("\nWelcome to trie phonebook!");
		printf("\n1:Enter new contact");
		printf("\n2:Search contact");
		printf("\n3:Display phonebook");
		printf("\n4:Exit");
		printf("\nEnter Choice: ");
		scanf("%d",&ch);
		if(ch==4)
			break;
		switch(ch){
			case 1:
				printf("Enter Name to insert(lowercase only):");
				scanf("%s",name);
				printf("Enter Number(10 digit): ");
				scanf("%s",number);
				if(search(root,name,number)==1){
					printf("\n%s already exists!\n",name);
					break;
				}
				insert(root,name,number);
				fprintf(fp,"\n%s %s",name,number);
				printf("\n%s - %s Added to phonebook\n",name,number);
				break;
			case 2:
				printf("Enter Name to search (lowercase only): ");
				scanf("%s",name);
				t=search(root,name,number);
				if(t==0)
					printf("\n%s Not Found!\n",name);
				else
					printf("\n%s - %s\n",name,number);
				break;
			case 3:
				rewind(fp);
				while(feof(fp)==0){
					fscanf(fp,"%s",name);
					fscanf(fp,"%s",number);
					printf("\n%s - %s",name,number);
				}
				printf("\n");
				break;
			default:
				printf("\nInvalid Choice!\n");
		}
	}
	fclose(fp);
    return 0; 
} 
