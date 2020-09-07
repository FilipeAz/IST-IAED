#ifndef _TREE_
#define _TREE_

#include "Cliente.h"

/*linkQUEUE: E um ponteiro para uma struct nodeTREE*/
typedef struct nodeTREE* linkTREE;

/*Struct QUEUEnode: Esta struct guarda uma struct cliente do tipo Cliente e dois ponteiros (l,r) para outras struct nodeTREE. */
struct nodeTREE{ 
    Cliente cliente; 
    linkTREE l, r;
};

/*Funcao NEWT: Recebe uma struct Cliente (cliente) e dois ponteiros para outros nodeTREE (l,r). Vai alocar memoria para uma struct nodeTREE, 
			   e guarda nessa struct o cliente, o l e o r. Devolve um ponteiro para a struct nodeTREE criada.*/
linkTREE NEWT(Cliente cliente, linkTREE l, linkTREE r);

/*Funcao search: Recebe um ponteiro h para um nodeTREE e a referencia de um cliente. Esta vai verificar se existe algum cliente com essa 
				referencia na arvore binaria e caso exista devolve um ponteiro para o nodeTREE em que ele esta contido.*/
linkTREE search(linkTREE h, long int ref);

/*Funcao insert: Recebe um ponteiro para um nodeTREE, headT, e uma struct Cliente (cliente).
				 Vai criar um QUEUEnode com a struct Cheque (ao chamar o NEWT). Caso a headQ estava vazia, a headQ passa 
			     a ser igual ao QUEUEnode criado. Caso contrario E colocado numa determinada posicao da arvore, dependendo da referencia.*/ 
linkTREE insert(linkTREE h, Cliente cliente);

/*Funcao visit: Recebe uma struct Clinete (cliente).
			    Vai imprimir todas as informacaos do cliente. */
void visit(Cliente cliente);

/*Funcao transverse: Recebe um ponteiro para um nodeTREE, headT.
	   				 Esta funcoa vai percorrer toda a arvore e imprime a informacao sobre todos os clientes activos do sistema(atraves da funcao visit). */ 
void transverse(linkTREE h);

/*Funcao total_cheques: Recebe uma struct Clinete (cliente). E apaga toda a informacao da arvore, ou seja apaga todos os nodeTREE. */
void apaga_tree(linkTREE h);

#endif