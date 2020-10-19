#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

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

	//	char PATH[][];

	createq();

	//-----------------------------------------------------------
	while(1){
		int i=0;
		int flag=0;

		char input[512];

		int pipefd0[2];

		printf("%% ");
		while(flag==0){
			input[i]=fgetc(stdin);


			if (input[i]==' ' && i!=0 && input[i-1]!=' '){
//				printf("%c is space\n",input[i]);
				i++;
			}
			else if (input[i]=='\n'){
//				printf("endl\n");
				input[i] = '\0';
				flag=1;
				addq(input);
			}
			else if (input[i]=='|'){
				input[i] = '\0';
				addq(input);
				i=0;
			}
			else if (input[i]!=' '){
				i++;
			}

		}

		//-----------------------------------------------------------
showqueue();

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

