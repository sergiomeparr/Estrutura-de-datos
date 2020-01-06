/*
PROBLEMA DE LAS N-REINAS
AUTOR: Mendoza Parra Sergio, Salcedo Barron Ruben Osmair, Tejeda Martinez Jose Miguel (C) Diciembre 2015
VERSI�N: 1.0

DESCRIPCI�N: Con la implementaci�n de "Backtracking"  
			 realizar la implementaci�n de las N-Reinas,
			 el problema de las N-Reinas consiste en colocar n reinas en
             un tablero de ajedrez de tama�o N*N de forma la reinas no
             se amenacen seg�n las normas del ajedrez. Se busca
             encontrar una soluci�n o todas las soluciones posibles. 
              
OBSERVACIONES: 

COMPILACI�N: gcc reinas.c  presentacionWin.c -o "Nombre del ejecutable"

EJECUCION: ./"Nombre del ejecutable" (Linux)
			"Nombre del ejecutable".exe (Windows)
*/

//Librerias
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "presentacion.h"

#define PAUSE system("pause")

static int nReinas = 0;		// Numero de reinas
static int *posicion = 0;	// Posicion en el ajedrez (empieza en 0)


 // ireinas : N�mero de la primera reina de colocar (profundidad del gr�fico)
int resolver(int ireinas);

/*
 Compruebe si la reina en la posici�n "tablero" se las reinas anteriores bien situada respecto.
 *
 * Tablero: Indice de la reina estamos colocando (profundidad del gr�fico).
 *
 * Devuelve 1 si est� bien situado a la reina en la posici�n "tablero",
   otra cosa devuelve 0.
 */
int check(int tablero);

int main(void)
 {
	int resultado = 1, i,j=1,k,l;
	clock_t t0, t1;
     /*Se debe ingresar un numero mayor a 0 de reinas de lo contrario 
       no se realizara la simulaci�n*/
	while (nReinas <= 0 || resultado == 0) {
		printf("Ingrese cuantas reinas : ");
		resultado = scanf("%d", &nReinas);
		system("cls");
	}
	for(k=1;k<=nReinas;k++){
			for(l=1;l<=nReinas;l++){
				MoverCursor(l,k);
				printf("#");
			}
		}
	posicion = (int*)malloc(sizeof(int) * nReinas);
	t0 = clock();
	resultado = resolver(0);
	t1 = clock();
	if (resultado) 
	{
		MoverCursor(0,nReinas+2);
		for (i = 0; i < nReinas; i++)
		{
			printf("Reina %d: columna %d ,fila %d\n", i + 1, j,posicion[i] + 1);
			j++;
		}
	} 
	else
		MoverCursor(0,nReinas+2);
		printf("Se resolvio el problema.\n");

	free(posicion);
	PAUSE;
	BorrarPantalla();
	return 0;
}

/*
int resolver(int ireinas);
Descripci�n: Funci�n de Backtracking el cual se coloca la reina en una posicion valida.
Recibe: El numero de reinas que fueron ingresadas para realizar la simulaci�n.
Devuelve: Las posiciones en las que son validas las n-reinas.
Observaciones: 
*/
int resolver(int ireinas) {
	int k,y,prevy=0;
	for (k = 0; k < nReinas; k++,prevy++) {
		//se coloca la reina una a una hasta llegar a una posicion valida
		posicion[ireinas] = k;
		if(prevy){
			MoverCursor(ireinas+1,prevy);
			printf("#");
		}
		MoverCursor(ireinas+1,k+1);
		printf("*");
		y=k+1;
		EsperarMiliSeg(500);
		if (check(ireinas)) {
			if (ireinas == nReinas - 1){
				return 1;
			}
			else if (resolver(ireinas + 1))
				return 1;
		}
		else
			if(y==nReinas){
				MoverCursor(ireinas+1,y);
				printf("#");
			}
	}

	return 0;
}


/*
int check(int tablero);
Descripci�n: Funci�n que permite saber si una reina est� en la misma columna o diagonal que otra reina en el tablero.
Recibe: El n�mero de reinas que fueron introducidas las cuales pondra en el tablero.
Devuelve: Las posiciones en las que fueron puestas las reinas.
Observaciones: Algunas veces no hace bien el backtracking solo en algunos casos.
*/
int check(int tablero) {
	int i;

	for (i = 0; i < tablero; i++)

		//Si existe una reina en la misma columna o diagonal, devuelve 0.
		if (posicion[i] == posicion[tablero]){
			return 0;
		}
		else if (abs(posicion[tablero] - posicion[i]) == tablero - i)
			return 0;

	return 1;
}

