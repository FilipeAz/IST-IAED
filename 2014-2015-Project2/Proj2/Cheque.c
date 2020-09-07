#include "Cheque.h"
#include "Global.h"

Cheque cria_cheque(long int valor,long int refe,long int refb,long int refc){
    Cheque x;
    x.referencia=refc;
    x.valor=valor;
    x.emissor=refe;
    x.beneficiario=refb;
    return x;
}
