#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX_NAME_SZ 256


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

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
       // Seek the last byte of the file
       fseek(handler, 0, SEEK_END);
       // Offset from the first to the last byte, or in other words, filesize
       string_size = ftell(handler);
       // go back to the start of the file
       rewind(handler);

       // Allocate a string that can hold it all
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;
       }

       // Always remember to close the file.
       fclose(handler);
    }

    return buffer;
}

/*


int main(){
	
	
    
    struct listaSimple *l1 = crearLista();
    
    FILE *archivo = fopen("archivo.txt", "r"); // Modo lectura
	   
	      // Aquí vamos a ir almacenando cada línea
	int i = 1;
	char texto[1000]; 
    while (fgets(texto, 1000, archivo))
    {
        // Aquí, justo ahora, tenemos ya la línea. Le vamos a remover el salto
        strtok(texto, "\n");
       
      
        char *str = malloc(sizeof(texto));
        memcpy(str, texto, sizeof(texto));
        insertarFinal(l1, str);
        
        i++;
    }
    
    
    imprimir(l1);
	return 0;
	
};*/




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

 
   printf(" \n=================================================================================================================================\n");
   //imprimir(l1);
   printf("%d \n", largo(l1));
  closedir (dir);

  return EXIT_SUCCESS;
}


