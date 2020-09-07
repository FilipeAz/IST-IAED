#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Hashtag.h"
#include "AVLTree.h"
#define NUMSEP 11
#define MAX_LINE_LENGTH 143

static const char separators[] = {' ','\t',',',';','.','?','!','"','\n',':','\0'};

/*funcao split separa todas as palavras recebidas do stdin e processa-as se comecarem por '#'*/
void split(char *line){
	char buffer_aux[MAX_LINE_LENGTH];
	int i, k;
	for(i = 0, k = 0; line[i] != '\0'; i++, k++) {
		buffer_aux[k] = tolower(line[i]);
	}
	buffer_aux[k] = '\0';
	char *token = strtok(buffer_aux, separators);
	Hashtag hashtag;
	while(token!=NULL){
		if(line[0] == 'a'){/*comando a insere um hashtag na arvore*/
			if(token[0] == '#' && strlen(token) > 1){
				hashtag = cria_hashtag(token);
				insertTREE(hashtag);
			}
		}
		else if(line[0] == 's'){/*comando s devolve o numeor total de hashtags e o numero de ocorrencias total de hashtags*/
			printf("%d %d\n",countTREE(),totOcorrenciasTREE());
		}
		
		else if(line[0] == 'm'){/*comando s imprime o nome e o numero de ocorrencias da hashtag com maior ocorrencias*/
			returnmaxHashtag();
		}
		
		else if(line[0] == 'l'){/*comando l imprime todas as hashtags de acordo com o numero de ocorrencias e por ordem alfabetica*/
			if(searchMAX() != NULL){
				int max = returnmaxHashtagCounter(), i, total = countTREE();
				for(i = 0;i < total;){
					i += returnHashtagsTREE(max);
					max--;
				}
			}
		}
		
		token = strtok(NULL, separators);
	}
} 

int main(){
	char message[MAX_LINE_LENGTH];
	init();
	fgets(message, MAX_LINE_LENGTH, stdin); 
	while( message[0] != 'x'){
		split(message);
		fgets(message, MAX_LINE_LENGTH, stdin);
	}
	freeArvore();
	return 0;
}






