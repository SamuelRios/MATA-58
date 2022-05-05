#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* removeBreakLine(char* s){
    int length = (int)strlen(s);
    if(s[length-1] == '\n') {
        char* copy = malloc(sizeof(char) * length);
        if(copy){
            for(int i=0; i<length-1; i++){
                copy[i] = s[i];
            }
            return copy;
        } else return NULL;
    } else return s;
}

int main(){

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

            // if(!words[wcount -1])
            //     exit(0);

            if(strcmp("quit", words[0]) == 0 || strcmp("exit", words[0]) == 0)
                return 0;
            else if(strcmp("start", words[0]) == 0 ){
                
            } else if(strcmp("wait", words[0]) == 0 ){

            } else if(strcmp("run", words[0]) == 0 ){

            } else if(strcmp("stop", words[0]) == 0 ){

            } else if(strcmp("continue", words[0]) == 0 ){

            } else printf("myshell: comando desconhecido: %s\n\n", words[0]);
            
            printf("myshell> ");
            fflush(stdout);
        }
        free(commandl);
    }
   
    
    
    sleep(5);
}



