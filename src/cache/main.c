#include "splay_tree.h"
#include "cache_io.h"
#include<stdlib.h>
#include<stdio.h>

int main() {
	splay_tree *t = new_splay_tree();
	
	printf("******************\n");
	
	insert(t, "hola");
	
	insert(t, "arroz");
	insert(t, "hole");
	insert(t, "holi");
	insert(t, "cabello");
	insert(t, "piramide");
	insert(t, "esternocleidomastoideo");
	insert(t, "adrenalina");
	insert(t, "carne");
	insert(t, "perone");
	insert(t, "programacion");
	insert(t, "xochimilco");
	insert(t, "zorro");

	node *x=search(t, "arroz");	
	node *y=search(t, "hole");
	insertar(x->books, "don quijote");
	insertar(y->books, "mein kampf");
	insertar(x->books, "metamorfosis");

	imprimir(t);
    
	splay(t,search(t,"esternocleidomastoideo"));
	printf("xxxxxxxxxxxxxxxxxx\n");
	printf("[%s]", t->root->word);
	printf("xxxxxxxxxxxxxxxxxx\n");
	printf("\n");
	eliminar(t, "arroz");
	eliminar(t, "zorro");
	
	imprimir(t);
	printf("\nguardando...\n");
	save_aux(t, t->root, "fichero.txt");
	/*node* act = search(t, i, 70);
	printf("[%d]", t->root->data);
	inorder(t, t->root);*/
	return 0;
}
