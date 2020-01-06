/*
Algoritmo de Huffman
AUTOR: Mendoza Parra Sergio, Salcedo Barron Ruben Osmair, Tejeda Martinez Jose Miguel (C) Diciembre 2015
VERSI�N: 1.0

DESCRIPCI�N: Implementar el algoritmo de codificaci�n de Huffman para codificar archivos de texto bajo lenguaje C.
			� Implementar codificaci�n voraz de Huffman
			� Implementar el algoritmo de decodificaci�n
   
OBSERVACIONES: 

COMPILACI�N: g++ Huffman.cpp -o "Nombre del ejecutable"

EJECUCION: ./"Nombre del ejecutable" (Linux)
			"Nombre del ejecutable".exe (Windows)
*/
//Librerias
#include<stdio.h>
#include<stdlib.h>

//Definiciiones del usuario
#define PAUSE system("pause") //Pausar el sistema (Windows)-> Sustituir por getchar() en Linux
#define CLEAR system("cls")  //Borrar pantalla (Windows)-> Sustituir por clear en Linux

/*Tipo nodo para �rbol o Lista de �rboles
El prop�sito es dual, sirve como elemento de una lista enlazada
Cuando se usa el puntero sig, y como elemento de un �rbol cuando
se usan los punteros cero y uno */
typedef struct _nodo
{
   char letra;      //Letra a la que hace referencia el nodo
   int frecuencia;  //Veces que aparece la letra en el texto o las letras de los nodos de las ramas cero y uno
   unsigned long int bits; // Valor de la codificaci�n de la letra
   char nbits;             // N�mero de bits de la codificaci�n
   _nodo *sig;      //Puntero a siguiente nodo de una lista enlazada
   _nodo *cero;     //Puntero a la rama cero de un �rbol
   _nodo *uno;      //Puntero a la rama uno de un �rbol
} tipoNodo;         //Nombre de tipo

//Nodo para construir una lista para la tabla de codigos
typedef struct _tabla
{
   char letra;      //Letra a la que hace referencia el nodo
   unsigned long int bits; //Valor de la codificaci�n de la letra
   char nbits;      //N�mero de bits de la codificaci�n
   _tabla *sig;     //Siguiente elemento de la tabla
} tipoTabla;        //Nombre del tipo

//Variables globales
tipoTabla *Tabla;

//Declaraci�n de funciones
void Cuenta(tipoNodo* &Lista, char c);
void Ordenar(tipoNodo* &Lista);
void InsertarOrden(tipoNodo* &Cabeza, tipoNodo *e);
void BorrarArbol(tipoNodo *n);
void CrearTabla(tipoNodo *n, int l, int v);
void InsertarTabla(char c, int l, int v);
tipoTabla *BuscaCaracter(tipoTabla *Tabla, char c);
int Codificar(char *in,char *out);
int Decodificar(char *in,char *out);


int main(void)
{
	unsigned int o; //Opciones de men�
	char filein[30],fileout[30]; //archivo de entrada - archivo de salida
	do
	{
		puts("\t\tAlgoritmo de Huffman\n\nQue deseas realizar?");
		puts("1. Codificacion de texto\n2. Decodificacion de texto\n3. Salir");
		scanf("%d",&o);
		CLEAR;
		switch (o)
		{
		case 1:
			puts("Ingresa el fichero de entrada (recuerda agregar la extension de archivo):");
			scanf("%s",filein); //archivo con texto plano
			puts("Ingresa el fichero de salida (recuerda agregar la extension de archivo):");
			scanf("%s",fileout); //archivo de salida con codificacion
			Codificar(filein,fileout);
			PAUSE;
			CLEAR;
			break;
		case 2:
			puts("Ingresa el fichero de entrada:");
			scanf("%s",filein); //archivo codificado
			puts("Ingresa el fichero de salida:");
			scanf("%s",fileout); //archivo decodificado a texto plano
			Decodificar(filein,fileout);
			PAUSE;
			CLEAR;
			break;
		default:
			break;
		};
	}while(o!=3);
	return 0;
}

