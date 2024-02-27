#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <signal.h>
#include <sys/inotify.h>

#define EXT_SUCCES 0
#define TOO_FEW_ARGS 1
#define ERR_INIT_MODIFY 2
#define ERR_ADD_WATCH 3
#define BASE_PATH_NULL 4
#define ERR_READ_NOTIFY 5

int IeventQueue = -1;
int IeventStatus = -1;
int readLength;
int main(int argc, char** argv)
{
    const uint32_t watchMask = IN_CREATE | IN_DELETE | IN_ACCESS | IN_CLOSE_WRITE | IN_MODIFY | IN_MOVE_SELF;
    char *basePath = NULL;
    char *token = NULL;
    const struct inotify_event* watchEvent;
    char *notificationMessage;



    char buffer[4096];
    if (argc < 2){
        fprintf(stderr,"USAGES : ddaemon PATH\n");
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
    printf("%s\n", basePath);
    IeventQueue = inotify_init();

    if (IeventQueue == -1){
            fprintf(stderr,"Error initializing intofiy instannce \n");
            exit(ERR_INIT_MODIFY);
    }

    IeventStatus = inotify_add_watch(IeventQueue, argv[1], watchMask);
    if (IeventStatus == -1){
            fprintf(stderr,"Error adding file to watch instance");
            exit(ERR_ADD_WATCH);


    }

    while(true){
         readLength = read(IeventQueue, buffer, sizeof(buffer));
            if(readLength == -1){
             exit(ERR_READ_NOTIFY);
         }
         for (char *bufferPointer = buffer; bufferPointer < buffer + readLength; bufferPointer += sizeof(struct inotify_event) + watchEvent->len){
             watchEvent = (const struct inotify_event *) bufferPointer;
             if (watchEvent->mask & IN_CREATE) {
                     notificationMessage = "File created\n";
                 }
             if (watchEvent->mask & IN_DELETE) {
                     notificationMessage = "File deleted\n";
             }
             if (watchEvent->mask & IN_ACCESS ){
                     notificationMessage = "File accessed\n";
             }
             if (watchEvent->mask & IN_CLOSE_WRITE) {
                     notificationMessage = "File writen and closed\n";
                 }
             if (watchEvent->mask & IN_MODIFY) {
                     notificationMessage = "File modified\n";
             }
             if (watchEvent->mask & IN_MOVE_SELF) {
                     notificationMessage = "File moved\n";
             }

             if (notificationMessage == NULL){
                     continue;
             }

             printf("%s\n",notificationMessage);




         }

    }

}
