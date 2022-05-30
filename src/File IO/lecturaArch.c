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


/* Función para devolver un error en caso de que ocurra */
void error(const char *s);
/* Función que hace algo con un archivo */
void procesoArchivo(char *archivo, struct listaSimple* lista);

int main()
{
  struct listaSimple *l1 = crearLista();
  /* Con un puntero a DIR abriremos el directorio */
  DIR *dir;
  /* en ent habrá información sobre el archivo que se está "sacando" a cada momento*/
  struct dirent *ent;

  /* Empezaremos a leer en el directorio actual */
  dir = opendir("./arch");
  //char texto[10000]; 
  /* Miramos que no haya error */
  if (dir == NULL)
    error("No puedo abrir el directorio");
	
  /* Una vez nos aseguramos de que no hay error, ¡vamos a jugar! */
  /* Leyendo uno a uno todos los archivos que hay */
  while ((ent = readdir (dir)) != NULL)
    {
      if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) )
    {
		printf("%s \n",ent->d_name);
		
		//FILE *fich;
	
		//fich=fopen(ent->d_name, "r");
		//if(fich){
			char texto[10000]; 
			//char texto2[20000]; 
			
			char *str2 = ent->d_name;
			//memcpy(str2, ent->d_name, sizeof(texto));
			//printf("%s \n",str2);
			//while (fgets(texto, 1000, fich))
			//{
				
				//strcat(strcpy(texto2, texto2), texto);
				
				
			//}
			//char *str = malloc(sizeof(texto));
			//memcpy(str, texto2, sizeof(texto));
			//fclose(fich);
			char *string = ReadFile(str2);
			//printf("%s \n",str2);
			insertarFinal(l1, str2, string);
			//printf("\n hhhhhhhhhhhhhh \n");
			
			//printf("%s \n",str2);
			
			//procesoArchivo(ent->d_name, l1);
		//}
		//else{printf("No entro \n");}
	}
    }
   imprimir(l1);
  closedir (dir);

  return EXIT_SUCCESS;
}

void error(const char *s)
{
  /* perror() devuelve la cadena S y el error (en cadena de caracteres) que tenga errno */
  perror (s);
  exit(EXIT_FAILURE);
}

void procesoArchivo(char *archivo, struct listaSimple* lista)
{
	  /* Para "procesar", o al menos, hacer algo con el archivo, vamos a decir su tamaño en bytes* /
	  / para ello haremos lo que vemos aquí: https://poesiabinaria.net/2010/04/tamano-de-un-fichero-en-c/ */
	FILE *fich;
	long ftam;
	
	//fich=fopen(archivo, "r");
	char texto[100000]  = " ";; 
	char texto2[200000]  = " ";; 
	//if (fich)
		//{
		//fseek(fich, 0L, SEEK_END);
		//ftam=ftell(fich);
		
		char *string = ReadFile(archivo);
		
		char *str2 = malloc(sizeof(texto));
		memcpy(str2, archivo, sizeof(texto));
		 //while (fgets(texto, 100000, fich))
		//{
			
			//strcat(strcpy(texto2, texto2), texto);
			
			
		//}
		
		
		//char *str = malloc(sizeof(texto));
		//memcpy(str, texto2, sizeof(texto));
		
		
		
		insertarFinal(lista, str2, string);
		
		//}
	//else
    /* Si ha pasado algo, sólo decimos el nombre */
    //printf ("%30s (No info.)\n", archivo);
    
    fclose(fich);
}
