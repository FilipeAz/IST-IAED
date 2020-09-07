#ifndef _CHEQUE_
#define _CHEQUE_

/*Struct cheques: Esta struct guarda as informacoes da entidade cheque, nomeadamente 
	a referencia, o valor, e as referencias do cliente emitente e do cliente beneficiario. */

typedef struct cheques{
    long int referencia;
    long int valor;
    long int emissor;
    long int beneficiario;
}Cheque;

/*Funcao cria_cheque: Esta funcao recebe as informacoes do cheque que queremos criar, nomeadamente
	a referencia, o valor, e as referencias do cliente emitente e do cliente beneficiario. 
	Esta vai criar e devolver uma struct cheques, Cheque. */ 
Cheque cria_cheque(long int valor,long int refe,long int refb,long int refc);

#endif