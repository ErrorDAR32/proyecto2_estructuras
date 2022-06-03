#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

#ifndef SPLAY_TREE
#define SPLAY_TREE
/**
  * arbol Splay-Segunda programada de datos
  * Autor: Kevin Salazar
  * Estructura definida para poder ser usada
  * con cadenas de caracteres
  */

typedef struct node {
	char* word;          //palabra
	linkedList* books;   //lista de libros donde se encuentra la palabra
	struct node *left;   //sub-izq
	struct node *right;  //sub-der
	struct node *parent; //nodo padre
}node;

typedef struct splay_tree {
	int pos;
	struct node *root;
}splay_tree;


//funcion tipo toString de java, pero aplicado a los nodos del arbol splay
void toString(node* n){
	printf("***************************\n");
	printf("Palabra: %s \n", n->word);
	printf("Lista de coincidencias: \n");
    linkedList* L = n->books;
	nodo* actual = L->inicio;
	int i=1;
	while(actual!=NULL){
		printf("\t%d. %s\n", i, actual->texto);
		actual=actual->sig;
		i++;
	}
}

//constructor de nodos
node* new_node(char* texto){
	node *n = calloc(1, sizeof(node));
	n->word = texto;
	n->books = newLinkedList();
	n->parent = NULL;
	n->right = NULL;
	n->left = NULL;

	return n;
}

splay_tree* new_splay_tree() {
	splay_tree *t = calloc(1, sizeof(splay_tree));
	t->root = NULL;

	return t;
}

//Se llama a esta funcion para imprimir el splay tree

//Retorna el nodo más grande
node* maximum(splay_tree *t, node *x) {
	while(x->right != NULL)
  	x = x->right;
	return x;
}

void left_rotate(splay_tree *t, node *x) {
	node *y = x->right;
	x->right = y->left;
	if(y->left != NULL) {
  		y->left->parent = x;
	}
	y->parent = x->parent;
	if(x->parent == NULL) { //x is root
  		t->root = y;
	}
	else if(x == x->parent->left) { //x is left child
  		x->parent->left = y;
	}
	else { //x is right child
  		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void right_rotate(splay_tree *t, node *x) {
	node *y = x->left;
	x->left = y->right;
	if(y->right != NULL) {
  		y->right->parent = x;
	}
	y->parent = x->parent;
	if(x->parent == NULL) { //x is root
  		t->root = y;
	}
	else if(x == x->parent->right) { //x is left child
  		x->parent->right = y;
	}
	else { //x is right child
  		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

//Funcion de "chaflaneo"
void splay(splay_tree *t, node *n) {
	if(n==NULL)
		return;
	while(n->parent != NULL) { //node is not root
	  if(n->parent == t->root) { //node is child of root, one rotation
	    if(n == n->parent->left) {
	      right_rotate(t, n->parent);
	    }
	    else {
	      left_rotate(t, n->parent);
	    }
	  }
	  else {
	    node *p = n->parent;
	    node *g = p->parent; //grandparent

	    if(n->parent->left == n && p->parent->left == p) { //both are left children
	      right_rotate(t, g);
	      right_rotate(t, p);
	    }
	    else if(n->parent->right == n && p->parent->right == p) { //both are right children
	      left_rotate(t, g);
	      left_rotate(t, p);
	    }
	    else if(n->parent->right == n && p->parent->left == p) {
	      left_rotate(t, p);
	      right_rotate(t, g);
	    }
	    else if(n->parent->left == n && p->parent->right == p) {
	      right_rotate(t, p);
	      left_rotate(t, g);
	    }
	  }
	}
}

//Function of insert node in splay tree
void insert(splay_tree *t, char *content) {
	node *n = new_node(content);
	node *y = NULL;
	node *temp = t->root;
	while(temp != NULL) {
	  y = temp;
	  if(strcmp(n->word, temp->word) < 0) //strcmp returns value with difference of chars through the words (ASCII value); it will be negative
	    temp = temp->left;
	  else
	    temp = temp->right;
	}
	n->parent = y;

	if(y == NULL) //newly added node is root
	  t->root = n;
	else if(strcmp(content, y->word) < 0)
	  y->left = n;
	else
	  y->right = n;

	splay(t, n);
}

node* search_aux(splay_tree *t, node *n, char* x) {
	if(n==NULL){
		printf("\nNo se encontro el nodo [%s]\n", x);
	    return NULL;
	}
	if( strcmp(x, n->word) == 0 ) { //comparation of strings with func of "string.h"; 0 is when is not difference between them
	  splay(t, n);
	  return n;
	}
	if(strcmp(x, n->word) < 0){
	  return search_aux(t, n->left, x);
	}
	if(strcmp(x, n->word) > 0){
	  return search_aux(t, n->right, x);
	}
	else{
		return NULL;
	}
}

//it deletes a node from the splay tree
void delete(splay_tree *t, node *n) {
	//The splay is made during the verification of n!=null
	splay_tree *left_subtree = new_splay_tree();
	left_subtree->root = t->root->left;
	if(left_subtree->root != NULL)
	  left_subtree->root->parent = NULL;

	splay_tree *right_subtree = new_splay_tree();
	right_subtree->root = t->root->right;
	if(right_subtree->root != NULL)
	  right_subtree->root->parent = NULL;

	free(n);

	if(left_subtree->root != NULL) {
	  node *m = maximum(left_subtree, left_subtree->root);
	  splay(left_subtree, m);
	  left_subtree->root->right = right_subtree->root;
	  t->root = left_subtree->root;
	}
	else {
	  t->root = right_subtree->root;
	}
}

//Imprime el arbol en forma lineal, SIN HACER ROTACIONES ~implem. recursiva
void inorder(splay_tree *t, node *n) {
	if(n != NULL) {
	  inorder(t, n->left);
	  toString(n);
	  inorder(t, n->right);
	}
}

void imprimir(splay_tree* t){
	inorder(t, t->root);
}

node *search(splay_tree *t, char* texto){
	return search_aux(t, t->root, texto);
}

void eliminar(splay_tree *t, char* txt){
	node *n=search(t, txt); 
	if(n != NULL){
		delete(t, n);
		return;
	}else{
		printf("No se puede borrar");
	}
	

}
#endif
