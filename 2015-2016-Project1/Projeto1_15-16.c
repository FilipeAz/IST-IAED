#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXAIR 1000

typedef struct Airport{
	char id[3];
	int capacity;
	int state;
	int currentFlights; /*so serve pa nao ter que ir srmpre a matriz pa ir buscar o numero de voos de cada aeroporto*/
}aeroporto;

aeroporto Aeroportos[MAXAIR];
int Flights[MAXAIR][MAXAIR];
static int counter = 0;

void resetFlights(){
	int x, y;
	for(x = 0;x < MAXAIR;x++){
		for(y = 0;y < MAXAIR;y++){
			Flights[x][y] = 0;
		}
	}
}

aeroporto newAirport(char id[], int capacity){
	aeroporto new;
	strcpy(new.id,id);
	new.capacity = capacity;
	new.state = 1;
	new.currentFlights = 0;
	return new;
}

int returnAirportPosition(char id[]){ /*apenas devolve a posicao do aeroporto no vetor atraves do nome*/
	int x;
	for(x = 0;x < counter;x++){
		if(strcmp(Aeroportos[x].id,id) == 0){
			return x;
		}
	}
	return -1;
}

void addAirport(char id[], int capacity){
	aeroporto new = newAirport(id,capacity);
	Aeroportos[counter] = new;
	counter++;
}

void updateCapacity(char id[], int capacity){
	int pos = returnAirportPosition(id);
	if(pos != -1 && Aeroportos[pos].state == 1 && (Aeroportos[pos].capacity + capacity) >= Aeroportos[pos].currentFlights){
		Aeroportos[pos].capacity+=capacity;
	}
	else{
		printf("*Capacidade de %s inalterada\n",Aeroportos[pos].id);
	}
}

void addIdaVolta(char id_1[], char id_2[]){
	int pos_1 = returnAirportPosition(id_1), pos_2 = returnAirportPosition(id_2);
	if(pos_1 != -1 && pos_2 != -1 && Aeroportos[pos_1].state == 1 && Aeroportos[pos_2].state == 1 && Aeroportos[pos_1].capacity >= (Aeroportos[pos_1].currentFlights + 2) && Aeroportos[pos_2].capacity >= (Aeroportos[pos_2].currentFlights + 2)){
		Aeroportos[pos_1].currentFlights+=2;
		Aeroportos[pos_2].currentFlights+=2;
		Flights[pos_1][pos_2]++;
		Flights[pos_2][pos_1]++;
	}
	else{
		printf("*Impossivel adicionar voo RT %s %s\n",id_1,id_2);
	}
}

void remIdaVolta(char id_1[],char id_2[]){
	int pos_1 = returnAirportPosition(id_1), pos_2 = returnAirportPosition(id_2);
	if(pos_1 != -1 && pos_2 != -1 && Aeroportos[pos_1].state == 1 && Aeroportos[pos_2].state == 1 && Flights[pos_1][pos_2] > 0 && Flights[pos_2][pos_1] > 0){
		Aeroportos[pos_1].currentFlights-=2;
		Aeroportos[pos_2].currentFlights-=2;
		Flights[pos_1][pos_2]--;
		Flights[pos_2][pos_1]--;
	}
	else{
		printf("*Impossivel remover voo RT %s %s\n",id_1,id_2);
	}
}

void addRota(char id_1[], char id_2[]){
	int pos_1 = returnAirportPosition(id_1), pos_2 = returnAirportPosition(id_2);
	if(pos_1 != -1 && pos_2 != -1 && Aeroportos[pos_1].state == 1 && Aeroportos[pos_2].state == 1 && Aeroportos[pos_1].capacity >= (Aeroportos[pos_1].currentFlights + 1) && Aeroportos[pos_2].capacity >= (Aeroportos[pos_2].currentFlights + 1)){
		Aeroportos[pos_1].currentFlights++;
		Aeroportos[pos_2].currentFlights++;
		Flights[pos_1][pos_2]++;
	}
	else{
		printf("*Impossivel adicionar voo %s %s\n", id_1, id_2);
	}
}

void remVoo(char id_1[],char id_2[]){
	int pos_1 = returnAirportPosition(id_1), pos_2 = returnAirportPosition(id_2);
	if(pos_1 != -1 && pos_2 != -1 && Aeroportos[pos_1].state == 1 && Aeroportos[pos_2].state == 1 && Flights[pos_1][pos_2] > 0){
		Aeroportos[pos_1].currentFlights--;
		Aeroportos[pos_2].currentFlights--;
		Flights[pos_1][pos_2]--;
	}
	else{
		printf("*Impossivel remover voo %s %s\n", id_1, id_2);
	}
}

void numVoos(char id_1[], char id_2[]){
	int pos_1 = returnAirportPosition(id_1), pos_2 = returnAirportPosition(id_2);
	if(pos_1 == -1){
		printf("*Aeroporto %s inexistente\n",id_1);
	}
	if(pos_2 == -1){
		printf("*Aeroporto %s inexistente\n",id_2);
	}
	else{
		printf("Voos entre cidades %s:%s:%d:%d\n", id_1, id_2, Flights[pos_1][pos_2], Flights[pos_2][pos_1]);
	}
}

void MVoos(){
	int x, pos = 0, max = 0, Noutgoing = 0, Nincoming = 0;
	for(x = 0;x < counter;x++){
		if(Aeroportos[x].currentFlights > max){
			max = Aeroportos[x].currentFlights;
			pos = x;
		}
	}
	for(x = 0;x < counter;x++){
		Noutgoing += Flights[pos][x];
		Nincoming += Flights[x][pos];
	}
	
	printf("Aeroporto com mais rotas %s:%d:%d\n", Aeroportos[pos].id, Noutgoing, Nincoming);
}

