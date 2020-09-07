/* Filipe Azevedo n82468;
   Bruno Lopes n82457;
   Pedro Santos n82507.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Global.h"
#include "Cheque.h"
#include "Cliente.h"
#include "Tree.h"
#include "Queue.h"
#define MAX_COMANDO_LENGTH 20

typedef struct info{            /*estrutura que guarda o numero de clientes ativos, o numero de cheques por processar e o valor total de todos os cheques por processar*/
    int n_clientes,n_cheques;    
    long int valor_cheques;
}Info;

Info i;                            /*inicializacao das variaveis globais*/
linkQUEUE headQ=NULL,tailQ=NULL;
linkTREE headT=NULL;

/*Funcao main: Funcao principal que chama todas as outras funcoes.
               Inicialmente, esta aguarda que o utilizador insira um comando especifico e a partir dai desencadeia uma determinada acao.
               Caso o comando seja invalido, imprime uma mensagem e aguarda por outro comando.
               Comando "cheque": Recebe um valor, que E um inteiro positivo correspondente ao valor do cheque, e refe, refb, e refc correspondem
                                respectivamente as referencias do cliente emissor, cliente beneficiario, e cheque.
                                E Adiciona um novo cheque à pool de cheques a processar. Pode assumir que nunca serão criados.
               Comando "processa": Processa o cheque emitido mais antigo, e remove o cheque da pool de cheques a processar. Nao imprime qualquer 
                                   output excepto se a pool de cheques for vazia. 
               Comando "processaR":Processa o cheque com a referencia refc, e remove o cheque da pool de cheques a processar.
                                   Nao imprime qualquer output excepto se nao existir nenhum cheque com a referida referencia.
               Comando "infocheque": Recebe a referencia de um cheque. E vai Imprimir a informacao referente ao cheque com a referencia ref.
               Comando "infocliente":Recebe a referencia de um cheque. Imprime a informacao referente ao cliente com a referencia ref. V
               Comando "info": Imprime a informacao sobre todos os clientes activos do sistema.
               Comando "sair": Sai do programa e apaga toda a informacao sobre o sistema. Imprime o numero de clientes activos do sistema, 
                               e o numero e o valor total de cheques por processar. */

