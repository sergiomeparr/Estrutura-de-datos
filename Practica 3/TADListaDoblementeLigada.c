//Librerías
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "TADListaDoblementeLigada.h" //Librería personalizada para las implementaciones del TAD Lista

//Operaciones de construcción

/*
void Initialize(lista *l);
Descripción: Recibe un apuntador a lista *l y la inicializa para su trabajo normal.
*/
void Initialize(lista *l)
{
	(*l).frente=NULL;
	l->final=NULL;
	l->tam=0;
	return;
}

/*
void Destroy(lista *l);
Descripción:: Recibe un apuntador a lista *l y la libera completamente.
*/
void Destroy(lista *l)
{
	nodo *aux;
	while(l->frente!=NULL)
	{
		aux=l->frente->atras;
		free(l->frente);
		l->frente=aux;
	}
	l->final=NULL;
	l->tam=0;
	return;
}

//Operaciones de consulta

/*
elemento Position(lista *l, posicion p);
Descripción: Recibe un apuntador a lista *l, una posición p y devuelve el elemento
			 en dicha posición.
Observaciones: La lista l no debe ser vacía y la posición P debe ser una
			   posición valida.
*/
elemento Position(lista *l, posicion p)
{
	elemento e;
	strcpy(e.palabra,"0");
	strcpy(e.definicion,"0");
	if(ValidatePosition(l,p)==TRUE)
	{
		return p->e;
	}
	else
	{
		return e;
	}
	return p->e;
}

/*
elemento Element(lista *l, unsigned long n);
Descripción: Recibe un apuntador a lista *l y un índice n (entre 1 y el tamaño de la lista), y devuelve el
			 elemento que se encuentra en la lista en ese índice partiendo del frente de esta =1 hacia
			 atrás.
Observaciones: Si la lista esta vacía o el índice se encuentra fuera del tamaño de la lista se
			   produce error, saliendo del programa.
*/
elemento Element(lista *l, unsigned long n)
{
	nodo *aux;
	elemento e;
	unsigned long i;
	
	aux=l->frente;
	strcpy(e.palabra,"0");
	strcpy(e.definicion,"0");
	if(aux!=NULL&&n>0&&n<=Size(l))
	{
		for(i=1;i<n&&aux!=NULL;i++)
		{
			aux=aux->atras;
		}		
		
		return aux->e;
	}
	else
	{
		return e;
	}
}

/*
unsigned long Size(lista *l);
Descripción: Recibe un apuntador a lista *l y devuelve el tamaño de la lista.
*/
unsigned long Size(lista *l)
{
	return l->tam;	
}

