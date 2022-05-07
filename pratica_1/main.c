#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "functions.c"

int main(){

    int processes = 0;
    char* commandl = (char*) malloc(sizeof(char) * 4097);

    if(commandl != NULL){

        printf("myshell> ");
        fflush(stdout);

        while(fgets(commandl, 4097, stdin) != NULL) {

            char* words[100];
            int wcount = 0;
            words[wcount] = strtok(commandl, " ");

            while(words[wcount]){
                wcount++;
                words[wcount] = strtok(0, " ");
            }

            words[wcount] = 0;
            words[wcount -1] = removeBreakLine(words[wcount -1]);

            if(strcmp("quit", words[0]) == 0 || strcmp("exit", words[0]) == 0)
                return 0;
            else if(strcmp("start", words[0]) == 0 ){
                if(wcount > 1){
                    processes++;
                    int returnId = start(words, wcount);
                    if(returnId == 0)
                        return 0;
                } else {
                    printf("myshell: o comando start deve possuir argumento(s).\n");
                }
            } else if(strcmp("wait", words[0]) == 0 ){
                waitProcess();
            } else if(strcmp("run", words[0]) == 0 ){

            } else if(strcmp("stop", words[0]) == 0 ){

            } else if(strcmp("continue", words[0]) == 0 ){

            } else {
                if(strlen(words[0]) > 0)
                    printf("myshell: comando desconhecido: %s\n", words[0]);
            }
            free(words[wcount -1]);

            printf("myshell> ");
            fflush(stdout);
        }

        free(commandl);

        return 0;
    } else {
        printf("Houve um problema na alocação de memória.");
    }
   
    
    
    sleep(5);
}