/*int Codificar(char *in,char *out);
Recibe: ruta de archivo de texto plano, ruta de salida del archivo codificado
Obervaciones: el nombre de archivo debe acompa�arse de su extensi�n. Ej: "archivo1.txt"
*/
int Codificar(char *in,char *out)
{
   tipoNodo *Lista;       // Lista de letras y frecuencias
   tipoNodo *Arbol;       // Arbol de letras y frecuencias

   FILE *fe, *fs;         // Ficheros de entrada y salida
   char c;                // variables auxiliares 
   tipoNodo *p;
   tipoTabla *t;
   int nElementos;        // N�mero de elementos en tabla
   long int Longitud = 0; // Longitud del fichero original

   unsigned long int dWORD; // Doble palabra usada durante la codificaci�n
   int nBits;               // N�mero de bits usados de dWORD

   Lista = NULL;
   // Fase 1: contar frecuencias
   fe = fopen(in, "r");
   while((c = fgetc(fe)) != EOF)
   {
      Longitud++;       // Actualiza la cuenta de la longitud del fichero
      Cuenta(Lista, c); // Actualiza la lista de frecuencias 
   }
   fclose(fe);

   // Ordenar la lista de menor a mayor 
   Ordenar(Lista);

   // Crear el arbol
   Arbol = Lista;
   while(Arbol && Arbol->sig) // Mientras existan al menos dos elementos en la lista
   {
      p = (tipoNodo *)malloc(sizeof(tipoNodo)); // Un nuevo �rbol 
      p->letra = 0;                             // No corresponde a ninguna letra 
      p->uno = Arbol;                           // Rama uno 
      Arbol = Arbol->sig;                       // Siguiente nodo en 
      p->cero = Arbol;                          // Rama cero 
      Arbol = Arbol->sig;                       // Siguiente nodo 
      p->frecuencia = p->uno->frecuencia +
                      p->cero->frecuencia;      // Suma de frecuencias 
      InsertarOrden(Arbol, p);                  // Inserta en nuevo nodo 
   }                                            // orden de frecuencia 

   // Construir la tabla de c�digos binarios 
   Tabla = NULL;
   CrearTabla(Arbol, 0, 0);

   // Crear fichero comprimido 
   fs = fopen(out, "wb");
   // Escribir la longitud del fichero 
   fwrite(&Longitud, sizeof(long int), 1, fs);
   // Cuenta el n�mero de elementos de tabla 
   nElementos = 0;
   t = Tabla;
   while(t)
   {
      nElementos++;
      t = t->sig;
   }
   // Escribir el n�mero de elemenos de tabla 
   fwrite(&nElementos, sizeof(int), 1, fs);
   // Escribir tabla en fichero 
   t = Tabla;
   while(t)
   {
      fwrite(&t->letra, sizeof(char), 1, fs);
      fwrite(&t->bits, sizeof(unsigned long int), 1, fs);
      fwrite(&t->nbits, sizeof(char), 1, fs);
      t = t->sig;
   }

   // Codificaci�n del fichero de entrada 
   fe = fopen(in, "r");
   dWORD = 0; // Valor inicial. 
   nBits = 0; // Ning�n bit 
   while((c = fgetc(fe)) != EOF)
   {
      // Busca c en tabla: 
      t = BuscaCaracter(Tabla, c);
      // Si nBits + t->nbits > 32, sacar un byte 
      while(nBits + t->nbits > 32)
      {
         c = dWORD >> (nBits-8);           // Extrae los 8 bits de mayor peso 
         fwrite(&c, sizeof(char), 1, fs);  // Y lo escribe en el fichero 
         nBits -= 8;                       // Ya tenemos hueco para 8 bits m�s 
      }
      dWORD <<= t->nbits; // Hacemos sitio para el nuevo caracter 
      dWORD |= t->bits;   // Insertamos el nuevo caracter 
      nBits += t->nbits;  // Actualizamos la cuenta de bits 
   }
   // Extraer los cuatro bytes que quedan en dWORD
   while(nBits>0)
   {
      if(nBits>=8) c = dWORD >> (nBits-8);
      else c = dWORD << (8-nBits);
      fwrite(&c, sizeof(char), 1, fs);
      nBits -= 8;
   }

   fclose(fe);  // Cierra los ficheros 
   fclose(fs);

   // Borrar Arbol 
   BorrarArbol(Arbol);

   // Borrar Tabla 
   while(Tabla)
   {
      t = Tabla;
      Tabla = t->sig;
      free(t);
   }

   return 0;
}

/* void Cuenta(tipoNodo* &Lista, char c);
Descripci�n: Actualiza la cuenta de frecuencia del car�cter c.
			 El puntero a Lista se pasa por referencia, ya que debe poder cambiar
			 ya sea por que la lista est� vac�a, o porque el nuevo elemento sea el primero */
