/*
TORRES DE HANOI
AUTOR: Mendoza Parra Sergio, Salcedo Barron Ruben Osmair, Tejeda Martinez Jose Miguel (C) Diciembre 2015
VERSIÓN: 1.0

DESCRIPCIÓN: Con la implementación de "Recursividad"  
			 realizar la simulacion de las torres de hanoi 
			 el cual se tendra que ver de forma gráfica, 
             los movimientos que realiza cada disco.

OBSERVACIONES: El programa permite agregar cualquier número 
			   de discos pero, del 1 al 4 hay simulación y
			   mayor a 4 solo estan los pasos a seguir y el 
			   numero de movimientos que se deben realizar.

EL CODIGO QUE IMPLEMENTA LA SIMULACION ES: Libreria.c

COMPILACION: gcc Hanoi.c Libreria.c -o "Nombre del ejecutable"

EJECUCION: ./"Nombre del ejecutable" (Linux)
			"Nombre del ejecutable".exe (Windows)
*/

//Librerias
#include <stdio.h>
#include <stdlib.h>
#include "Libreria.h"  //Libreria que nos permite usar Gotoxy(MoverCursor) para la simulacion
#define tiempo 2       //Tiempo que se espera en cada paso de la simulación

//Funciones
int hanoi(int discos, int torre1, int torre2, int torre3);
int borrar(int x,int y);
int graficos(int discos);

//Variable Global (Contador de movimientos)
int movimientos=0;

int main()
{ 
   menu();
}

int Borrar(int x,int y)
{
    Gotoxy(x,y);
    printf("     ");
}

/*
int graficos(int discos);
Descripcion: Hace la simulacion de las torres de hanoi menores a 5 y mayor a 0.
Recibe: Numero de discos para realizar las simulacion con sus respectivos casos.
Devuelve: La simulación con respectivos discos.
Observaciones: Si se agrega un numero grande no se hara la simulacion solo se pondran los movimientos
*/
int graficos(int discos)
{
    int x;
    //Posiciones para simulación
    int y=13;
    int x1=5;
    if(discos==1){
          Gotoxy(x1,y);
          for(x=1;x<=discos;x++)
          {
              printf("%d\n",x);
          }
          //Se espera 2 segundos en cada movimiento de la simulacion       
          sleep(tiempo);
          Borrar(x1,y);
          Gotoxy(x1+23,y);
          printf("%d",x-1);
          sleep(tiempo);
          printf("\n\n\n\n\n");               
    }
    if(discos==2){
          Gotoxy(x1,y-1);
          for(x=1;x<=discos;x++)
          {
              printf("\t%d\n",x);
          }       
          sleep(tiempo);
          Borrar(x1,y-1);
          Gotoxy(x1+14,y);
          printf("%d",x-2);
          sleep(tiempo);
          Borrar(x1,y);
          Gotoxy(x1+23,y);
          printf("%d",x-1);
          sleep(tiempo);
          Borrar(x1+14,y);
          Gotoxy(x1+23,y-1);
          printf("%d",x-2);
          sleep(tiempo);
          printf("\n\n\n\n\n");                      
    }
    if(discos==3){
          Gotoxy(x1,y-2);
          for(x=1;x<=discos;x++)
          {
              printf("\t%d\n",x);
          }       
          sleep(tiempo);
          Borrar(x1,y-2);
          Gotoxy(x1+23,y);
          printf("%d",x-3);
          sleep(tiempo);
          Borrar(x1,y-1);
          Gotoxy(x1+14,y);
          printf("%d",x-2);
          sleep(tiempo);
          Borrar(x1+23,y);
          Gotoxy(x1+14,y-1);
          printf("%d",x-3);
          sleep(tiempo);
          Borrar(x1,y);
          Gotoxy(x1+23,y);
          printf("%d",x-1);
          sleep(tiempo);
          Borrar(x1+14,y-1);
          Gotoxy(x1+3,y);
          printf("%d",x-3);
          sleep(tiempo);
          Borrar(x1+14,y);
          Gotoxy(x1+23,y-1);
          printf("%d",x-2);
          sleep(tiempo);
          Borrar(x1,y);
          Gotoxy(x1+23,y-2);
          printf("%d",x-3);
          sleep(tiempo);
          printf("\n\n\n\n\n");       
    }
    if(discos==4){
          Gotoxy(x1,y-3);
          for(x=1;x<=discos;x++)
          {
              printf("\t%d\n",x);
          }       
          sleep(tiempo);
          Borrar(x1,y-3);
          Gotoxy(x1+14,y);
          printf("%d",x-4);
          sleep(tiempo);
          Borrar(x1,y-2);
          Gotoxy(x1+23,y);
          printf("%d",x-3);
          sleep(tiempo);
          Borrar(x1+14,y);
          Gotoxy(x1+23,y-1);
          printf("%d",x-4);
          sleep(tiempo);
          Borrar(x1,y-1);
          Gotoxy(x1+14,y);
          printf("%d",x-2);
          sleep(tiempo);
          Borrar(x1+23,y-1);
          Gotoxy(x1+3,y-1);
          printf("%d",x-4);
          sleep(tiempo);
          Borrar(x1+23,y);
          Gotoxy(x1+14,y-1);
          printf("%d",x-3);
          sleep(tiempo);
          Borrar(x1,y-1);
          Gotoxy(x1+14,y-2);
          printf("%d",x-4);
          sleep(tiempo);
          Borrar(x1,y);
          Gotoxy(x1+23,y);
          printf("%d",x-1);
          sleep(tiempo);
          Borrar(x1+14,y-2);
          Gotoxy(x1+23,y-1);
          printf("%d",x-4);
          sleep(tiempo);
          Borrar(x1+14,y-1);
          Gotoxy(x1+4,y);
          printf("%d",x-3);
          sleep(tiempo);
          Borrar(x1+23,y-1);
          Gotoxy(x1+4,y-1);
          printf("%d",x-4);
          sleep(tiempo);
          Borrar(x1+14,y);
          Gotoxy(x1+23,y-1);
          printf("%d",x-2);
          sleep(tiempo);
          Borrar(x1,y-1);
          Gotoxy(x1+14,y);
          printf("%d",x-4);
          sleep(tiempo);
          Borrar(x1,y);
          Gotoxy(x1+23,y-2);
          printf("%d",x-3);
          sleep(tiempo);
          Borrar(x1+14,y);
          Gotoxy(x1+23,y-3);
          printf("%d",x-4);
          sleep(tiempo);
          printf("\n\n\n\n\n");       
    }
}


