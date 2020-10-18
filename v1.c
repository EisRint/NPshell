#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	char data[512];
	struct node *next;
};

typedef struct node Node;

void createq();
void showfront();
void addq(char *);
void delq();
void showqueue();

Node *front, *rear;

int main(void) {
	int select;
	char input[512];

	createq();


	//-----------------------------------------------------------
	while(1){
		int i=0;
		int k=0;
		int flag=0;
		char data[512];
		while(flag==0){
			data[i]=fgetc(stdin);
			if (data[i]==' '){
				//printf("%c is space\n",data[i]);
				input[i] = '\0';
				i=0;
				addq(input);
			}
			else if (data[i]=='\n'){
				//printf("endl\n");
				input[i] = '\0';
				flag=1;
				addq(input);
			}
			else{
				//printf("%c is char\n",data[i]);
				input[i]=data[i];
				i++;
			}
		}

		showqueue();

		//-----------------------------------------------------------

	}

	return 0;
}

void createq() {
	front = rear = (Node*) malloc(sizeof(Node));
	front->next = rear->next = NULL;
}

void showfront(){
	if(front->next == NULL)
		printf("\n佇列為空！");
	else
		printf("\n頂端值：%s", front->next->data);
}

void addq(char *data) {
	Node *newnode;

	newnode = (Node*) malloc(sizeof(Node));

	if(front->next == NULL)
		front->next = newnode;

	strcpy(newnode->data,data);
	newnode->next = NULL;
	rear->next = newnode;
	rear = newnode;
}

void delq() {
	Node* tmpnode;

	if(front->next == NULL) {
		printf("\n佇列已空！");
		return;
	}

	tmpnode = front->next;
	front->next = tmpnode->next;
	free(tmpnode);
}

void showqueue() {
	Node* tmpnode;

	tmpnode = front->next;

	printf("\n佇列內容：\n");
	while(tmpnode != NULL) {
		printf("%s\n", tmpnode->data);
		tmpnode = tmpnode->next;
	}
}

