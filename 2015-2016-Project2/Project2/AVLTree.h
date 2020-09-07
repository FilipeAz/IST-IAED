#ifndef _AVLTREE_
#define _AVLTREE_

#include "Hashtag.h"
#define MAX_HASHTAG_LENGTH 141

/*linkTREE é um ponteiro para um no da arvore AVL*/
typedef struct nodeTREE* linkTREE;

/*struct nodeTREE e um no da arvore que contem uma hashtag, a altura do no da arvore e ponteiros para o filho esquerdo e para o filho direito*/
struct nodeTREE{ 
    Hashtag hashtag; 
	int height;
    linkTREE l, r;
};

/*Declaracao de de funcoes do ficheiro c*/
void init();

linkTREE NEWT(Hashtag hashtag, linkTREE l, linkTREE r);

linkTREE searchMax(linkTREE h, int count);

void upMax(linkTREE n);

linkTREE insert(linkTREE h, Hashtag hashtag);

int returnHashtags(linkTREE h, int contador);

int height(linkTREE h);

linkTREE rotL(linkTREE h);

linkTREE rotR(linkTREE h);

linkTREE rotLR(linkTREE h);

linkTREE rotRL(linkTREE h);

int Balance(linkTREE h);

linkTREE AVLbalance(linkTREE h);

void freeTREE(linkTREE h);

void freeArvore();

linkTREE searchTREE();

Hashtag* searchMAX();

void insertTREE();

int countTREE();

int totOcorrenciasTREE();

int returnHashtagsTREE(int contador);

void returnmaxHashtag();

int returnmaxHashtagCounter();

#endif




