#include "splay_tree.h"
#include "cache_io.h"
#include<stdlib.h>
#include<stdio.h>

int main() {
	splay_tree *t = new_splay_tree();
	
	insert(t, "hola");
	insert(t, "arroz");
	insert(t, "hole");
	insert(t, "holi");
	insert(t, "cabello");
	insert(t, "piramide");
	insert(t, "esternon");
	insert(t, "adrenalina");
	insert(t, "carne");
	insert(t, "perone");
	insert(t, "programacion");
	insert(t, "xochimilco");
	insert(t, "zorro");

	node *x=search(t, "arroz");	
	node *y=search(t, "holi");
	insertar(x->books, "don quijote"); //la funcion insertar es de la lista integrada al splay tree
	insertar(y->books, "mein kampf");  //node->books es una lista dinamica de enlace simple
	insertar(x->books, "metamorfosis"); //
    
	splay(t,search(t,"esternocleidomastoideo"));
	
	eliminar(t, "xochimilco");

	printf("\nguardando...\n");
	saveTree(t);
	char* buffer = calloc(1000, sizeof(char));
	char* res=calloc(1000, sizeof(char));
	FILE *archivo;
	archivo = fopen("fichero.txt","r+");
	while(feof(archivo)==0){
		fgets(buffer, 1000, archivo);
		res=concatenar(res, buffer);
	}
	printf("%s", res);
	fclose(archivo);

	return 0;
}
