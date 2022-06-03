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
	printf("\n***************\n");
	node *y=search(t, "holi");
	insertar(x->books, "don quijote"); //la funcion insertar es de la lista integrada al splay tree
	insertar(y->books, "mein kampf");  //node->books es una lista dinamica de enlace simple
	insertar(x->books, "metamorfosis"); //

	imprimir(t);
    
	splay(t,search(t,"esternocleidomastoideo"));
	printf("xxxxxxxxxxxxxxxxxx\n");
	printf("[%s]", t->root->word);
	printf("xxxxxxxxxxxxxxxxxx\n");
	printf("\n");
	eliminar(t, "zorro");
	
	printf("\n\n[%s]\n", t->root->word);
	eliminar(t, "xochimilco");
	
	printf("\n\n[%s]\n", t->root->word);
	imprimir(t);
	//printf("\nguardando...\n");
	//save_aux(t, t->root, "fichero.txt");
	/*node* act = search(t, i, 70);
	printf("[%d]", t->root->data);
	inorder(t, t->root);*/
	return 0;
}
