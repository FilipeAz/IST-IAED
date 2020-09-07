#include <stdio.h>
#include <stdlib.h>
#include "Cheque.h"
#include "Global.h"
#include "Queue.h"

int QUEUEempty() {
    return headQ == NULL;
}

linkQUEUE NEWQ(Cheque cheque, linkQUEUE next) {
    linkQUEUE x = (linkQUEUE) malloc(sizeof(struct QUEUEnode));
    x->cheque = cheque;
    x->next = next;
    return x;
} 

void QUEUEput(Cheque cheque) {
    if (headQ == NULL) {
        headQ = (tailQ = NEWQ(cheque,headQ));
        return;
    }
    tailQ->next = NEWQ(cheque, tailQ->next);
    tailQ = tailQ->next;
}

Cheque QUEUEget() {
    Cheque cheque = headQ->cheque;
    linkQUEUE t = headQ->next;
    free(headQ);
    headQ = t;
    return cheque;
}

Cheque QUEUE_processa_ref(long int ref){ 
	linkQUEUE x=NULL; 
	linkQUEUE t=headQ; 
	Cheque cheque;
	while(t!=NULL && t->cheque.referencia!=ref){ 
		x=t; 
		t=t->next; } 
	if (t==NULL){ 
		return cria_cheque(0,0,0,0); } 
	if (x==NULL && t->next!=NULL){ 
		cheque=t->cheque;
		headQ=t->next;
		free(t); 
		return cheque;} 
	if (x==NULL && t->next==NULL){ 
		cheque=t->cheque;
		free(t); 
		headQ=NULL;
		tailQ=NULL;
		return cheque;}
	if (t->next==NULL){
		cheque=t->cheque;
		tailQ=x;
		tailQ->next=NULL;
		free(t);
		return cheque;
	}
	cheque=t->cheque; 
	t=x->next; 
	x->next=t->next; 
	free(t);
	return cheque; }

int total_cheques(){
	linkQUEUE h;
	int i=0;
	for(h=headQ;h!=NULL;h=h->next)
		i++;
	return i;
}

int total_valor_cheques(){
	linkQUEUE h;
	int i=0;
	for(h=headQ;h!=NULL;h=h->next)
		i+=h->cheque.valor;
	return i;
}

void clean_QUEUE(){
	linkQUEUE h=headQ,aux;
	while(h!=NULL){
		aux=h->next;
		free(h);
		h=aux;
	}
}
