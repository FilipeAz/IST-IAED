#include "Hashtag.h"
#include <string.h>
#include <stdio.h>

/*cria_hashtag e o construtor de Hashtags*/
Hashtag cria_hashtag(char name[]){
	Hashtag h;
	strcpy(h.name,name);
	h.counter = 1;
	return h;
}

/*getHashtagName copia o nome da Hashtag para um buffer*/
void getHashtagName(Hashtag h, char* buffer){
	sprintf(buffer,"%s",h.name);
}


/*getHashtagCounter devolve o numero ocorrencias da hashtag*/
int getHashtagCounter(Hashtag h){
	return h.counter;
}

/*upHashtagCounter aumenta o numero de ocorrencias*/
void upHashtagCounter(Hashtag* h){
	h->counter++;
}