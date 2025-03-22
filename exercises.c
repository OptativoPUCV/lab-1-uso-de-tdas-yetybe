#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "arraylist.h"
#include "stack.h"

//#include "exercises.h"

//Funciones auxiliares que puedes utilizar para debuggear tus ejercicios
//NO MODIFICAR
void imprime_lista(List *L) {
   int *dato;
   dato = (int*)first(L);
   printf("[");
   while(dato != NULL) {
      printf("%d ", *dato);
      dato = (int*)next(L);
   }
   printf("]\n");

}

//Ojo que la pila se vacía al imprimir y se imprime en orden inverso
//NO MODIFICAR
void imprime_y_vacia_pila(Stack *P) {
   void *dato;
   printf("[");
   while((dato = pop(P)) != NULL) {
      printf("%d ", *(int*)dato);
   }
   printf("]\n");
}

/* 
Ejercicio 1.
Crea una Lista y agrega punteros a elementos del 1 al 10.
Recuerda que la lista almacena punteros, por lo que
debes reservar memoria para cada elemento que agregues.
Al finalizar retorna la lista creada.
*/

/*List* crea_lista() 
{
   List* L = create_list();
   for (size_t k = 1; k < 11; k++) 
   {
      int *elemento = (int*)malloc(sizeof(int)); 
      *elemento = k;
      pushBack(L, elemento);
   }
   return L;
}
   */

List* crea_lista() {
   // Crear una lista vacía
   List* L = create_list();
   printf("[LOG] Lista creada.\n");

   // Agregar elementos del 1 al 10
   for (int i = 1; i <= 10; i++) {
      // Reservar memoria para el entero
      int* dato = (int*)malloc(sizeof(int));
      dato = i; // Asignar el valor correspondiente
      printf("[LOG] Reservada memoria para el entero: %d\n",dato);

      // Agregar el elemento al final de la lista
      pushBack(L, dato);
      printf("[LOG] Elemento %d agregado a la lista.\n", *dato);
   }

   // Retornar la lista creada
   printf("[LOG] Lista completada. Retornando lista...\n");
   return L;
}
   
/*
Ejercicio 2.
Crea una función que reciba una lista de enteros (int*) y 
retorne la suma de sus elementos.

int sumaLista(List *L) 
{
   if (L == NULL) return 0;

   int contador = 0;
   int *elemento = first(L);
   while (elemento !=  NULL)
   {
      contador += *elemento;
      elemento = next(L);
   }
   return contador;
}

/*
Ejercicio 3.
Crea una función que reciba una lista de punteros a int (int*) y
un entero elem. La función debe eliminar todos los elementos 
de la lista que sean iguales a elem.
Asume que popCurrent luego de eliminar un elemento se
posiciona en el elemento anterior.
*/

void eliminaElementos(List*L, int elem)
{
   int *posicion = first(L);
   int *primero = first(L);
   while(posicion != NULL)
   {
      if (*primero  == elem )
         popFront(L);

      else if (*posicion == elem)
      {
         popCurrent(L);
      }
      posicion = next(L); 
   }
}

/*
Ejercicio 4.
La función copia los punteros de la pila P1 en la pila P2.
El orden de ambas pilas se debe mantener.
Puedes usar una pila auxiliar.
*/

void copia_pila(Stack* P1, Stack* P2) 
{
   Stack *pAux = create_stack();
   while(top(P1) != -1)
   {
      void *puntero = top(P1);
      push(pAux , puntero );
      pop(P1);
   }

   while(top(pAux) != -1)
   {
      void *puntero = top(pAux);
      push(P1 , puntero);
      push( P2, puntero );
      pop(pAux);
   }
}

/*
Ejercicio 5.
La función verifica si la cadena de entrada tiene sus 
paraéntesis balanceados. Retorna 1 si están balanceados,
0 en caso contrario.
*/

int parentesisBalanceados(char *cadena) 
{
   Stack *pilAux = create_stack();
   Stack *pilaComp = create_stack();
   Stack *pilaOriginal = create_stack();
   if (!pilAux || !pilaComp || !pilaOriginal) return 0;

   int len = strlen(cadena);

   for (int k = 0; k < len ; k ++)
   {
      char *c = malloc(sizeof(char));
      if (!c)return 0;
      *c = cadena[k];
      push(pilAux , *c);
      push(pilaComp , *c);
   }

  
   while ( top(pilAux) != -1)
   {
      push(pilaOriginal , top(pilAux));
      pop(pilAux);
   }

   while (top(pilaOriginal) != -1)
   {
      char *c1 = (char*)top(pilaOriginal);
      char *c2 = (char*)top(pilaComp);
      
      if (*c1 == '(' && *c2 != ')' || *c1 == '{' && *c2 != '}' || *c1 == '[' && *c2 != ']'  ) return 0;
      pop(pilaOriginal);
      pop(pilaComp);
   }


   return 1;
}



int main()
{
   List *lista = crea_lista();
    
  
   return 0;
}
