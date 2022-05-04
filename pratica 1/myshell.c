#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){

    char* commandl = (char*) malloc(sizeof(char) * 4097);

    if(commandl != NULL){

        printf("myshell> ");
        fflush(stdout);

        while(fgets(commandl, 4097, stdin) != NULL){

            printf("%s", commandl);
            printf("%d\n", (int)strlen(commandl));  

            char* words[100];
            int wcount = 0;
            words[wcount] = strtok(commandl, " ");
            while(wcount < 100 && words[wcount]){
                printf("%s\n", words[wcount] );
                words[wcount] = strtok(NULL, " ");
                wcount++;
            }
            printf("myshell> ");
            fflush(stdout);
        }
        free(commandl);
    }
   
    
    
    sleep(5);
}