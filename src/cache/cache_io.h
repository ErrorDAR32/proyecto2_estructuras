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
una de estas (|) o estas (�)
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

/*
prueba para concatenar caracteres
usando solo la funcion strlen de string.h
*/

char* concatenar(char* a, char* b){
    int l1 = strlen(a);
    int l2 = strlen(b);
    char* res = calloc((10000), sizeof(char)); 
    int i;
    for(i = 0; i<l1; i++){
        res[i]=a[i];
    }
    res[i]=' ';
    int x=0;
    for(i=i+1;i<(l1+l2+1); i++){
        res[i]=b[x];
        x++;
    }

    return res;
}

void save_aux2(node* n, char* f){
	char *buffer = calloc(MAX, sizeof(char));
	FILE *archivo;
 	archivo = fopen(f,"r+"); //lectura/escritura
	while(feof(archivo)==0){
		fgets(buffer, MAX, archivo); //en teoria no hace nada, pero mueve el puntero al final del archivo
	}
	fprintf(archivo, "%s\n", n->word);
	linkedList* L = n->books;
	nodo* actual = L->inicio;
	while(actual!=NULL){
		fprintf(archivo, "\t%s\n", actual->texto);
		actual=actual->sig;
	}
	
	fclose(archivo);
}

int save_aux(splay_tree *t, node *n, char* f) {
	if(n != NULL) {
	  save_aux(t, n->left,f);
	  save_aux2(n, f);
	  save_aux(t, n->right, f);
	  return 0;
	}
	else{
		return -1;
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
 		int x=save_aux(s, s->root, nombre);
		if(x!=0){
			printf("\nno se guardo el archivo\n");
			return;
		} 
		FILE *arch;
		arch=fopen(nombre, "r+");
		char*buffer=calloc(10000, sizeof(char));
		while(feof(archivo)==0){
			fgets(buffer, 10000, archivo); 
		}
		fprintf(arch, "[%s]\n", s->root->word);
		fclose(arch);
 	    printf("\narchivo guardado exitosamente\n");
		return;
	}
}

/*void loadTree(char* fileName){
	FILE *file;
	char*
	
}*/

#endif
