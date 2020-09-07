#ifndef _CLIENTE_
#define _CLIENTE_

/*Struct clientes: Esta struct guarda as informacoes da entidade cliente, nomeadamente a referencia, o numero total de 
	cheques por processar emitidos pelo cliente , o valor total de cheques por processar emitidos pelo cliente, o numero total de 
	cheques por processar em que o cliente E beneficiario e o valor total de cheques por processar em que o cliente E beneficiario. */

typedef struct clientes{
    long int referencia;
    long int n_cheques_emitidos_emi;
    long int valor_cheques_emitidos_emi;
    long int n_cheques_emitidos_ben;
    long int valor_cheques_emitidos_ben;
}Cliente;

/*Funcao cria_cliente: Recebe a referencia (ref) do cliente. Cria a struct cliente apenas com a referencia e os restos dos campos a zero.
					   Vai devolver a struct clientes criada. */ 
Cliente cria_cliente(long int ref);

/*Funcao cliente_vazio: Recebe uma struct, Cliente. Vai verificar se a struct tem todos os campos a 0, 
				        ou seja se esta vazia, caso nao tenha devolve zero. */ 
int cliente_vazio(Cliente cliente);

/*Funcao aumenta_cheques_emitidos: Recebe um ponteiro para uma struct, pcliente, e o valor de um cheque.
								   Esta vai incrementar o numero total de cheques por processar em que o cliente E emitente, e adicionar o valor 
								   ao valor total de cheques por processar emitidos pelo cliente. */								    
void aumenta_cheques_emitidos(Cliente* pcliente, int valor);

/*Funcao diminui_cheques_emitidos: Recebe um ponteiro para uma struct, pcliente, e o valor de um cheque.
								   Esta vai decrementar o numero total de cheques por processar em que o cliente E emitente, e subtrair o valor 
								   ao valor total de cheques por processar emitidos pelo cliente. */
void diminui_cheques_emitidos(Cliente* pcliente, int valor);

/*Funcao aumenta_cheques_ben: Recebe um ponteiro para uma struct, pcliente, e o valor de um cheque.
								   Esta vai incrementar o numero total de cheques por processar em que o cliente E beneficiario, e adicionar o valor 
								   ao valor total de cheques por processar em que o cliente E beneficiario. */
void aumenta_cheques_ben(Cliente* pcliente, int valor);

/*Funcao diminui_cheques_ben: Recebe um ponteiro para uma struct, pcliente, e o valor de um cheque.
								   Esta vai decrementar o numero total de cheques por processar em que o cliente E beneficiario, e subtrair o valor 
								   ao valor total de cheques por processar em que o cliente E beneficiario. */
void diminui_cheques_ben(Cliente* pcliente, int valor);

#endif