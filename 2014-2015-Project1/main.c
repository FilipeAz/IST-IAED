/*Bruno Lopes n82457,
  Filipe Azevedo n82468,
  Pedro Santos n */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXBANK 1000

/*Criacao de uma estrutura "Banco": guarda o nome, a classificacao e a referencia,
 e uma variavel c que representa o numero de bancos no sistema: */
typedef struct Bank{
    char nome[42];
    int classificacao;
    int ref;
}banco;
static int c=0;

/* comando a: adiciona ao vetor de structs "banco clientes" no indice c um novo
 banco caracterizado por um nome, classificacao e referencia*/
void add_banco(banco clientes[], char nome[], int classificacao, int ref1){

    strcpy(clientes[c].nome, nome);
    clientes[c].classificacao=classificacao;
    clientes[c].ref=ref1;
    c++;
}

/* comando k/r: Actualiza a classificacao do banco correspondente a clasificacao que entrou em input */
void class_banco(banco clientes[], int ref1, int classificacao){
    int i;
    for (i=0;i<c;i++)
        if (clientes[i].ref==ref1) {
            clientes[i].classificacao=classificacao;
            break;
        }
    }


/* comando e: adiciona na matriz(que representa as relacoes divida/emprestimo) 
um valor introduzido por input nas coordenadas dos indices dos bancos em questao,
que no fundo representa:"ref1" empresta "valor" a "ref2"*/
void add_emp (int matriz[MAXBANK][MAXBANK], banco clientes[], int ref1, int ref2, int valor){
    int o, e;
    for(o=0;clientes[o].ref!=ref1;o++)
	;
    for(e=0;clientes[e].ref!=ref2;e++)
	;
    matriz[o][e]+=valor;
}

/* comando p: reduz o valor que anteriormente estava definido na matriz de coordenadas
indice de matriz dos bancos chamados por input*/
void add_amorti (int matriz[MAXBANK][MAXBANK], banco clientes[], int ref1, int ref2, int valor){
    int o, e;
    for(o=0;clientes[o].ref!=ref2;o++)
	;
    for(e=0;clientes[e].ref!=ref1;e++)
	;
    matriz[o][e]-=valor;
}

/* comando l: comando que retorna uma listagem com diferentes informacoes sobre 
os bancos registados de acordo com o numero escrito pelo utilizador.*/
int list_bancos(int num, banco clientes[], int matriz[MAXBANK][MAXBANK]){
    int i, a, m, lin, col, inP=0, outP=0, outV=0, outVM=0, inV=0, inVM=0, vectoraux[MAXBANK], finalvec[MAXBANK], myCount = 0;
    for (i = 0; i < c; i++) {
        vectoraux[i] = 0;
        finalvec[i] = 0;
    }
    if (num==0){
/*O numero 0 faz com que o programa liste todos os bancos ordenados pela ordem 
de introducao no sistema na forma 'referencia nome classificacao'.*/
        for(a=0;a<c;a++)
            printf("%d %s %d\n",
            clientes[a].ref,clientes[a].nome,
            clientes[a].classificacao);}

    else if (num==1){
/*O numero 1 faz com que o programa liste todos os bancos ordenados pela ordem 
de introducao no sistema na forma 'referencia nome classificacao inP outP outV 
outVM inV inVM' em que:
inP e numero total de bancos parceiros a quem o banco tem uma divida; 
outP e numero total de bancos parceiros a quem o banco tem dinheiro emprestado;
outV e o valor total emprestado pelo banco em questao a outros bancos;
outVM e o valor total emprestado pelo banco em questao a bancos maus;
inV e o valor total emprestado ao banco em questao por outros bancos;
inVM e o valor total emprestado ao banco em questao por bancos maus.*/
        for (i=0;i<c;i++){
            for (col=0;col<c;col++){
                if (matriz[i][col]!=0){
                    outP++;
                    outV=outV+matriz[i][col];
                    if (clientes[col].classificacao==0)
                        outVM=outVM+matriz[i][col];}
            }
            for (lin=0;lin<c;lin++){
                if (matriz[lin][i]!=0){
                    inP++;
                    inV=inV+matriz[lin][i];
                    if (clientes[lin].classificacao==0)
                        inVM=inVM+matriz[lin][i];}
                    }
	    printf("%d %s %d %d %d %d %d %d %d\n", clientes[i].ref, clientes[i].nome, clientes[i].classificacao, inP, outP, outV, outVM, inV, inVM);
	    inP=0;
	    outP=0;
	    outV=0;
	    outVM=0;
	    inV=0;
	    inVM=0;
}
		}

	else if (num==2){
/*O numero 2 faz com que o programa escreva a distribuicao/histograma d(k)
do numero de bancos actualmente com exactamente k parceiros comerciais, sobe a 
forma 'parceiros d(parceiros)'.*/
	    for (i=0;i<c;i++){
            for (m=0;m<c;m++){
                if ((matriz[i][m]!=0) && (matriz[m][i]!=0)) {
                    vectoraux[i]++;
                }
                else if (matriz[i][m] != 0) {
                    vectoraux[i]++;
                    vectoraux[m]++;
                }
            }
        }
        for (i = 0; i < c; i++) {
            finalvec[vectoraux[i]]++;
        }
        for (i = 0; i < c && myCount <= c; i++) {
            if (finalvec[i] != 0) {
                printf ("%d %d\n", i, finalvec[i]);
                myCount+=finalvec[i];
            }
        }
}
	return 0;
    }

