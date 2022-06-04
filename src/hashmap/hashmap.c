//hashmap strings as keys, references as mapped values
// uses linked lists as buckets for collisions
//doubles in capacity when load factor is reached
// data is wrapped in "HashMapNode"s, these nodes also contain 
//information for the workings of the hashmap
#include <stdio.h>
#include <stdlib.h>

#ifndef HASHMAP_H
#define HASHMAP_H

//Nodo de la tabla de hash
struct HashMapNode {
    unsigned long hash;
    char* key;
    void* value;
};

//Struct de la tabla de hash
struct HashMap {
    float loadFactor;
    struct HashMapNode *Buckets;
    unsigned long elements;
    unsigned long capacity;
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

    hmap.Buckets = calloc(sizeof(struct HashMapNode), cap);


    //inicializacion de los nodos de la tabla de hash
    for (int i=0; i<hmap.capacity; i++) {
        hmap.Buckets[i].hash = 0;
        hmap.Buckets[i].key = NULL;
        hmap.Buckets[i].value = NULL;
    }

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

        struct HashMapNode *hn = (struct HashMapNode*) &hmap->Buckets[i];
        printf("\n    hmapNode at %p {,\n", hn);

        if (hn->key != NULL) {
            printf("        key: %s,\n", hn->key);
        } else {
            printf("        key: NULL,\n");
        }

        if (hn->value != NULL) {
            printf("        value: %p,\n", hn->value);
        } else {
            printf("        value: NULL,\n");
        }
        printf(  "        hash: %lu ,\n",hn->hash);
        printf(  "    },\n");
        
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
        struct HashMapNode *n = &hmap->Buckets[i];

        HMinsertNode(&newhmap, n);
    }

    free(hmap->Buckets);
    *hmap = newhmap;
    return 0;
}

int HMinsertNode(struct HashMap *hmap, struct HashMapNode *newhn) {
    if ((hmap->elements / hmap->capacity)>=0.75) {
        HMresize(hmap);
    }


    unsigned long pos = newhn->hash % hmap->capacity;

    struct HashMapNode *hn = &hmap->Buckets[pos];
    
    // in case of collisions
    unsigned int count = 0;
    while (count < hmap->capacity) { //avoid infinite wraparound in case of no match
        if (hn->hash == newhn->hash) {
            return -1;
        }
        if (hn->key == NULL) {
            printf("inserting key %s at %lu, %p\n", newhn->key, pos, newhn);
            *hn = *newhn;
            hmap->elements++;
            printHashMap(hmap);
            return 0;
        }

        pos = (pos+1) % hmap->capacity;
        hn = &hmap->Buckets[pos];
    }
    
    return -1;
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
    struct HashMapNode *hn = &hmap->Buckets[pos];

    unsigned int count = 0;
    while (count < hmap->capacity) { //avoid infinite wraparound in case of no match
        if (hn->hash == hash) {
            return hn->value;
        }

        pos = pos+1 % hmap->capacity;
        hn = &hmap->Buckets[pos];
        count++;
    }
    return NULL;
}

//funcion de borrado segun llave
void* HMremoveValue(struct HashMap *hmap,char *k) {
    unsigned long hash = djb2_hash(k);
    unsigned long pos = hash % hmap->capacity;
    struct HashMapNode *hn = &hmap->Buckets[pos];

     unsigned int count = 0;
    while (count < hmap->capacity) { //avoid infinite wraparound in case of no match
        if (hn->hash == hash) {
            hn->hash == 0;
            hn->key = NULL;
            void* v = hn->value;
            hn->value = NULL;
            return v;
        }

        pos = pos+1 % hmap->capacity;
        hn = &hmap->Buckets[pos];
        count++;
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

//int main() {
//    testHM();
//   return 0;
//}

#endif