int main(){
	char comando[MAX_COMANDO_LENGTH];                                 /*declaracao das variaveis globais ao main*/
    long int referencia,valor,refe,refb,refc;
    Cheque cheque;
    Cliente cliente,cliente_emi,cliente_ben;
    Cliente *pcliente_emi /*ponteiro para o cliente emissor*/,*pcliente_ben /*ponteiro para o cliente beneficiario*/;
    linkTREE pnode_emi /*ponteiro para o no onde esta o cliente emissor*/,pnode_ben /*ponteiro para o no onde esta o cliente beneficiario*/;
    i.n_clientes=0;
    i.n_cheques=0;
    i.valor_cheques=0;
    while(1){
        scanf("%s",comando);
        getchar();
        if (strcmp("cheque",comando)==0){
            scanf("%ld %ld %ld %ld",&valor,&refe,&refb,&refc);
            cheque=cria_cheque(valor,refe,refb,refc);
            QUEUEput(cheque);                                          /*coloca-se o cheque na Pool*/
            i.valor_cheques+=valor;
            i.n_cheques++;                                              /*atualiza-se a struct info*/
            pnode_emi=search(headT,refe);
            if (pnode_emi==NULL){
            	cliente_emi=cria_cliente(refe);
                pnode_emi=insert(headT,cliente_emi);
                i.n_clientes++;}
            pcliente_emi=&(pnode_emi->cliente);
            aumenta_cheques_emitidos(pcliente_emi,valor);              /*atualiza-se o cliente emissor*/
            pnode_ben=search(headT,refb);
            if (pnode_ben==NULL){
            	cliente_ben=cria_cliente(refb);
            	insert(headT,cliente_ben);
                i.n_clientes++;}
            pcliente_ben=&(search(headT,refb)->cliente);
            aumenta_cheques_ben(pcliente_ben,valor);}                   /*atualiza-se o cliente beneficiario*/

        else if (strcmp("processa",comando)==0){
            if (QUEUEempty()==0){                                       /*verifica-se se a Pool nao esta vazio*/
                cheque = QUEUEget();                                    /*retira-se o cheque colocado ha mais tempo*/
                i.n_cheques--;
                i.valor_cheques-=cheque.valor;                          /*atualiza-se a struct info*/
                pnode_emi=search(headT,cheque.emissor);
                pcliente_emi=&(pnode_emi->cliente);
                diminui_cheques_emitidos(pcliente_emi,cheque.valor);     /*atualiza-se o cliente emissor*/
                pnode_ben=search(headT,cheque.beneficiario);
                pcliente_ben=&(pnode_ben->cliente);
                diminui_cheques_ben(pcliente_ben,cheque.valor);          /*atualiza-se o cliente beneficiario*/
                cliente_emi=pnode_emi->cliente;
                cliente_ben=pnode_ben->cliente;
                if (cliente_vazio(cliente_emi)!=0)
                    i.n_clientes--;                                                       
                if (cliente_vazio(cliente_ben)!=0)
                    i.n_clientes--; }                                    /*se os clientes nao se encontrarem ativos atualiza-se o numero de clientes*/
            else{
                printf("Nothing to process\n");
            }
        }

        else if (strcmp("processaR",comando)==0){
            scanf("%ld",&referencia);
            cheque = QUEUE_processa_ref(referencia);
            if (cheque.valor!=0){                                               /*Se o cheque nao tiver valor=0 (ou seja, nao e vazio)*/
                i.n_cheques--;
                i.valor_cheques-=cheque.valor;                                  /*atualiza-se a struct info*/
                pnode_emi=search(headT,cheque.emissor);
                diminui_cheques_emitidos(&(pnode_emi->cliente),cheque.valor);   /*atualiza-se o cliente emissor*/
                pnode_ben=search(headT,cheque.beneficiario);
                diminui_cheques_ben(&(pnode_ben->cliente),cheque.valor);        /*atualiza-se o cliente beneficiario*/
                cliente_emi=pnode_emi->cliente;
                cliente_ben=pnode_ben->cliente;
                if (cliente_vazio(cliente_emi)!=0)
                    i.n_clientes--;
                if (cliente_vazio(cliente_ben)!=0)
                    i.n_clientes--;                                             /*se os clientes nao se encontrarem ativos atualiza-se o numero de clientes*/
            }
            else{
                printf("Cheque %ld does not exist\n",referencia);
            }   
        }

        else if (strcmp("infocheque",comando)==0){
            linkQUEUE h=headQ;
            scanf("%ld",&referencia);
            while (h->cheque.referencia!=referencia)
                h=h->next;
            printf("Cheque-info: %ld %ld %ld --> %ld\n",h->cheque.referencia,h->cheque.valor,        /*da informacao sobre o cheque com a referencia dada no input*/
                   h->cheque.emissor,h->cheque.beneficiario);
        }

        else if (strcmp("infocliente",comando)==0){
            scanf("%ld",&referencia);
            cliente = search(headT,referencia)->cliente;
            printf("Cliente-info: %ld %ld %ld %ld %ld\n",cliente.referencia,cliente.n_cheques_emitidos_emi,   /*da informacao sobre o cliente com a referencia dada no input*/
                   cliente.valor_cheques_emitidos_emi,cliente.n_cheques_emitidos_ben,
                   cliente.valor_cheques_emitidos_ben);
        }

        else if (strcmp("info",comando)==0){
            transverse(headT);                      /*da informacao sobre todos os clientes ativos no sistema*/
        }

        else if (strcmp("sair",comando)==0){
            printf("%d %d %ld\n",i.n_clientes,i.n_cheques,i.valor_cheques);    /*retorna a estrutura info*/
            apaga_tree(headT);
            clean_QUEUE();                                                     /*apaga as estruturas de dados dos cheques e dos clientes, FIFO e arvore binaria de pesquisa respetivamente*/
            return EXIT_SUCCESS;
        }
        else{
            printf("Comando invalido, introduza outro comando\n");
        }
        }}