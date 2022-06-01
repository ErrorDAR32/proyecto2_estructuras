#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_NAME_SZ 256




struct nodo{
	char *nombre;
	char *texto;
	
	struct nodo* siguiente;
	
	
	
};

struct listaSimple{
	
	struct nodo* inicio;
	
	
};

struct nodo* crearNodo(){
	struct nodo* nn = calloc(1,sizeof(struct nodo));
	return nn;
}


int insertarFinal(struct listaSimple* lista, char * nombre, char *texto){
		if(lista == NULL){
			return -1;
		}
		if(lista->inicio == NULL){
			struct nodo* nuevo = calloc(1, sizeof(struct nodo));
			nuevo->nombre = nombre;
			nuevo->texto = texto;
			lista->inicio = nuevo;
			return 0;
		}
		else{
			struct nodo* tmp = lista->inicio;
			while(tmp->siguiente != NULL){
				tmp = tmp->siguiente;
			}
			tmp->siguiente = crearNodo();
			tmp->siguiente->nombre = nombre;
			tmp->siguiente->texto = texto;
			
		};
		return 0;
};

void imprimir(struct listaSimple* lista){
	if(lista == NULL){
		printf("No existen la lista \n");
	}
	
	if(lista->inicio == NULL){
		printf("No existen elementos \n");
	}
	else{
		struct nodo* tmp = lista->inicio;
		while(tmp->siguiente != NULL){
			
			printf("%s",tmp->nombre);
			printf("\n");
			printf("%s",tmp->texto);
			printf("\n");
			tmp = tmp->siguiente;
		};
		
		printf("%s",tmp->nombre);
		printf("\n");
		printf("%s",tmp->texto);
		printf("\n");
		
	};
	printf("Terminado exitosamente");
	printf("\n");
};

int largo(struct listaSimple* lista){
	int i = 0;
	if(lista == NULL){
		return i;
	}
	
	if(lista->inicio == NULL){
		return i;
	}
	else{
		struct nodo* tmp = lista->inicio;
		while(tmp->siguiente != NULL){
			
			i++;
			tmp = tmp->siguiente;
		};
		
		i++;
		
		
	};
	return i;
	
};		
struct listaSimple* crearLista(){
	struct listaSimple* lista = calloc(1, sizeof(struct listaSimple));
	return lista;
	}


char* ReadFile(char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       // busca el ultumo byte del documento
       fseek(handler, 0, SEEK_END);
       // va del primer al ultimo byte, o sea sizeof
       string_size = ftell(handler);
       // vuelve al inicio del documento
       rewind(handler);

       // crea un string que pueda almacenar todo
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // lee todo en una sola operacion
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // agrega un \0 a la ultima posicion
       // con eso el buffer es ahora un string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // si ocurre un error vuelve el buffer a null
           free(buffer);
           buffer = NULL;
       }

       // cierra el documento
       fclose(handler);
    }

    return buffer;
}






int main()
{
  struct listaSimple *l1 = crearLista();
  
  
  //Con un puntero a DIR abriremos el directorio y Empezaremos a leer en el directorio especificado 
  DIR *dir = opendir("./arch");
  //Miramos que no haya error 
  if (dir == NULL)
    return -1;
  //en ent habrá información sobre el archivo que se está "sacando" a cada momento
  struct dirent *ent;
  //Leyendo uno a uno todos los archivos que hay 
  while ((ent = readdir(dir)) != NULL) {
    if ((strcmp(ent->d_name, ".") == 0) || (strcmp(ent->d_name, "..") == 0)) {
      continue;
    }

    //printf("%s \n", ent->d_name);
    char full_filename[1024] = "./arch/";
    strcat(full_filename, ent->d_name);
    char *string = ReadFile(full_filename);
    
    //printf("%s \n..............................................\n", string);
    
    insertarFinal(l1, ent->d_name, string);
  }

 
   //printf(" \n=================================================================================================================================\n");
   //imprimir(l1);
   //printf("%d \n", largo(l1));
  closedir (dir);

  return EXIT_SUCCESS;
}