/* comando K: baixa de classificacao o banco 'bom' com mais valor emprestado a
bancos 'maus'. Se houver mais do que um banco nestas condicoes, deve baixar de 
classificacao o ultimo banco a ser introduzido no sistema. O output deve ser 
da forma: '*referencia nome classificacao inP outP outV outVM inV inVM\n
"Numero total de bancos" "Numero total de bancos bons"'.*/
int baixa_class_banco(banco clientes[], int matriz[MAXBANK][MAXBANK]){
	int i, col, valor=0, valor_final=0, i_final=0,inP=0,outP=0,outV=0;
    int outVM=0,inV=0,inVM=0,lin,bons=0;
	for (i=0;i<c;i++){
		if (clientes[i].classificacao==1){
			for (col=0;col<c;col++)
				if (clientes[col].classificacao==0)
					valor += matriz[i][col];
			if (valor>=valor_final){
				valor_final = valor;
				i_final = i;}}
		valor = 0;}
	if (valor_final!=0){
		clientes[i_final].classificacao = 0;
        for (col=0;col<c;col++){
                if (matriz[i_final][col]!=0){
                    outP++;
                    outV=outV+matriz[i_final][col];
                    if (clientes[col].classificacao==0)
                        outVM=outVM+matriz[i_final][col];}
                }
        for (lin=0;lin<c;lin++){
                if (matriz[lin][i_final]!=0){
                    inP++;
                    inV=inV+matriz[lin][i_final];
                    if (clientes[lin].classificacao==0)
                        inVM=inVM+matriz[lin][i_final];}
        }
        printf("*%d %s %d %d %d %d %d %d %d\n", clientes[i_final].ref, clientes[i_final].nome, clientes[i_final].classificacao, inP, outP, outV, outVM, inV, inVM);
    }
    for (i=0;i<c;i++){
        if (clientes[i].classificacao==1)
            bons++;
            }
    printf("%d %d\n", c, bons);
    return 0;
}





int main(){
/*Funcao central do programa que chama todas as outras funcoes de acordo com os comandos recebidos*/
    int classificacao, ref1, ref2, i, x, y, comando, valor, num, bons=0, matriz[MAXBANK][MAXBANK];
    banco clientes[MAXBANK];
    char nome[42];
    /*Loop que inicia a matriz 'matriz' a zero*/
    for (x=0;x<MAXBANK;x++)
        for (y=0;y<MAXBANK;y++)
            matriz[x][y]=0;

    while (1){
        comando = getchar();
        getchar();
        switch (comando) {
            case 'a':
                if (scanf("%s %d %d", nome, &classificacao, &ref1)==3){
                    if (classificacao==0 || classificacao==1){
                        add_banco(clientes, nome, classificacao, ref1);}
                    else{
                        printf("Comando desconhecido, introduza outro comando:\n");}
                }
                break;
            case 'k':
                if (scanf("%d", &ref1)==1)
                    class_banco(clientes, ref1, 0);
                break;
            case 'r':
                if (scanf("%d", &ref1)==1)
                    class_banco(clientes, ref1, 1);
                break;
            case 'e':
                if (scanf("%d %d %d", &ref1, &ref2, &valor)==3)
                    add_emp(matriz, clientes, ref1, ref2, valor);
                break;
            case 'p':
                if (scanf("%d %d %d", &ref1, &ref2, &valor)==3)
                    add_amorti(matriz, clientes, ref1, ref2, valor);
                break;
            case 'l':
                if (scanf("%d", &num)==1)
                    list_bancos(num, clientes, matriz);
                break;
            case 'K':
                baixa_class_banco(clientes, matriz);
                break;
            case 'x':
	    /*O comando 'x' sai do programa retornando o numero total de bancos 
	    e o numero total de bancos bons*/
                for (i=0;i<c;i++){
                    if (clientes[i].classificacao==1)
                        bons++;
                }
                printf("%d %d\n", c, bons);
                return EXIT_SUCCESS;
            default:
	    /*Definido para pedir outro comando quando o introduzido nao for conhecido*/
                printf("Comando desconhecido, introduza outro comando:\n");
                break;}
	    if (comando!='K')
	    /*Condicao definida para nao retirar o espaco a seguir ao comando K
	    uma vez que este comando nao recebe informacao adicional*/
            getchar();
        }
    return 0;
}
