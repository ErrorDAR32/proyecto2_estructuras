//hashmap strings as keys, references as mapped values
// uses linked lists as buckets for collisions
//doubles in capacity when load factor is reached
// data is wrapped in "HashMapNode"s, these nodes also contain 
//information for the workings of the hashmap
#include "doublell.c"

//Struct de la tabla de hash
struct HashMap {
    float loadFactor;
    struct DLinkedList *Buckets;
    unsigned long elements;
    unsigned long capacity;
};


//Nodo de la tabla de hash
struct HashMapNode {
    unsigned long hash;
    char* key;
    void* value;
};


//djb2
//Funcion de hash
unsigned long djb2_hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while (*str++ != '\0') {
        c = *str;
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}


//Constructor de la tabla de hash
struct HashMap HMnewHashMap(unsigned long cap) {
	//factor de carga estandar = 75%
    struct HashMap hmap = 
    {
        0.75,
        NULL,
        0,
        cap,
    };

    struct DLinkedList *dll = calloc(hmap.capacity, sizeof(struct DLinkedList));

    //inicializacion de los nodos de la tabla de hash
    for (int i=0; i<hmap.capacity; i++) {
        dll[i] = newDLinkedList();
    }

    hmap.Buckets = dll;

    return hmap;
}

//Funcion de impresion de la tabla de hash
void printHashMap(struct HashMap *hmap) {
    printf("HashMap at %p: {", hmap);
    printf(" loadFactor: %f,", hmap->loadFactor);
    printf(" elements: %lu, ", hmap->elements);
    printf(" capacity: %lu, ", hmap->capacity);
    printf(" buckets: {\n");
    for (int i=0; i<hmap->capacity; i++) {
        struct DLinkedList *l = &hmap->Buckets[i];
        printf("    %i: DoubleLinkedList at %p { len:%u, start:%p, end:%p, ", i,  l, l->length, l->start, l->end);
        struct DLLNode* n = l->start;

        int once = 0;
        while (n != NULL) {
            once = 1;
            printf("\n            LinkedListNode at %p {prev: %p, next: %p, hmapNode at %p {,\n", n, n->prev, n->next, n->data);

            struct HashMapNode *hn = (struct HashMapNode*) n->data;
            printf("                 key: %s ,\n", hn->key);
            printf("                 value at %p ,\n",hn->value);
            printf("                 hash: %lu ,\n",hn->hash);
            printf("            },\n");
            n = n->next;
        }

        if(!once) {
            printf("}\n");
        } else {
            printf("\n    }\n");
        }
        
    }
    printf("}\n");
}

//Insertar nodo a la tabla de hash
int HMinsertNode(struct HashMap *hmap, struct HashMapNode *newhn);

// reconstructs the hashmap when the load factor is reached
// duplicates capacity
int HMresize(struct HashMap *hmap) {
    struct HashMap newhmap = HMnewHashMap(hmap->capacity*2);

    for(int i=0; i<hmap->capacity; i++) {
        struct DLinkedList *l = &hmap->Buckets[i];

        struct DLLNode* n = l->start;

        while (n != NULL) {
            HMinsertNode(&newhmap, (struct HashMapNode*)n->data);
            n = n->next;
        }
        //deallocates all nodes in list without touching data refs inside;
        DLLfree(l);

    }
    free(hmap->Buckets);
    *hmap = newhmap;
    
    return 0;
}

int HMinsertNode(struct HashMap *hmap, struct HashMapNode *newhn) {
    if ((hmap->elements / hmap->capacity)>=0.75) {

        HMresize(hmap);
    }


    unsigned long position = newhn->hash % hmap->capacity;

    struct DLLNode *n = hmap->Buckets[position].start;
    
    // in case of collisions
    while (n != NULL) {
        struct HashMapNode *hn = (struct HashMapNode*) n->data;
        
        if (hn->hash == newhn->hash) {
            return -1;
        }
        n = n->next;
    }
    hmap->elements++;
    DLLappendNode(&hmap->Buckets[position], DLLnewNode(newhn));
    return 0;


} 

int HMinsertKeyValue(struct HashMap *hmap,char *k,void *v) {
    struct HashMapNode *newhn = malloc(sizeof(struct HashMapNode));
    newhn->key = k;
    newhn->value = v;
    newhn->hash = djb2_hash(k);

    return HMinsertNode(hmap, newhn);
}

//metodo accesor de la tabla
void* HMgetValue(struct HashMap *hmap, char *k) {
    unsigned long hash = djb2_hash(k);
    unsigned long pos = hash % hmap->capacity;
    struct DLinkedList *l = &hmap->Buckets[pos];

    if (l->start == NULL) {
        return NULL;
    }

    struct DLLNode *n = l->start;
    while (n!=NULL)
    {
        struct HashMapNode *hmn = (struct HashMapNode*) n->data;
        if(hmn->hash == hash) {
            return hmn->value;
        }
        n = n->next;
    }
    return NULL;
    
}

//funcion de borrado segun llave
void* HMremoveValue(struct HashMap *hmap,char *k) {
    unsigned long hash = djb2_hash(k);
    unsigned long pos = hash % hmap->capacity;
    struct DLinkedList * l = &hmap->Buckets[pos];

    if (l->start == NULL) {
        return NULL;
    }

    struct DLLNode *n = l->start;
    int i = 0;
    while (n!=NULL)
    {
        struct HashMapNode *hmn = (struct HashMapNode*) n->data;
        if(hmn->hash == hash) {
            void* val = hmn->value;
            free(hmn);
            free(DLLremoveNode(l,i));
            return val;
        }
        i++;
        n = n->next;
    }
    return NULL;

}


//prueba de la tabla de hash, funcion experimental
int testHM() {
    struct HashMap h = HMnewHashMap(1);
    printHashMap(&h);

    HMinsertKeyValue(&h, "asd", "lul");

    //same key, not inserted
    HMinsertKeyValue(&h, "asd", "lul");
    printf("\n\n\n\n\n\n\n");
    printHashMap(&h);

    //inserted
    HMinsertKeyValue(&h, "relul", "niceee");
    printf("\n\n\n\n\n\n\n");
    printHashMap(&h);

    //not removed
    HMremoveValue(&h, "ccp");
    printf("\n\n\n\n\n\n\n");
    printHashMap(&h);

    //removed
    HMremoveValue(&h, "asd");
    printf("\n\n\n\n\n\n\n");
    printHashMap(&h);
    

    //get returns address of data
    printf("%p\n", HMgetValue(&h, "relul"));

    //get, returns null
    printf("%p\n", HMgetValue(&h, "cpp"));

    return 0;
}
