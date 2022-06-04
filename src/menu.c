#include <stdio.h>
#include "hashmap/hashmap.c"
#include "File IO/lecturaArch.c"
#include "Search/Search.c"

void main() {
    printf("Bienvenido al Proyecto 2 De Estructuras de Datos\n");
    printf("Autores: \na \nb \nc");
    printf("\n\n");

    struct HashMap h = HMnewHashMap(8);


    readfiles("./arch/", &h);

    printf("%i\n", search_string("hola asd ASD", "asd"));

    //printHashMap(&h);

    printf("%lu archivos cargados\n", h.elements);

    //printf("%s", HMgetValue(&h, "EXTRA_01-2019,_10_ENE_21-05-2019_07_53_17.pdf.txt"));

    while (true) {
        printf("Por Favor Escoja Una de las siguientes opciones:\n");
        printf("1: Buscar por nombre de archivo\n");
        printf("2: Buscar por fragmento de texto\n");
        printf(">>> ");

        char* buff[1024];

        scanf("%s", &buff);
        char* buff2[1024];

        if (strcmp(buff, "1") == 0) {
            printf("Ingrese el nombre del archivo: ");
            scanf("%s", &buff2);
            void* v = HMgetValue(&h, buff2);
            if (v == NULL) {
                printf("No se encontro el archivo\n");
            } else {
                printf("%s\n", v);
            }

        } else if (strcmp(buff, "2") == 0) {
            printf("Ingrese el fragmento de texto: ");
            scanf("%s", &buff2);
            printf("buff2: %s\n", buff2);
            char** ks = search(&h, buff2);

            if (ks == NULL) {
                printf("No se encontro el fragmento\n");
            } else {
                for (int i = 0; i<h.elements; i++) {
                    printf("%s\n", ks[i]);
                }
            }

        } else {
            printf("Opcion no valida\n");
        }
    }

}