/*
boolean Empty(lista *l);
Descripción: Recibe un apuntador a lista *l y devuelve TRUE en caso de que la
			 lista este vacía; devuelve FALSE en caso contrario
*/
boolean Empty(lista *l)
{
	if(l->frente==NULL && l->final==NULL && l->tam==0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
boolean ValidatePosition(lista *l, posicion p);
Descripción: Recibe un apuntador a lista l, una posición p y devuelve TRUE si la
			 posición es una posición p válida en la lista l y FALSE en caso
			 contrario.
*/
boolean ValidatePosition(lista *l, posicion p)
{
	nodo *aux;
	
	aux=l->frente;
	while(aux!=p&&aux!=NULL)
	{
		aux=aux->atras;
	}
	
	if(aux==NULL)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

//Operaciones de modificación

/*
void Insert(lista *l, elemento e, posicion p,boolean b);
Descripción: Recibe un apuntador a lista l, una posición p, un elemento e y un
			 valor booleano; el elemento e deberá agregarse en la
			 posición anterior de p si b es verdadero y en la posición
			 siguiente de P en caso contrario.
Observaciones: La posición p es una posición valida, si p es
			   no valida o NULL, se insertará a e al frente de la lista.
*/
void Insert(lista *l, elemento e, posicion p,boolean b)
{
	nodo* aux;
	//Crear al nodo
	aux=(nodo *)malloc(sizeof(nodo));
	aux->e=e;

	//Validar la posicion
	if(ValidatePosition(l,p)==TRUE)
	{			
		//Atras de P
		if(b==TRUE)
		{
			//Si P es el final de la lista
			if(l->final==p)
			{
				l->final=aux;
			}
			
			aux->atras=p->atras;
			p->atras=aux;
			aux->adelante=p;
			aux->atras->adelante=aux; //*(aux->atras).adelante=aux;
		}
		else
		{
			//Si P es el frente de la lista
			if(l->frente==p)
			{
				l->frente=aux;
			}
			
			aux->adelante=p->adelante;
			aux->atras=p;
			p->adelante=aux;
			aux->adelante->atras=aux;
			
		}
	}		
	else
	{
		//Insertar al frente de la lista
		//Si es vacia
		if(l->frente==NULL&&l->final==NULL)
		{
			aux->atras=NULL;
			aux->adelante=NULL;
			l->frente=aux;
			l->final=aux;		
		}
		//Si no es vacia
		else
		{
			aux->adelante=NULL;
			aux->atras=l->frente;
			l->frente->adelante=aux;
			l->frente=aux;
		}
	}
	
	l->tam++;
	return;
}

/*
void Add(lista *l,elemento e);
Descripción: Recibe un apuntador a lista l y un elemento e, el cual se se agrega al
			 final de la lista.
*/
void Add(lista *l,elemento e)
{
	nodo* aux;
	//Crear al nodo
	aux=(nodo *)malloc(sizeof(nodo));
	aux->e=e;

	//Insertar al final de la lista
	//Si es vacia
	if(l->frente==NULL&&l->final==NULL)
	{
		aux->atras=NULL;
		aux->adelante=NULL;
		l->frente=aux;
		l->final=aux;		
	}
	//Si no es vacia agregar al final
	else
	{
		aux->atras=NULL;
		aux->adelante=l->final;
		l->final->atras=aux;
		l->final=aux;
	}
	
	l->tam++;
	return;
}

/*
void Remove(lista *l,posicion p);
Descripción: Recibe un apuntador a lista l y una posición p, el elemento en la
			 posición p será removido, conservando las refencias a los demás elementos de la lista.
Observaciones: La lista l no debe ser vacía y la posición p debe ser una
			   posición valida.
*/
void Remove(lista *l,posicion p)
{
	//Validar la posicion
	if(ValidatePosition(l,p)==TRUE)
	{
		//Si P es el frente
		if(p==l->frente)
		{
			l->frente=p->atras;
			p->atras->adelante=NULL;
			free(p);
		}
		//Si P es el ultimo nodo
		else if(p==l->final)
		{
			l->final=p->adelante;
			p->adelante->atras=NULL;
			free(p);			
		}
		else
		{
			p->adelante->atras=p->atras;
			p->atras->adelante=p->adelante;
			free(p);			
		}
		//Actualizar el numero de nodos
		l->tam--;	
	}
	else
	{
		exit(1);
	}
}

/*
void Replace(lista *l,posicion p, elemento e);
Descripción: Recibe un apuntador a lista *l, una posición p y un elemento e, el
			 elemento en la posición P será sustituido por e
Observaciones: La lista l no debe ser vacía y la posición p debe ser una
			   posición valida.
*/
void Replace(lista *l,posicion p, elemento e)
{
	//Validar la posicion
	if(ValidatePosition(l,p)==TRUE)
	{
		p->e=e;
	}
	else
	{
		exit(1);
	}	
}

//Operaciones de posicionamiento y busqueda

/*
posicion Final(lista *l);
Descripción: Recibe un apuntador a lista *l y retorna la posición del elemento al
			 final de la misma.
*/
posicion Final(lista *l)
{
	return l->final;
}

/*
posicion First(lista *l);
Descripción: Recibe un apuntador a lista *l y devuelve la posición del elemento
			 al inicio de la misma.
*/
posicion First(lista *l)
{
	return l->frente;
}

/*
posicion Following(lista *l, posicion p);
Descripción: Recibe un apuntador a lista *l, una posición p y devuelve la
			 posición del elemento siguiente de p.
Observaciones: La lista l no debe ser vacía y la posición p debe ser una
			   posición valida.
*/
posicion Following(lista *l, posicion p)
{
	if(ValidatePosition(l,p)==TRUE)
	{
		return p->atras;
	}	
	else
	{
		exit(1);
	}
}

/*
posicion Previous(lista *l, posicion p);
Descripción: Recibe un apuntador a lista *l, una posición p y devuelve la
			 posición del elemento anterior a p.
Observaciones: La lista l no debe ser vacía y la posición p debe ser una
			   posición valida.
*/
posicion Previous(lista *l, posicion p)
{
	if(ValidatePosition(l,p)==TRUE)
	{
		return p->adelante;
	}	
	else
	{
		exit(1);
	}	
}

/*
posicion Search(lista *l, elemento e);
Descripción: Recibe un apuntador a lista *l y un elemento e, devuelve la
			 posición del elemento que coincida exactamente con e.
*/
posicion Search(lista *l, elemento e)
{
	nodo *aux;
	aux=l->frente;
	while(aux!=NULL)
	{
		if(memcmp(&((*aux).e),&e,sizeof(elemento))==0) //memcmp(&aux->e,&e,sizeof(elemento)==0)
		{
			return aux;
		}
		aux=aux->atras;
	}
	return NULL;
}
