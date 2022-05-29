#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

#ifndef SPLAY_TREE
#define SPLAY_TREE
/**
  * Árbol Splay-Segunda programada de datos
  * Autor: Kevin Salazar
  * Estructura definida para poder ser usada
  * con cadenas de caracteres
  */

typedef struct node {
	int num;             //posicion en la cual fue insertada, SE ASIGNA SOLITO
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

node* new_node() {
	node *n = calloc(1, sizeof(node));
	n->num = 0;
	n->word = "";
	n->books = newLinkedList();
	n->parent = NULL;
	n->right = NULL;
	n->left = NULL;

	return n;
}

//funcion tipo toString de java, pero aplicado a los nodos del arbol splay
void toString(node* n){
	printf("***************************\n");
	printf("[%d] Palabra: %s \n", n->num, n->word);
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

//constructor sobrecargado de nodos
node* new_node2(char* texto){
	node *n = calloc(1, sizeof(node));
	n->num = 0;
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
//Retorna el nodo mÃ¡s grande
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

void insert(splay_tree *t, node *n) {
	int x = t->pos;
	x++;
	t->pos = x;
	n->num=x;

	node *y = NULL;
	node *temp = t->root;
	while(temp != NULL) {
	  y = temp;
	  if(n->num < temp->num)
	    temp = temp->left;
	  else
	    temp = temp->right;
	}
	n->parent = y;

	if(y == NULL) //newly added node is root
	  t->root = n;
	else if(n->num < y->num)
	  y->left = n;
	else
	  y->right = n;

	splay(t, n);
}

node* search(splay_tree *t, node *n, int x) {
	if(x == n->num) {
	  splay(t, n);
	  return n;
	}
	else if(x < n->num)
	  return search(t, n->left, x);
	else if(x > n->num)
	  return search(t, n->right, x);
	else
	  return NULL;
}

void delete(splay_tree *t, node *n) {
	splay(t, n);

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
#endif