void MConnected(){
	int x, y, aux = 0, max = -1;
	char id[3];
	for(x = 0;x < counter;x++){
		for(y = 0;y < counter;y++){
			if(Flights[x][y] != 0 || Flights[y][x] != 0){
				aux++;
			}
		}
		if(aux > max){
			max = aux;
			strcpy(id,Aeroportos[x].id);
		}
		aux = 0;
	}
	printf("Aeroporto com mais ligacoes %s:%d\n", id, max);
}

void VMPopular(){
	int x, y, max = 0;
	char id_1[3], id_2[3];
	for(x = 0;x < counter;x++){
		for(y = 0;y < counter;y++){
			if(Flights[x][y] > max){
				max = Flights[x][y];
				strcpy(id_1,Aeroportos[x].id);
				strcpy(id_2,Aeroportos[y].id);
			}
		}
	}
	printf("Voo mais popular %s:%s:%d\n", id_1, id_2, max);
}

void closeAirport(char id[]){
	int pos = returnAirportPosition(id), x;
	if(pos != -1){
		Aeroportos[pos].state = 0;
		Aeroportos[pos].currentFlights = 0;
		for(x = 0;x < counter;x++){
			Aeroportos[x].currentFlights -= Flights[pos][x];
			Aeroportos[x].currentFlights -= Flights[x][pos];
			Flights[pos][x] = 0;
			Flights[x][pos] = 0;
		}
	}
	else{
		printf("*Aeroporto %s inexistente\n", id);
	}
}

void openAirport(char id[]){
	int pos = returnAirportPosition(id);
	if(pos != -1){
		Aeroportos[pos].state = 1;
	}
	else{
		printf("*Aeroporto %s inexistente\n", id);
	}
}

void LZero(){
	int x, y, Noutgoing, Nincoming;
	for(x = 0;x < counter;x++){
		Noutgoing = 0;
		Nincoming = 0;
		for(y = 0;y < counter;y++){
			Noutgoing += Flights[x][y];
			Nincoming += Flights[y][x];
		}
		printf("%s:%d:%d:%d\n", Aeroportos[x].id, Aeroportos[x].capacity, Noutgoing, Nincoming);
	}
}

void LOne(){
	int c, i, x, y, Noutgoing, Nincoming, pos_pri;
	aeroporto aux[counter], s;
	for(c = 0;c < counter;c++){
		aux[c] = Aeroportos[c];
	}
	for(i = 1;i < counter;i++){
		for(c = 1;c < counter;c++){
			if(strcmp(aux[c - 1].id,aux[c].id) > 0){
				s = aux[c - 1];
				aux[c - 1] = aux[c];
				aux[c] = s;
			}
		}
	}
	for(x = 0;x < counter;x++){
		pos_pri = returnAirportPosition(aux[x].id);
		Noutgoing = 0;
		Nincoming = 0;
		for(y = 0;y < counter;y++){
			Noutgoing += Flights[pos_pri][y];
			Nincoming += Flights[y][pos_pri];
		}
		printf("%s:%d:%d:%d\n", aux[x].id, aux[x].capacity, Noutgoing, Nincoming);
	}
}

void LTwo(){
	int x, current = 0, airports = 0, total = 0;
	while(total < counter){
		for(x = 0;x < counter;x++){
			if(Aeroportos[x].currentFlights == current){
				airports++;
				total++;
			}
		}
		if(airports != 0){
			printf("%d:%d\n", current, airports);
		}
		current++;
		airports = 0;
	}
}

void quit(){
	int x, y, flights = 0;
	for(x = 0;x < counter;x++){
		for(y = 0;y < counter;y++){
			flights += Flights[x][y];
		}
	}
	printf("%d:%d\n", flights, counter);
}

int main(){
	char comando, id_1[3], id_2[3];
	int capacity, tipo;
	resetFlights();
	while(1){
		comando = getchar();
		if(comando == 'A'){
			scanf(" %s %d",id_1,&capacity);
			addAirport(id_1,capacity);
		}
		else if(comando == 'I'){
			scanf(" %s %d",id_1,&capacity);
			updateCapacity(id_1,capacity);
		}
		else if(comando == 'F'){
			scanf(" %s %s",id_1,id_2);
			addIdaVolta(id_1,id_2);
		}
		else if(comando == 'G'){
			scanf(" %s %s",id_1,id_2);
			addRota(id_1,id_2);
		}
		else if(comando == 'R'){
			scanf(" %s %s",id_1,id_2);
			remVoo(id_1,id_2);
		}
			
		else if(comando == 'S'){
			scanf(" %s %s",id_1,id_2);
			remIdaVolta(id_1,id_2);
		}
			
		else if(comando == 'N'){
			scanf(" %s %s",id_1,id_2);
			numVoos(id_1,id_2);
		}
		
		else if(comando == 'P'){
			MVoos();
		}
		
		else if(comando == 'Q'){
			MConnected();
		}
		
		else if(comando == 'V'){
			VMPopular();
		}
		
		else if(comando == 'C'){
			scanf(" %s",id_1);
			closeAirport(id_1);
		}
		
		else if(comando == 'O'){
			scanf(" %s",id_1);
			openAirport(id_1);
		}
		
		else if(comando == 'L'){
			scanf(" %d", &tipo);
			if(tipo == 0){
				LZero();
			}
			else if(tipo == 1){
				LOne();
			}
			else if(tipo == 2){
				LTwo();
			}
		}
		
		else if(comando == 'X'){
			quit();
			return EXIT_SUCCESS;
		}
	}
	return 0;
}






































