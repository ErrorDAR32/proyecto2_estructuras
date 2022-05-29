#include <stdio.h>
#include <stdlib.h>
#ifndef LINKED_LIST
#define LINKED_LIST
/**
  * Lista enlazada-Segunda programada de datos
  * Autor: Kevin Salazar
  * Estructura definida para poder ser usada
  * con cadenas de caracteres
  */
  
typedef struct nodo{
	char* texto;
	struct nodo* sig;
}nodo;

typedef struct linkedList{
    struct nodo* inicio;
}linkedList;

//constructor del nodo
nodo* new_nodo(char* txt){
	nodo* n = calloc(1, sizeof(nodo));
	n->texto=txt;
	return n;
}

//constructor de la lista
linkedList* newLinkedList(){
	linkedList* n = calloc(1, sizeof(linkedList));
	return n;
}

//funcion de insercion al final
void insertar(linkedList* L, char* contenido){
	if(L->inicio == NULL){
		L->inicio=new_nodo(contenido);
	}
	else{
		nodo* actual = L->inicio;
		while(actual != NULL){
			if(actual->sig == NULL){
				actual->sig=new_nodo(contenido);
				return;
			}
			actual=actual->sig;
		}
    }
}

//funcion de busqueda de nodos
nodo* buscar(linkedList* L, char* contenido){
	if(L->inicio == NULL){
		return NULL;
	}
	else{
		nodo* actual = L->inicio;
		while(actual != NULL){
			if(actual->texto == contenido){
				return actual;
			}
			else{
				actual=actual->sig;
			}
		}
		return NULL;
    }
}

//Funcion de borrado de nodo
void borrarNodo(linkedList* L, char* contenido){
	if(L->inicio == NULL){
		printf("Lista no valida");
	}
	else{
		nodo* borrar = buscar(L, contenido);
		nodo* actual = L->inicio;
		while(actual != NULL){
			if(actual->sig == borrar){
				actual->sig=borrar->sig;
				return;
			}
			actual=actual->sig;
		}
	}
}
#endif
