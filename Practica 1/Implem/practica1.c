/*
Autores: Mendoza Parra Sergio, Salcedo Barron Rubén Osmair, Tejeda Martínez José Miguel
Versión 1.0 (20 de Octubre de 2015)
Descripción: Programa que evalúa expresiones infijas

Con la implementación del TAD Pila el programa evalúa una expresión infija
 1)El programa verifica la correcta escritura de paréntesis
 2)El programa muestra la conversión de la expresión a posfijo
 3)El programa permite la evaluación del la expresión posfija

Observaciones: El programa requerira de la libreria "TADPilaEst.h", la cuál tiene las implementaciones 
para hacer uso de las funciones del TAD Pila

Compilación: 	gcc -o practica1 practica1.c TADPilEst.o "Si se tiene el código objeto"
				gcc -o practica1 practica1.c TADPilaEst.c "Si se tiene el código fuente"
Ejecución: Windows practica1.exe  &  Linux ./practica1
*/

//LIBRERIAS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "TADPilaEst.h"

//Tama�o maximo de la cadena
#define TAM_CADENA 100

//Declaracion de funciones
int Capturar(char *cadena); //Función que se llama desde el menú principal para leer la cadena y evaluarla con la funcion EvaluaParentesis()
int EvaluaParentesis(char *cadena); //Recibe la cadena evaluando que haga uso correcto de los paréntesis y se encuentre redactada correctamente
int ConvertirPost(char *cadena,char *cadena2); //Recibe la cadena anteriormente evaluada y realiza la conversión a posfijo, la cual de devuelve en "cadena2"
int EvaluarPost(char *cadena); //Usando la cadena en posfijo se reemplazan los valores de las letras y realiza su evaluación para imprimir en pantalla


void main (void){
	char expInfija[TAM_CADENA], expPost[TAM_CADENA];
	int opc;	//Opciones del menu
	expInfija[0]='\0';
	expPost[0]='\0';
	do{
		opc=0;
		puts("\n\t\tPractica 1\n\n\tEvaluacion de expresiones");
		puts("\n\tQue deseas hacer?\n");
		puts("\t1. Capturar expresion.\n");
		puts("\t2. Ver expresion en posfijo.\n");
		puts("\t3. Evaluar expresion en posfijo.\n");
		puts("\t4. Salir.");
		fflush(stdin);
		scanf("%d",&opc);
		system("cls");
		switch(opc){
			case 1:
				Capturar(expInfija);
				break;
			case 2:
				ConvertirPost(expInfija,expPost);
				break;
			case 3:
				EvaluarPost(expPost);
				break;
			case 4:
				;
		}
	}
	while(opc!=4);
	return;
}

int EvaluaParentesis(char *cadena)
{
	int tam_cadena;
	int i;
	
	//Se declara una pila "mi_pila"
	pila mi_pila;
	//Declaro un elemento "e1"
	elemento e1;	
	//Inicializaci�n de "mi_pila"
	Initialize(&mi_pila);
	
	//Medir el tama�o de la cadena
	tam_cadena=strlen(cadena);
	
	//Recorrer cada caracter de la cadena 
	for(i=0;i<tam_cadena;i++)
	{
		//Si el caracter es ( introducirlo a la pila
		if(cadena[i]=='(')
			{
				e1.c='(';
				Push(&mi_pila,e1);
			}
		
		//Si el caracter es ) realizar un Pop a la pila		
		else if(cadena[i]==')')
			{
				//Si se intenta extraer un elemento y la pila es vacia Error: P.g. (a+b)*c)
				if(Empty(&mi_pila))
				{
					printf("ERROR: Existen mas parentesis que cierran de los que abren");
					return (-1);//Salir del programa con error
				}
				e1=Pop(&mi_pila);
			}
	}
	
	//Si al terminar de revisar la expresi�n a�n hay elementos en la pila Error: P.g. (a+b)*c(a-c
	if(!Empty(&mi_pila))
	{
		printf("ERROR: Existen mas parentesis que abren de los que cierran");
		return (-1); //Salir del programa con error
	}
	
	//Si la ejecuci�n termina de manera correcta
	printf("Expresion correcta");
	
	//Destruir los elementos de la pila
	Destroy(&mi_pila);	
	return 0;
}

