#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define EXT_SUCCESS 0
#define TOO_FEW_ARGS 1
#define ERR_INIT_MODIFY 2
#define BASE_PATH_NULL 3
#define FILE_NOT_FOUND 4

int main(int argc, char **argv){
    bool escape = false;
    char *basePath = NULL;
    char *token = NULL;


    char buffer[4096];
    if (argc < 2){
        fprintf(stderr,"USAGES : fileio PATH\n");
        exit(TOO_FEW_ARGS);
    }

    basePath = (char *)malloc((sizeof(char) *(strlen(argv[1]) + 1 )));
    strcpy(basePath,argv[1]);
    token = strtok(basePath,"/");
    while (token != NULL) {
        basePath = token;
        token = strtok(NULL,"/");
    }

    if (basePath == NULL){
        fprintf(stderr,"Error getting base path \n");
        exit(BASE_PATH_NULL);
    }

    if (access(basePath, W_OK)){
        printf("%s\n","File found and writable!");
    }

    FILE *file = fopen(basePath,"r");
    if (file == NULL){
        printf("%s\n" ,"Error reading file");
        exit(FILE_NOT_FOUND);
    }

    while (fgets(buffer,sizeof(buffer),file)!=NULL){
        printf("%s",buffer);
        fputs(buffer,file);

    }

    fclose(file);

    return EXT_SUCCESS;
}
