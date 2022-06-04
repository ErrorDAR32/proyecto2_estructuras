#include "../hashmap/hashmap.c"

char** search(struct HashMap h, char* substring){
    if(strlen(substring) == 0){
        return NULL;
    }

    char** result = malloc(sizeof(char*)*h.elements);
    int counter = 0;
    
    for(int i = 0; i < h.capacity; i++){
        if(search_string(h.Buckets[i].value, substring) == 1){
            result[counter] = h.Buckets[i].value;
            counter++;
        }
    }

    if(counter == 0){
        return NULL;
    }
    
    return result;
}


int search_string(char* string, char* substring){
    if(strlen(substring) == 0){
        return 0;
    }
    
    for(int i = 0; i < strlen(string); i++){
        if(string[i] == substring[0]){

            for(int j = 0; j < strlen(substring); j++){
                if(string[i+j] != substring[j]){
                    return 0;
                }
            }
            
            return 1;
        }
    }
    
    return 0;
}
