#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<strings.h>

#define SUCCESS 0
#define TOO_FEW_ARGS 1
#define ERR_INIT_MODIFY 2
#define BASE_PATH_NULL 3
#define FILE_NOT_FOUND 4
int main(int argc, char **argv,char **argd){
    char *basePath = NULL;
    char *token = NULL;
    char *searchParam = NULL;

    char buffer[4096];
    if (argc < 3){
        fprintf(stderr,"USAGES : fileio PATH\n");
        exit(TOO_FEW_ARGS);
    }

    argd = &argv[2];

    basePath = malloc(sizeof(char) * (strlen(argv[1]) + 1 ));
    strcpy(basePath,argv[1]);

    token = strtok(basePath,"/");

    while (token != NULL) {
        basePath = token;
        token = strtok(NULL,"/");
    }

    searchParam = malloc(sizeof(char) * strlen(argd[0] + 1));
    strcpy(searchParam,argd[0]);





    FILE *file = fopen(basePath,"r");
    if (file == NULL){
        printf("%s\n" ,"Error reading file");
        exit(FILE_NOT_FOUND);
    }

    while (fgets(buffer,sizeof(buffer),file)!=NULL){
        if(strstr(buffer,argd[0])){
            printf("%s","FOUND MATCH:");
            printf("%s",buffer);
        }

    }



    fclose(file);
    free(basePath);
    printf("%s\n","Success");
    exit(SUCCESS);

}
