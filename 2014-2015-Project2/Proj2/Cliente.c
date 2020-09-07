#include "Cliente.h"
#include "Global.h"

Cliente cria_cliente(long int ref){
    Cliente x;
    x.referencia=ref;
    x.n_cheques_emitidos_emi=0;
    x.valor_cheques_emitidos_emi=0;
    x.n_cheques_emitidos_ben=0;
    x.valor_cheques_emitidos_ben=0;
    return x;
}

int cliente_vazio(Cliente cliente){
    return (cliente.n_cheques_emitidos_emi==0 && cliente.valor_cheques_emitidos_emi==0 &&
            cliente.n_cheques_emitidos_ben==0 && cliente.valor_cheques_emitidos_ben==0);}

void aumenta_cheques_emitidos(Cliente* pcliente, int valor){
    pcliente->valor_cheques_emitidos_emi+=valor;
    pcliente->n_cheques_emitidos_emi++;
}

void diminui_cheques_emitidos(Cliente* pcliente, int valor){
    pcliente->valor_cheques_emitidos_emi-=valor;
    pcliente->n_cheques_emitidos_emi--;
}

void aumenta_cheques_ben(Cliente* pcliente, int valor){
    pcliente->valor_cheques_emitidos_ben+=valor;
    pcliente->n_cheques_emitidos_ben++;
}

void diminui_cheques_ben(Cliente* pcliente, int valor){
    pcliente->valor_cheques_emitidos_ben-=valor;
    pcliente->n_cheques_emitidos_ben--;
}