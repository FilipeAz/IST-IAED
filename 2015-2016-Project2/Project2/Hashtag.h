#ifndef _HASHTAG_
#define _HASHTAG_
#define MAX_HASHTAG_LENGTH 141

/*Estrutura Hashtag que contem o nome e o numero de ocorrencias do hashtag*/
typedef struct hashtags{
    char name[MAX_HASHTAG_LENGTH];
	int counter;
}Hashtag;

/*Declaracao de de funcoes do ficheiro c*/
Hashtag cria_hashtag(char name[]);

void getHashtagName(Hashtag h, char* buffer);

int getHashtagCounter(Hashtag h);

void upHashtagCounter(Hashtag* h);

#endif