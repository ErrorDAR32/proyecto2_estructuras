#include <stdio.h>
#include "hashmap/hashmap.c"
#include "File IO/lecturaArch.c"

void main() {
    printf("Bienvenido al Proyecto 2 De Estructuras de Datos\n");
    printf("Autores: \na \nb \nc");
    printf("\n\n");

    struct HashMap h = HMnewHashMap(8);

    readfiles("./arch", h);

    printf("%i archivos cargados", h.elements);
    printf("Por Favor Escoja Una de las siguientes opciones:\n");
    printf("1: Buscar por nombre de archivo");

}