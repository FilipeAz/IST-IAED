#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLTree.h"
#define MAX_HASHTAG_LENGTH 141


/*Variaveis estaticas globais que correspondem a cabeca da arvore, um ponteiro para o hashtag com mais ocorrencias, o numero total de hashtags e o numero total de ocorrencias de hashtags.*/
static linkTREE head;
static Hashtag *maxHashtag;
static int numHashtags;
static int totOcorrencias;

/*init inicializa as variaveis globais*/
void init(){
	head = NULL;
	maxHashtag = NULL;
	numHashtags = 0;
	totOcorrencias = 0;
}

/*NEWT aloca memoria para um no da arvore com os parametros recebidos e retorna um ponteiro para esse no*/
linkTREE NEWT(Hashtag hashtag, linkTREE l, linkTREE r){
	linkTREE x = (linkTREE) malloc(sizeof(struct nodeTREE));
    x->hashtag = hashtag;
    x->l = l;
    x->r = r;
	x->height=1; 
    return x;
}

/*upMax atualiza o maxHashtag de acordo com as hashtags inseridas na arvore*/
void upMax(linkTREE n){
	char buffer[MAX_HASHTAG_LENGTH], buffer_aux[MAX_HASHTAG_LENGTH];
	getHashtagName(n->hashtag,buffer);
	if(maxHashtag == NULL){
		maxHashtag = &n->hashtag;
		return;
	}
	if(getHashtagCounter(n->hashtag) > getHashtagCounter(*maxHashtag)){
		maxHashtag = &n->hashtag;
	}
	else if(getHashtagCounter(n->hashtag) == getHashtagCounter(*maxHashtag)){
		getHashtagName(*maxHashtag,buffer_aux);
		if(strcmp(buffer,buffer_aux) < 0){
			maxHashtag = &n->hashtag;
		}
	}
}

/*insert insere hashtags numa sub-arvore por ordem alfabetica*/
linkTREE insert(linkTREE h, Hashtag hashtag) {
	char buffer[MAX_HASHTAG_LENGTH], buffer_aux[MAX_HASHTAG_LENGTH];
	getHashtagName(hashtag,buffer);
	if (h == NULL){
		linkTREE new = NEWT(hashtag, NULL, NULL);
		upMax(new);
		numHashtags++;
		totOcorrencias++;
		return new;
	}
	getHashtagName(h->hashtag,buffer_aux);
	if (strcmp(buffer,buffer_aux) == 0){
		upHashtagCounter(&h->hashtag);
		totOcorrencias++;
		upMax(h);
		return h;
	}
	if (strcmp(buffer,buffer_aux) < 0)
		h->l = insert(h->l, hashtag);
	else
		h->r = insert(h->r, hashtag);
	h = AVLbalance(h); 
	return h;
}

/*returnHashtags imprime as hashtags que tem o numero de ocorrencias igual ao contador por ordem alfabetica*/
int returnHashtags(linkTREE h, int contador){
	int v = 0, tot = 0;
	char buffer[MAX_HASHTAG_LENGTH];
	if (h == NULL)
		return 0;
	else{
		getHashtagName(h->hashtag,buffer);
	}
	tot += returnHashtags(h->l,contador);
	if(getHashtagCounter(h->hashtag) == contador){
		printf("%s %d\n",buffer, contador);
		v = 1;
	}
	tot += returnHashtags(h->r,contador); 
	if(v == 1){
		return tot + 1;
	}
	return tot;
}

/*height calcula a altura de um no da arvore*/
int height(linkTREE h){
	if (h == NULL) 
		return 0;
	return h->height;
} 

/*rotL faz uma rotacao a esquerda*/
linkTREE rotL(linkTREE h){
	int height_left, height_right;
	linkTREE x = h->r;
	h->r = x->l;
	x->l = h;
	height_left = height(h->l);
	height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 : height_right + 1;
	height_left = height(x->l);
	height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 : height_right + 1;
	return x;
} 

/*rotL faz uma rotacao a direita*/
linkTREE rotR(linkTREE h){
	int height_left, height_right;
	linkTREE x = h->l;
	h->l = x->r;
	x->r = h;
	height_left = height(h->l);
	height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 : height_right + 1;
	height_left = height(x->l);
	height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 : height_right + 1;
	return x; 
}

/*rotL faz uma rotacao dupla, primeiro a esquerda e depois a direita*/
linkTREE rotLR(linkTREE h){
	if (h==NULL)
		return h;
	h->l = rotL(h->l);
	return rotR(h);
} 

/*rotL faz uma rotacao dupla, primeiro a direita e depois a esquerda*/
linkTREE rotRL(linkTREE h){
	if (h==NULL)
		return h;
	h->r = rotR(h->r);
	return rotL(h);
}

/*Balance calcula o balance factor que vai ser utilizado no balanceamento da arvore*/
int Balance(linkTREE h) {
	if(h == NULL) 
		return 0;
	return height(h->l) - height(h->r);
} 

/*AVLbalance efetua o balanceamento da arvore*/
linkTREE AVLbalance(linkTREE h) {
	int balanceFactor;
	if (h==NULL) 
		return h;
	balanceFactor= Balance(h);
	if(balanceFactor>1) {
		if (Balance(h->l)>0){
			h=rotR(h);
		}
		else{
			h=rotLR(h);
		}
	}
	else if(balanceFactor<-1){
		if (Balance(h->r)<0){
			h = rotL(h);
		}
		else{
			h = rotRL(h);
		}
	}
	else{
		int height_left = height(h->l);
		int height_right = height(h->r);
		h->height = height_left > height_right ? height_left + 1 : height_right + 1;
	}
	return h;
} 

/*freeTREE faz free de todos os nos de uma sub-arvore*/
void freeTREE(linkTREE h){
	if (h == NULL)
        return;
    freeTREE(h->l);
    freeTREE(h->r);
    free(h);
}

/*freeArvore faz free de todos os nos da arvore*/
void freeArvore(){
	freeTREE(head);
}

/*searchMAX retorna a hashtag com maior número de ocorrencias e com menor ordem alfabetica*/
Hashtag* searchMAX(){
	return maxHashtag;
}

/*insertTREE insere uma hashtag na arvore AVL*/
void insertTREE(Hashtag hashtag){
	head = insert(head,hashtag);
}

/*countTREE retorna o numero total de hashtags*/
int countTREE(){
	return numHashtags;
}

/*totOcorrenciasTREE retorna o numero total de ocorrencias*/
int totOcorrenciasTREE(){
	return totOcorrencias;
}

/*returnHashtagsTREE imprime todas as hashtags da arvore por ordem de ocorrencias e por ordem alfabetica*/
int returnHashtagsTREE(int contador){
	return returnHashtags(head,contador);
}

/*returnmaxHashtagCounter devolve o numero de ocorrencias da hashtag com maior ocorrencias*/
int returnmaxHashtagCounter(){
	return getHashtagCounter(*maxHashtag);
}

/*returnmaxHashtag imprime o nome e o numero de ocorrencias da hashtag com maior ocorrencias*/
void returnmaxHashtag(){
	char buffer[MAX_HASHTAG_LENGTH];
	if(maxHashtag == NULL){
		return;
	}
	getHashtagName(*maxHashtag,buffer);
	printf("%s %d\n",buffer,getHashtagCounter(*maxHashtag));
}