/*
int hanoi(int discos, int torre1, int torre2, int torre3);
Descripcion: Hace de forma recursiva los movimientos para hacer las torres de hanoi.
Recibe: Numero de discos, las torres se definen al principio dando 1,2,3 valor a las torres.
Devuelve: La recursividad de las torres de hanoi(movimientos).
Observaciones: Si se agrega un numero grande no se hara la simulacion solo se pondran los movimientos
*/    
int hanoi(int discos, int torre1, int torre2, int torre3)
{
  //Si solo hay un disco.  
  if (discos==1){
              //Se mueve de torre 1 a torre 3   
       printf("\tMover Disco %d en Torre %d a Torre %d\n",discos,torre1,torre3);
  }
  else{//Si se tienen más discos.
       //Se resta 1 con forme a los movimientos en cada torre.
       hanoi(discos-1, torre1, torre3, torre2);
	   printf("\tMover Disco %d en Torre %d a Torre %d\n",discos,torre1,torre3);
	   hanoi(discos-1, torre2, torre1, torre3);
  }
  movimientos++;
}

int menu()
{
	int discos;
	int opcion;
	int x=5,y=15,i;
	system("cls");
	printf ("\n\n\t Torres de Hanoi \n ");
	printf("\n\n\tIniciar simulacion(1.Si  2.No): ");
    scanf ("%d", &opcion);
    if(opcion==1){ 
	    printf("\n\tCuantos Discos quieres del 1 al 4: ");
		scanf("%d",&discos);
		printf("\n\n\n\n\n");
	    //Posiciones de las torres para simulación.
        Gotoxy(x,y);
        printf("Torre1");
        Gotoxy(x+10,y);
        printf("Torre2");
        Gotoxy(x+20,y);
        printf("Torre3");
        graficos(discos);                
        printf("\n\n");
        printf("\tPasos a seguir:\n\n");
        hanoi(discos, 1, 2, 3);
        printf("\n\tNumero de Movimientos %d \n\n\n",movimientos);
        system("pause");
        main();		
	    }  
	if(opcion>=2 || opcion<0){
        exit(1);
		}		
}