int Capturar(char *cadena)
{
	do{
		puts("\nIngresa la expresion\n");
		scanf("%s",cadena);
	}
	while(EvaluaParentesis(cadena)==(-1));
	puts("\n");
	system("pause");
	system("cls");
	return 0;
}

int ConvertirPost(char *cadena,char *cadena2){
	int tam_cadena;
	int i,j=0,k;

	if(cadena[0]!='\0'){
		//Se declara una pila "mi_pila"
		pila mi_pila;
		//Declaro un elemento "e1"
		elemento e1;	
		//Inicializaci�n de "mi_pila"
		Initialize(&mi_pila);
		
		//Medir el tama�o de la cadena
		tam_cadena=strlen(cadena);
		
		puts("Expresion en posfijo:\n");
		
		//Recorrer cada caracter de la cadena 
		for(i=0;i<tam_cadena;i++)
		{
			//Si el caracter es ( introducirlo a la pila
			if(cadena[i]=='(')
				{
					e1.c='(';
					Push(&mi_pila,e1);
				}
			//Si el caracter es ) realizar un Pop a la pila		
			if(cadena[i]==')'){
				for(k=0;k<TAM_CADENA;k++){
					e1=Pop(&mi_pila);
					if(e1.c=='+' || e1.c=='-' || e1.c=='*' || e1.c=='/' || e1.c=='^'){
						strcpy(&cadena2[j],&e1.c);
						j++;
					}
					else if(e1.c=='(')	k=TAM_CADENA;
				}
			}
             //Si la cadena esta en los intervalos de letras de la "A" a la "Z"
			if(cadena[i]<='Z' && cadena[i]>='A'){
				strcpy(&cadena2[j],&cadena[i]);
				j++;
			}
            //Si el operador es "+" devuelve el elemento que esta encima de la pila
			if(cadena[i]=='+'){
                               //Si la pila esta vacia.
				if(Empty(&mi_pila)==FALSE){
					for(k=0;k<TAM_CADENA;k++){
						e1=Top(&mi_pila);
						//Si el operador es de mayor precedencia se hace un pop de la pila. 
						if(e1.c=='+' || e1.c=='-' || e1.c=='*' || e1.c=='/' || e1.c=='^'){
							e1=Pop(&mi_pila);
							strcpy(&cadena2[j],&e1.c);
							j++;
						}
						//Si elemento caracter es '(' o si la pila no esta vacia devuelve el tama�o de la cadena.
						if(e1.c=='(' || Empty(&mi_pila)==TRUE)		k=TAM_CADENA;
					}
					e1.c='+';
					Push(&mi_pila,e1);
				}
				if(Empty(&mi_pila)==TRUE){
					e1.c='+';
					Push(&mi_pila,e1);
				}
			}

            //Si el operador es "-" devuelve el elemento que esta encima de la pila
			if(cadena[i]=='-'){
				if(Empty(&mi_pila)==FALSE){
					for(k=0;k<TAM_CADENA;k++){
						e1=Top(&mi_pila);
						//Si el operador es de mayor precedencia que "-" se hace pop en la pila
						if(e1.c=='-' || e1.c=='*' || e1.c=='/' || e1.c=='^'){
							e1=Pop(&mi_pila);
							strcpy(&cadena2[j],&e1.c);
							j++;
						}
						//Si son de menor precedencia solo se ingresa el "-"
						if(e1.c=='(' || e1.c=='+' || Empty(&mi_pila)==TRUE)		k=TAM_CADENA;
					}
					e1.c='-';
					Push(&mi_pila,e1);
				}
				if(Empty(&mi_pila)==TRUE){
					e1.c='-';
					Push(&mi_pila,e1);
				}
			}
		 
		    //Si el operador es "*" devuelve el elemento que esta encima de la pila
			if(cadena[i]=='*'){
				if(Empty(&mi_pila)==FALSE){
					for(k=0;k<TAM_CADENA;k++){
						e1=Top(&mi_pila);
						//Si los elementos igual o mayor precedencia
						if(e1.c=='*' || e1.c=='/' || e1.c=='^'){
							e1=Pop(&mi_pila);
							strcpy(&cadena2[j],&e1.c);
							j++;
						}
						//Si el elemento es diferente se ingresa el "*"
						if(e1.c!='(' ||e1.c!='+' || e1.c!='-' || Empty(&mi_pila)==TRUE)		k=TAM_CADENA;
					}
					e1.c='*';
					Push(&mi_pila,e1);
				}
				//Si la pila esta vacia solo se devuelve el operando 
				if(Empty(&mi_pila)==TRUE){
					e1.c='*';
					Push(&mi_pila,e1);
				}
			}
		
		    //Si el operador es "/" devuelve el elemento que esta encima de la pila
			if(cadena[i]=='/'){
				if(Empty(&mi_pila)==FALSE){
                    //Recorrido de la cadena para encontrar operandos de mayor precedencia 
					for(k=0;k<TAM_CADENA;k++){
						e1=Top(&mi_pila);
						//Si son de mayor o igual precedencia se saca el elemento
						if(e1.c=='/' || e1.c=='^'){
							e1=Pop(&mi_pila);
							strcpy(&cadena2[j],&e1.c);
							j++;
						}
						//Si es de menor precedencia se queda en la pila el operador de mayor precedencia.
						if(e1.c!='(' ||e1.c!='+' || e1.c!='-' || e1.c!='*' || Empty(&mi_pila)==TRUE)
							k=TAM_CADENA;
					}
					e1.c='/';
					Push(&mi_pila,e1);
				}
				//Si solo hay un operando se devuelve el mismo
				if(Empty(&mi_pila)==TRUE){
					e1.c='/';
					Push(&mi_pila,e1);
				}
			}

            //Si el operador es "^" devuelve el elemento que esta encima de la pila
			else if(cadena[i]=='^'){
				if(Empty(&mi_pila)==FALSE){
                    //Recorrido de la cadena.
					for(k=0;k<TAM_CADENA;k++){
						e1=Top(&mi_pila);
						//Si "^" es igual a su mismo operador
						if(e1.c=='^'){
							e1=Pop(&mi_pila);
							strcpy(&cadena2[j],&e1.c);
							j++;
						}
						//Si es de menor precedencia se ingresa a la pila "^"
						if(e1.c!='(' ||e1.c!='+' || e1.c!='-' || e1.c!='*' || e1.c!='/' || Empty(&mi_pila)==TRUE)
							k=TAM_CADENA;
					}
					e1.c='^';
					Push(&mi_pila,e1);
				}
				//Si es el unico operando se devuelve el mismo
				if(Empty(&mi_pila)==TRUE){
					e1.c='^';
					Push(&mi_pila,e1);
				}
			}
		}
		
		if(Empty(&mi_pila)==FALSE){
			k=Value_Top(&mi_pila)+1;
			for(i=0;i<k;i++){
				e1=Pop(&mi_pila);
				strcpy(&cadena2[j],&e1.c);
				j++;
			}
		}
		//Destruir los elementos de la pila
		Destroy(&mi_pila);
		for(i=0;i<j;i++)	printf("%c",cadena2[i]);
		puts("\n");
	}
	else
		puts("Aun no se ha capturado una expresion.\n");
	fflush(stdin);
	system("pause");	
	system("cls");
	return 0;
}

