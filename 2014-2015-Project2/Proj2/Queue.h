#ifndef _QUEUE_
#define _QUEUE_

#include "Cheque.h"

/*linkQUEUE: E um ponteiro para uma struct QUEUEnode*/
typedef struct QUEUEnode* linkQUEUE;

/*Struct QUEUEnode: Esta struct guarda uma struct cheque do tipo Cheque e um ponteiro para outra struct QUEUEnode. */
struct QUEUEnode {
    Cheque cheque;
    linkQUEUE next;
};

/*Funcao QUEUEempty: Nao Recebe nada. Verifica apenas se a arvore binaria esta vazia, ao verificar se headQ esta vazia.*/ 
int QUEUEempty();

/*Funcao NEWQ: Recebe uma struct Cheque (cheque) e um ponteiro para outro QUEUEnode (next). Vai alocar memoria para uma struct QUEUEnode, 
			   e guarda nessa struct o cheque e o next. Devolve um ponteiro para a struct QUEUEnode criada.*/ 
linkQUEUE NEWQ(Cheque cheque, linkQUEUE next);

/*Funcao QUEUEput: Recebe uma struct Cheque (cheque). Vai criar um QUEUEnode com a struct Cheque. Caso a headQ estava vazia, a headQ passa 
			   a ser igual ao QUEUEnode criado. Caso contrario E colocado no fim da QUEUE.*/ 
void QUEUEput(Cheque cheque);

/*Funcao QUEUEget: Processa o primeiro cheque da QUEUE, ou seja eetira o primeiro elemento da QUEUEnode (headQ) e devolve o cheque da QUEUEnode.*/ 
Cheque QUEUEget();

/*Funcao QUEUE_processa_ref: Processa o cheque de referencia (ref) da QUEUE, ou seja vai procurar a struct,QUEUEnode, com o cheque de 
							 referencia igual a ref. E vai remove-lo e devolver o cheque da QUEUEnode.*/
Cheque QUEUE_processa_ref(long int ref);

/*Funcao total_cheques: Esta funcao apaga toda a informacao da QUEUE, ou seja apaga todos os QUEUEnode. */
void clean_QUEUE();

#endif