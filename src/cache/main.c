#include "splay_tree.h"
#include<stdlib.h>
#include<stdio.h>

int main() {
	splay_tree *t = new_splay_tree();
	
	node *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
	a = new_node();
	b = new_node();
	c = new_node();
	d = new_node();
	e = new_node();
	f = new_node();
	g = new_node();
	h = new_node();
	i = new_node();
	j = new_node();
	k = new_node();
	l = new_node();
	m = new_node();
	inorder(t, t->root);
	printf("******************\n");
	
	insert(t, a);
	insertar(a->books, "don quijote");
	insert(t, b);
	insert(t, c);
	insert(t, d);
	insert(t, e);
	insert(t, f);
	insert(t, g);
	insert(t, h);
	insert(t, i);
	insert(t, j);
	insert(t, k);
	insert(t, l);
	insert(t, m);
	inorder(t, t->root);
	printf("[%d]", t->root->num);
	printf("\n");
	delete(t, a);
	delete(t, m);
	
	inorder(t, t->root);
	/*node* act = search(t, i, 70);
	printf("[%d]", t->root->data);
	inorder(t, t->root);*/
	return 0;
}