int EvaluarPost(char *cadena){
	int tam_cadena;
	int i,k;
	int j;
	char letras[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	char expEvaluada[26];
	char postEvaluada[TAM_CADENA];
	int var1, var2, res;
    
    //Si la posicion 0 de la cadena es diferente de nulo
	if(cadena[0]!='\0')
	{ 
        //Se inicia pila               
	    pila mi_pila;
		//Declaro un elemento "e1"
		elemento e1,e2,e3;
		//Inicializaci�n de "mi_pila"
		Initialize(&mi_pila);
		
		//Medir el tama�o de la cadena
		tam_cadena=strlen(cadena);
		
		//Un recorrido de la ExpEvaluada del tama�o 26 (tama�o del abecedario, may�sculas
		for(i=0;i<26;i++)	expEvaluada[i]='\0';
		
		puts("Asignacion de valores:\n"); 
		
		//Asignacion de los valores a las letras correspondientes
		for(i=0;i<tam_cadena;i++){
			if(cadena[i]<='Z' && cadena[i]>='A'){
				for(j=0;j<26;j++){
					if(letras[j]==cadena[i] && expEvaluada[j]=='\0'){
						printf("Ingresa el valor de %c (solo un digito): ",letras[j]);
						scanf("%s",&expEvaluada[j]);
					}
				}
			}
		}
		
		//Recorrido de la cadena.
		for(i=0;i<tam_cadena;i++){
            //Si estan en el intervalo del "A" a la "Z"(mayusculas)
			if(cadena[i]<='Z' && cadena[i]>='A'){
				for(j=0;j<26;j++){
                    //Si alguna letra es encontrada, se copia en la posicion "0" de letras[j]. 
					if(letras[j]==cadena[i]){
						strcpy(&postEvaluada[i],&expEvaluada[j]);
					}
				}	
			}
			else	strcpy(&postEvaluada[i],&cadena[i]);
		}
		
		//Mientras la postEvaluada sea diferente de nulo.
		i=0;
		while(postEvaluada[i]!='\0'){
            //Si la evaluacion tiene un rango de numeros ingresados del 0 al 9.
			if(postEvaluada[i]>='0'&&postEvaluada[i]<='9'){
                //Lo que se almacena en postEvaluada se le quita '0' en codigo ascii                            
				e1.d=postEvaluada[i]-'0';
				Push(&mi_pila,e1);
			}
			//De lo contrario si la postfija evaluada tiene operandos se hace casos para cada operando  
			else switch(postEvaluada[i]){
				
				//caso que  si el operando es "+" hay dos elementos de caracter entero que se van a sumar.
                case '+': 
					e1 = Pop(&mi_pila);
                      e2= Pop(&mi_pila);
					  res = e2.d + e1.d;
                      e2.d=res;
					  Push(&mi_pila,e2);
                      break;

                //caso que  si el operando es "-" hay dos elementos de caracter entero que se van a restar.
				case '-' : e1 = Pop(&mi_pila);
                      e2= Pop(&mi_pila);
					  res = e2.d - e1.d;
                      e2.d=res;
					  Push(&mi_pila,e2);
                       break;

                //caso que  si el operando es "*" hay dos elementos de caracter entero que se van a multiplicar.
				case '*' : e1 = Pop(&mi_pila);
                      e2= Pop(&mi_pila);
					  res = e2.d * e1.d;
                      e2.d=res;
					  Push(&mi_pila,e2);
                       break;

                //caso que  si el operando es "/" hay dos elementos de caracter entero que se van a dividir.
				case '/' : e1 = Pop(&mi_pila);
                      e2= Pop(&mi_pila);
					  res = e2.d / e1.d;
                      e2.d=res;
					  Push(&mi_pila,e2);
                       break;

                //caso que  si el operando es "^" hay dos elementos de caracter entero que se le aplica la potecia de uno.
				case '^' : e1 = Pop(&mi_pila);
                      e2= Pop(&mi_pila);
					  e3.d=1;
					  //Sumatoria de las multiplicaciones de elemento 3 
					  for(j=0;j<e1.d;j++)	e3.d=e3.d*e2.d;
					  Push(&mi_pila,e3);
                      break;
			}
		i++;
		}
		e2=Pop(&mi_pila);
		printf("\n\nEl resultado de la expresion es: %i \n", e2.d);
	}
	//Si no se ha ingresado nada se manda un mensaje.
	else
		puts("Aun no se ha evaluado una expresion a posfijo.\n");
  	system("pause");
	system("cls");
	return 0;
}
