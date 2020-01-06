/*
FIBONACCI Y TRIBONACCI
AUTOR: Mendoza Parra Sergio, Salcedo Barron Ruben Osmair, Tejeda Martinez Jose Miguel (C) Diciembre 2015
VERSIÓN: 1.0

DESCRIPCIÓN: Con la implementación de "Recursividad"  
			 realizar de manera recursiva el numero máximo  
			 en el que llega la serie de fibonacci y 
             Tribonacci.
              
OBSERVACIONES: El programa puede tener problemas dependiendo
              del número en el que llegue las series por lo que
              depende del programa hasta donde llegue.

COMPILACIÓN: gcc Menu.c -o "Nombre del ejecutable"

EJECUCION: ./"Nombre del ejecutable" (Linux)
			"Nombre del ejecutable".exe (Windows)
*/

//Librerias
#include <stdio.h>
#include <stdlib.h>

/*
double fibonacci(double n);
Descripción: Función que permite obtener la Recursividad de la serie de fibonacci.
Recibe: El número del ciclo "for" para hacer la recursividad.
Devuelve: La recursividad del numero ingresado.
Observaciones: En el programa le das un numero y te da el resultado en forma recursiva pero no
               una sucesión de "n" números
*/
double fibonacci(double n)
{
     //Si el numero es mayor a 2  
  if (n>2)
     //Regresa la formula de fibonacci f[n]=f[n-1]+f[n-2]
    return fibonacci(n-1) + fibonacci(n-2);
     //De lo contrario retorna los valores de la sucesión f[0]=0, f[1]=1
  else if (n==2)
    return 1;
  else if (n==1)       
    return 1;
  else if (n==0)
    return 0;
}

/*
double tribonacci(double n1);
Descripción: Función que permite obtener la Recursividad de la serie de Tribonacci.
Recibe: El número del ciclo "for" para hacer la recursividad.
Devuelve: La recursividad del numero ingresado.
Observaciones: En el programa le das un numero y te da el resultado en forma recursiva pero no
               una sucesión de "n" números
*/
double tribonacci(double n1)
{
      //Si el numero es mayor a 3     
  if (n1>=3)
      //Regresa la fórmula de fibonacci f[n]=f[n-1]+f[n-2]+f[n-3]
    return  tribonacci(n1-1) + tribonacci(n1-2)+ tribonacci(n1-3);
      //De lo contrario retorna las condiciones iniciales de la sucesión f[0]=1, f[1]=1, f[2]=2
  else if (n1==2)
    return 2;
  else if (n1==1)       
    return 1;
  else if (n1==0)
    return 1;
}

int main()
{
	int op,r;
	double num,x;
	double num1,x1;
	do
	{
	system("cls");
    printf ("\t\n Menu- \n\n 1-Fibonacci \n\n 2-Tribonacci \n ");
    scanf ("\n %d", &op);
    system("cls");
	switch (op){
        case 1:  
		    printf (" Fibo Introducir número: ");
		    scanf ("%lf", &x); 
		    //Se pasa por valor el numero a la funcion fibonacci.
            for (num=0; num<=x; num++)
		    {
		        printf("%.lf\n",fibonacci(num));
		    }
	    break;
	    case 2:
		    printf (" Tribo Introducir número: ");
    	    scanf ("%lf", &x1); 
	        //Se pasa por valor el numero a la funcion tribonacci.
            for (num1=0; num1<=x1; num1++)
	        {
	            printf("%.lf\n",tribonacci(num1));
	        }
	    break;
	    default: exit(1);
	    break;
        }
   printf ("\t\n Desea repetir \n\n 1-Si \n 2-No\n");
   scanf ("\n %d", &r);
   }while(r!=2);
   return 0;
}
