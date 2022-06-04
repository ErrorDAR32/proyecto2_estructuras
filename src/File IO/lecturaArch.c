#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include "../hashmap/hashmap.c" 

#define MAX_NAME_SZ 256


char* ReadFile(char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       
       fseek(handler, 0, SEEK_END);     
       string_size = ftell(handler);       
       rewind(handler);       
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );
       read_size = fread(buffer, sizeof(char), string_size, handler);
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           free(buffer);
           buffer = NULL;
       }
       fclose(handler);
    }

    return buffer;
}


int readfiles(char * ruta, struct HashMap h){
	
	DIR *dir = opendir(ruta);
	if (dir == NULL){
		return -1;
	}
	struct dirent *ent;
	while ((ent = readdir(dir)) != NULL) {
		if ((strcmp(ent->d_name, ".") == 0) || (strcmp(ent->d_name, "..") == 0)) {
		  continue;
		}

		//printf("%s \n", ent->d_name);
		char full_filename[1024];
    strcpy(full_filename, ruta);
		strcat(full_filename, ent->d_name);
		char *string = ReadFile(full_filename);
		
		printf("%i\n", HMinsertKeyValue(&h, ent->d_name, string));
		
		
  }

	return 0;
	
	
	
}


//int main()
//{
//  
//	struct HashMap h = HMnewHashMap(8);
//	readfiles("./arch", h);
//   
//    printf("lul");
//    
//    printHashMap(&h);
//
//   
//  return EXIT_SUCCESS;
//}