void Cuenta(tipoNodo* &Lista, char c)
{
   tipoNodo *p, *a, *q;

   if(!Lista)  // Si la lista est� vac�a, el nuevo nodo ser� Lista
   {
      Lista = (tipoNodo *)malloc(sizeof(tipoNodo)); // Un nodo nuevo 
      Lista->letra = c;                             // Para c 
      Lista->frecuencia = 1;                        // en su 1� aparici�n 
      Lista->sig = Lista->cero = Lista->uno = NULL;
   }
   else
   {
      // Buscar el caracter en la lista (ordenada por letra) 
      p = Lista;
      a = NULL;
      while(p && p->letra < c)
      {
         a = p;      // Guardamos el elemento actual para insertar 
         p = p->sig; // Avanzamos al siguiente 
      }
      // Dos casos: 
      // 1) La letra es c se encontr� 
      if(p && p->letra == c) p->frecuencia++; // Actualizar frecuencia 
      else
      // 2) La letra c no se encontr�
      {
         // Insertar un elemento nuevo 
         q = (tipoNodo *)malloc(sizeof(tipoNodo));
         q->letra = c;
         q->frecuencia = 1;
         q->cero = q->uno = NULL;
         q->sig = p;        // Insertar entre los nodos p 
         if(a) a->sig = q;  // y a 
         else Lista = q;    // Si a es NULL el nuevo es el primero 
      }
   }
}

/*void Ordenar(tipoNodo* &Lista);
Descripci�n: Ordena Lista de menor a mayor por frecuencias.
			 De nuevo pasamos el puntero a lista por referencia */
void Ordenar(tipoNodo* &Lista)
{
   tipoNodo *Lista2, *a;

   if(!Lista) return; // Lista vacia
   Lista2 = Lista;
   Lista = NULL;
   while(Lista2)
   {
      a = Lista2;              // Toma los elementos de Lista2 
      Lista2 = a->sig;
      InsertarOrden(Lista, a); // Y los inserta por orden en Lista 
   }
}

/*void InsertarOrden(tipoNodo* &Cabeza, tipoNodo *e);
Descripcion: Inserta el elemento e en la Lista ordenado por frecuencia de menor a mayor.
			 El puntero a Cabeza se pasa por referencia */
void InsertarOrden(tipoNodo* &Cabeza, tipoNodo *e)
{
   tipoNodo *p, *a;

   if(!Cabeza) // Si Cabeza en NULL, e es el primer elemento
   {
      Cabeza = e;
      Cabeza->sig = NULL;
   }
   else
   {
       // Buscar el caracter en la lista (ordenada por frecuencia)
       p = Cabeza;
       a = NULL;
       while(p && p->frecuencia < e->frecuencia)
       {
          a = p;      // Guardamos el elemento actual para insertar 
          p = p->sig; // Avanzamos al siguiente 
       }
       // Insertar el elemento
       e->sig = p;
       if(a) a->sig = e;   // Insertar entre a y p
       else Cabeza = e;    // el nuevo es el primero 
    }
}

/*void CrearTabla(tipoNodo *n, int l, int v);
Descripci�n; Funci�n recursiva para crear Tabla.
			 Recorre el �rbol cuya raiz es n y le asigna el c�digo v de l bits */
void CrearTabla(tipoNodo *n, int l, int v)
{
   if(n->uno)  CrearTabla(n->uno, l+1, (v<<1)|1);
   if(n->cero) CrearTabla(n->cero, l+1, v<<1);
   if(!n->uno && !n->cero) InsertarTabla(n->letra, l, v);
}

/*void InsertarTabla(char c, int l, int v);
Descripci�n; Insertar un elemento en la tabla */
void InsertarTabla(char c, int l, int v)
{
   tipoTabla *t, *p, *a;

   t = (tipoTabla *)malloc(sizeof(tipoTabla)); // Crea un elemento de tabla
   t->letra = c;                               // Y lo inicializa
   t->bits = v;
   t->nbits = l;

   if(!Tabla)         // Si tabla es NULL, entonces el elemento t es el 1�
   {
      Tabla = t;
      Tabla->sig = NULL;
   }
   else
   {
       // Buscar el caracter en la lista (ordenada por frecuencia)
       p = Tabla;
       a = NULL;
       while(p && p->letra < t->letra)
       {
          a = p;      // Guardamos el elemento actual para insertar
          p = p->sig; // Avanzamos al siguiente
       }
       // Insertar el elemento 
       t->sig = p;
       if(a) a->sig = t;  // Insertar entre a y p 
       else Tabla = t;    // el nuevo es el primero 
    }
}

/*tipoTabla *BuscaCaracter(tipoTabla *Tabla, char c);
Descripci�n: Buscar un caracter en la tabla, devielve un puntero al elemento de la tabla */
tipoTabla *BuscaCaracter(tipoTabla *Tabla, char c)
{
   tipoTabla *t;

   t = Tabla;
   while(t && t->letra != c) t = t->sig;
   return t;
}

