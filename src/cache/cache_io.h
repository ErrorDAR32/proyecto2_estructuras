#ifndef CACHE_IO
#define CACHE_IO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splay_tree.h"

#define MAX 100000

//funciones de apoyo, se quedan un rato aqui xd
/*
pienso usar una linked list para guardar cada que el string se tope con 
una de estas (|) o estas (°)
*/
//************************************************
//struct de lista simple, con solo funcion de insercion para hacer entrada y salida de cache
/*typedef struct nd{
	char* key;
	char* value;
	struct nd* sig;
}nd;

typedef struct list{
	struct nd* start;
}list;

nd newNd(char* k, char* v){
	nd *nn= calloc(1, sizeof(nd));
	nn->key = k;
	nn->value = v;
	return nn;
}
list newList(){
	list *l=calloc(1, sizeof(list));
	return l;
}
void insertList(list *L, nd *n){
	if(L->start == NULL){
		L->start=n;
	}
	else{
		nd* actual = L->start;
		while(actual != NULL){
			if(actual->sig == NULL){
				actual->sig=n;
				return;
			}
			actual=actual->sig;
		}
    }
}
//************************************************
char* recopilar(char* texto){
	int i, largo = strlen(texto);
	char* res = calloc(largo, sizeof(char));
	
	for(i=0; i<=largo; i++){
		if(texto[i]=='|'){
			break; //aqui se implementa lo de la lista dinamica
		}else{
			res[i]=texto[i];
		}
	}
	return res;
}
*/

void save_aux2(node* n, char* f){
	FILE *archivo;
 	archivo = fopen(f,"r+");
	fprintf(archivo, "***************************\n");
	fprintf(archivo, "[%d] Palabra: %s \n", n->num, n->word);
	fprintf(archivo, "Lista de coincidencias: \n");
    linkedList* L = n->books;
	nodo* actual = L->inicio;
	int i=1;
	while(actual!=NULL){
		fprintf(archivo, "\t%d. %s\n", i, actual->texto);
		actual=actual->sig;
		i++;
	}
	fclose(archivo);
}

void save_aux(splay_tree *t, node *n, char* f) {
	if(n != NULL) {
	  save_aux(t, n->left,f);
	  save_aux2(n, f);
	  save_aux(t, n->right, f);
	}
}

void saveTree(splay_tree* s){
 	FILE *archivo;
 	char* nombre = "fichero.txt";
 	archivo = fopen(nombre,"r+");
 	
 	if (archivo == NULL){
        printf("\nARCHIVO NO VALIDO\n");
        system("PAUSE");
        return;
    }
 	else{
 		fclose(archivo);
 		save_aux(s, s->root, nombre);
 	    printf("archivo guardado exitosamente");
		return;
	}
}

/*void loadTree(char* fileName){
	FILE *file;
	char*
	
}*/

#endif
