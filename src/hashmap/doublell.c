// a doubly linked list, multipurpose, allocated
// the list works by linking "DLLNode"s, these nodes also wrap a pointer that leads to the data; 

#include <stdio.h>
#include <stdlib.h>

struct DLLNode {
    struct DLLNode* next;
    struct DLLNode* prev;
    void* data;
};

struct DLinkedList {
    unsigned int length;
    struct DLLNode* start;
    struct DLLNode* end;
};

struct DLLNode* DLLnewNode(void* v) {
    struct DLLNode* allocatednode = malloc(sizeof(struct DLLNode));
    allocatednode->prev = NULL;
    allocatednode->next = NULL;
    allocatednode->data = v;

    return allocatednode;
}

//allocates memory for a int and puts it into a node
struct DLLNode* DLLnewNode_withInt(int v) {
    int* allocated = malloc(sizeof(int));
    *allocated = v;
    return DLLnewNode(allocated);
}

void printDLL(struct DLinkedList* l) {
    printf("DoubleLinkedList at %p { len:%u, start:%p, end:%p, \n", l, l->length, l->start, l->end);
    struct DLLNode* n = l->start;
    while (n != NULL) {
        printf("    LinkedListNode at %p { data: %i, prev: %p, next: %p },\n", n, *(int*)n->data, n->prev, n->next);
        n = n->next;
    }
    printf("}\n");
}

struct DLinkedList newDLinkedList() {
    return (struct DLinkedList) {0, NULL, NULL};
}

//this only frees nodes on linkedlist
//freeing data inside linkedlist nodes is user's responsability
int DLLfree(struct DLinkedList* l) {
    if (l->length == 0) {
        return 0;
    }
    struct DLLNode* current = l->start;
    unsigned int frees = 0;
    do {
        struct DLLNode* next = current->next;
        free(current);
        current = next;
        frees++;
    } while (current != NULL);

    l->start = NULL;
    l->end = NULL;
    l->length = 0;
    return frees;
}

struct DLLNode* DLLgetNthNode(struct DLinkedList* list, unsigned int pos) {
    struct DLLNode* current = list->start;
    if (pos >= list->length) {
        return NULL;
    }
    while (pos>0) {
        current = current->next;
        pos--;
    }
    return current;
}

struct DLLNode* DLLappendNode(struct DLinkedList* list, struct DLLNode* n) {
    if (list->length == 0) {
        list->start = n;
    } else {
        struct DLLNode* last = DLLgetNthNode(list, list->length - 1);
        last->next = n;
        n->prev = last;
    }
    list->end = n;
    list->length +=1;
    return n;

}


struct DLLNode* DLLinsertNode(struct DLinkedList* list, unsigned int pos, struct DLLNode* n) {
    if (pos >= list->length) {
        return NULL;
    }
    if (pos == 0) {
        n->next = list->start;
        list->start = n;
        n->next->prev = n;
    } else {
        struct DLLNode* at_pos = DLLgetNthNode(list, pos);
        at_pos->prev->next = n;
        n->next = at_pos;
        n->prev = at_pos->prev;
        at_pos->prev = n;
    }
    list->length += 1; 
    return n;

}

struct DLLNode* DLLpopNode(struct DLinkedList* ll) {
    if (ll->length == 0) {
        return NULL;
    }

    struct DLLNode* n = ll->end;

    if (ll->length == 1) {
        ll->start = NULL;
        ll->end = NULL;
    } else {
        ll->end = n->prev;
        n->prev->next = NULL;
    }

    ll->length--;

    n->next = NULL;
    n->prev = NULL;
    return n;
}

struct DLLNode* DLLremoveNode(struct DLinkedList* ll, unsigned int pos) {
    if (pos >= ll->length) {
        return NULL;
    }
    struct DLLNode* n = DLLgetNthNode(ll, pos);

    if (ll->length == 1) {
        ll->start = NULL;
        ll->end = NULL;
    } else if (pos == 0) {
        ll->start = n->next;
    } else if (pos == ll->length - 1) {\
        n->prev->next = NULL;
        ll->end = n->prev;
    } else {
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }

    ll->length--;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

int testDlinkedList() {
    struct DLinkedList l1 = newDLinkedList();
    DLLappendNode(&l1, DLLnewNode_withInt(2));
    DLLappendNode(&l1, DLLnewNode_withInt(4));
    DLLappendNode(&l1, DLLnewNode_withInt(6));

    DLLinsertNode(&l1, 0, DLLnewNode_withInt(1));
    DLLinsertNode(&l1, 2, DLLnewNode_withInt(3));
    DLLinsertNode(&l1, 4, DLLnewNode_withInt(5));
    
    printDLL(&l1);

    //note allocated data is leaked here
    free(DLLpopNode(&l1)); //removed 6
    free(DLLremoveNode(&l1, 0)); // removed first (1)
    free(DLLremoveNode(&l1, 3)); // removed last (5)
    free(DLLremoveNode(&l1, 1)); // removed in the middle (3)

    printDLL(&l1);

    printf("Nodes freed: %u\n", DLLfree(&l1));

    return 0;
}
