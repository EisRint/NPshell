#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>


int main(void) {

	char *env;
	env = getcwd(NULL, 0);
	env = realloc(env, strlen(env) * 2 + 7);
	sprintf(env + strlen(env) + 1, "/bin:%s", env);
	memmove(env + strlen(env), env + strlen(env) + 1, strlen(env) + 6);


	char *lang;
	lang = malloc(12);
	strcpy(lang,"en_US.UTF-8\0");

	//-----------------------------------------------------------
	while(1){
		int i=0;
		int k=0;
		int flag=0;

		char input[512];

		char Q[7500][512];

		printf("%% ");
		while(flag==0){
			if (feof(stdin)){
				printf("\n");
				exit(0);
			}
			else{
				input[i]=fgetc(stdin);
			}

			if (input[i]==' ' && i!=0 && input[i-1]!=' '){
				i++;
			}
			else if (input[i]=='\n'){
				input[i] = '\0';
				flag=1;
				strcpy(Q[k],input);
				k++;
			}
			else if (input[i]=='|'){
				input[i] = '\0';
				strcpy(Q[k],input);
				k++;
				i=0;
			}
			else if (input[i]!=' '){
				i++;
			}

		}

		//-----------------------------------------------------------

		if(strcmp(Q[0],"exit")==0){
			exit(0);
		}
		
		if(Q[0][0]=='p' && Q[0][1]=='r' && Q[0][2]=='i' && Q[0][3]=='n' && Q[0][4]=='t' && Q[0][5]=='e' && Q[0][6]=='n' && Q[0][7]=='v'){
			if(Q[0][9]=='P' && Q[0][10]=='A' && Q[0][11]=='T' && Q[0][12]=='H'){
				printf("%s\n",env);	
				continue;
			}
			if(Q[0][9]=='L' && Q[0][10]=='A' && Q[0][11]=='N' && Q[0][12]=='G'){
				printf("%s\n",lang);	
				continue;
			}
			else{
				continue;
			}
			
		}

		if(Q[0][0]=='s' && Q[0][1]=='e' && Q[0][2]=='t' && Q[0][3]=='e' && Q[0][4]=='n' && Q[0][5]=='v'){
			if(Q[0][7]=='P' && Q[0][8]=='A' && Q[0][9]=='T' && Q[0][10]=='H'){
				env = realloc(env, strlen(&Q[0][12]));
				strcpy(env, &Q[0][12]);
				continue;
			}
			if(Q[0][7]=='L' && Q[0][8]=='A' && Q[0][9]=='N' && Q[0][10]=='G'){
				lang = realloc(lang, strlen(&Q[0][12]));
				strcpy(lang, &Q[0][12]);
				continue;
			}
			else{
				continue;
			}
			
		}

		int is_empty=0;
		int l=0;
		int pipefd0[2];
		int pipefd1[2];

		if(pipe(pipefd0)<0)
			printf("pipe1 create error");
		while(is_empty==0){		
			int len;
			char buffer[1024]={0};

			if(pipe(pipefd1)<0)
				printf("pipe1 create error");
			signal(SIGCHLD,SIG_IGN);
			if(fork() == 0){ /*child process*/

				dup2(pipefd0[0], STDIN_FILENO);
				close(pipefd1[0]);
				dup2(pipefd1[1], STDOUT_FILENO); /*pipefd0 will close after STDIN receive EOF*/

				char *argv[50];
				int argvi = 0;
				int it = 0;
				_Bool f = 1;
				while(Q[l][it] != '\0') {
					if(Q[l][it] != ' ') {
						if (f){
							argv[argvi] = &Q[l][it];
							++argvi;
							++it;
							f = 0;
						} else {
							++it;
						}
					} else {
						Q[l][it] = '\0';
						++it;
						f = 1;
					}
				}
				argv[argvi] = NULL;

				char  pathenv[strlen(env) + sizeof("PATH=")];
				sprintf(pathenv, "PATH=%s", env);
				char *envp[] = {pathenv, NULL};
//				puts("argv:");
//				for(int fori = 0; argv[fori] != NULL; ++fori) {
//				    printf("%s, ", argv[fori]);
//				}
//				puts("");
//				puts("envp:");
//                                for(int fori = 0; envp[fori] != NULL; ++fori) {
//				    printf("%s, ", envp[fori]);
//				}
//				puts("");
				setenv("PATH",env,1);

				printf("%d\n",execvp(argv[0],argv));
				int errsv = errno;
				printf("errno = %d\n",errsv);


				exit(0);
			}else{ /*parent process*/
				close(pipefd1[1]);
				close(pipefd0[0]);
				pipefd0[0]=pipefd1[0];


			}


			l++;
			if(l==k){
				is_empty=1;
				while((len=read(pipefd1[0],buffer,1023))>0){
					buffer[len]='\0';
					printf("%s",buffer);
				}
			}


		}
	}




	return 0;
}

