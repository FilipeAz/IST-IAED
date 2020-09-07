#include <stdio.h>
#include <stdlib.h>
#include "Cliente.h"
#include "Global.h"
#include "Tree.h"

linkTREE NEWT(Cliente cliente, linkTREE l, linkTREE r) {
    linkTREE x = (linkTREE) malloc(sizeof(struct nodeTREE));
    x->cliente = cliente;
    x->l = l;
    x->r = r;
    return x;
}

linkTREE search(linkTREE h, long int ref) {
    if (h == NULL)
        return NULL;
    if (ref == h->cliente.referencia)
        return h;
    if (ref < h->cliente.referencia)
        return search(h->l, ref);
    else
        return search(h->r, ref);
}

linkTREE insert(linkTREE h, Cliente cliente) {
    long int ref = cliente.referencia;
    if (headT==NULL){
        headT=NEWT(cliente, NULL, NULL);
        return headT;}
    if (h == NULL)
        return NEWT(cliente, NULL, NULL);
    if (ref < h->cliente.referencia)
        h->l = insert(h->l, cliente);
    else
        h->r = insert(h->r, cliente);
    return h;
} 
 

void visit(Cliente cliente){
    if (cliente_vazio(cliente)==0)
	   printf("*%ld %ld %ld %ld %ld\n",cliente.referencia,cliente.n_cheques_emitidos_emi,
		      cliente.valor_cheques_emitidos_emi,cliente.n_cheques_emitidos_ben,
		      cliente.valor_cheques_emitidos_ben);
}

void transverse(linkTREE h){
    if (h == NULL)
        return;
    transverse(h->l);
    visit(h->cliente);
    transverse(h->r);
}

void apaga_tree(linkTREE h){
    if (h == NULL)
        return;
    apaga_tree(h->l);
    apaga_tree(h->r);
    free(h);
}