/*void BorrarArbol(tipoNodo *n);
Descripci�n: Funci�n recursiva para borrar un arbol */
void BorrarArbol(tipoNodo *n)
{
   if(n->cero) BorrarArbol(n->cero);
   if(n->uno)  BorrarArbol(n->uno);
   free(n);
}

int Decodificar(char *in,char *out)
{
   tipoNodo *Arbol;        // Arbol de codificaci�n
   long int Longitud;      // Longitud de fichero 
   int nElementos;         // Elementos de �rbol 
   unsigned long int bits; // Almacen de bits para decodificaci�n 
   FILE *fe, *fs;          // Ficheros de entrada y salida 

   tipoNodo *p, *q;        // Auxiliares 
   unsigned char a;
   int i, j;

   // Crear un arbol con la informaci�n de la tabla
   Arbol = (tipoNodo *)malloc(sizeof(tipoNodo)); // un nodo nuevo 
   Arbol->letra = 0;
   Arbol->uno = Arbol->cero = NULL;
   fe = fopen(in, "rb");
   fread(&Longitud, sizeof(long int), 1, fe); // Lee el n�mero de caracteres 
   fread(&nElementos, sizeof(int), 1, fe); // Lee el n�mero de elementos 
   for(i = 0; i < nElementos; i++) // Leer todos los elementos 
   {
      p = (tipoNodo *)malloc(sizeof(tipoNodo)); // un nodo nuevo 
      fread(&p->letra, sizeof(char), 1, fe); // Lee el car�cter 
      fread(&p->bits, sizeof(unsigned long int), 1, fe); // Lee el c�digo 
      fread(&p->nbits, sizeof(char), 1, fe); // Lee la longitud 
      p->cero = p->uno = NULL;
      // Insertar el nodo en su lugar 
      j = 1 << (p->nbits-1);
      q = Arbol;
      while(j > 1)
      {
         if(p->bits & j) // es un uno
            if(q->uno) q = q->uno;   // Si el nodo existe, nos movemos a �l 
            else                     // Si no existe, lo creamos 
            {
               q->uno = (tipoNodo *)malloc(sizeof(tipoNodo)); // un nodo nuevo 
               q = q->uno;
               q->letra = 0;
               q->uno = q->cero = NULL;
            }
         else // es un cero 
            if(q->cero) q = q->cero; // Si el nodo existe, nos movemos a �l 
            else                     // Si no existe, lo creamos 
            {
               q->cero = (tipoNodo *)malloc(sizeof(tipoNodo)); // un nodo nuevo 
               q = q->cero;
               q->letra = 0;
               q->uno = q->cero = NULL;
            }
         j >>= 1;  // Siguiente bit 
      }
      // Ultimo Bit 
      if(p->bits & 1) // es un uno
         q->uno = p;
      else            // es un cero 
         q->cero = p;
   }
   // Leer datos comprimidos y extraer al fichero de salida 
   bits = 0;
   fs = fopen(out, "w");
   // Lee los primeros cuatro bytes en la dobel palabra bits 
   fread(&a, sizeof(char), 1, fe);
   bits |= a;
   bits <<= 8;
   fread(&a, sizeof(char), 1, fe);
   bits |= a;
   bits <<= 8;
   fread(&a, sizeof(char), 1, fe);
   bits |= a;
   bits <<= 8;
   fread(&a, sizeof(char), 1, fe);
   bits |= a;
   j = 0; // Cada 8 bits leemos otro byte 
   q = Arbol;
   // Bucle 
   do {
      if(bits & 0x80000000) q = q->uno; else q = q->cero; // Rama adecuada 
      bits <<= 1;           // Siguiente bit 
      j++;
      if(8 == j)            // Cada 8 bits 
      {
         i = fread(&a, sizeof(char), 1, fe); // Leemos un byte desde el fichero 
         bits |= a;                    // Y lo insertamos en bits 
         j = 0;                        // No quedan huecos 
      }                                
      if(!q->uno && !q->cero)          // Si el nodo es una letra 
      {
         putc(q->letra, fs);           // La escribimos en el fich de salida 
         Longitud--;                   // Actualizamos longitud que queda 
         q=Arbol;                      // Volvemos a la raiz del �rbol 
      }
   } while(Longitud);                  // Hasta que acabe el fichero 
   // Procesar la cola 

   fclose(fs);                         // Cerramos ficheros 
   fclose(fe);

   BorrarArbol(Arbol);                 // Borramos el �rbol 
   return 0;
}
