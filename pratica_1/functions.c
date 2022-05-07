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

void start(char** words, int wcount){
    errno = 0;
    int pid = fork();
    if(pid == -1){

    } else if(pid ==0){
        sleep(10);
        char** args;
        if(wcount > 2)
            args = (char**) words+1;
        execvp(args[0],  args);
    }
}

void waitProcess(){
    int* wstatus;

    errno = 0;
    int pid = wait(wstatus);

    if(pid == -1){
        int myerrno = errno;
        
        if(myerrno == 10)
            printf("myshell: não há processos restantes.\n");
        else if(myerrno == 11)
             printf("myshell: O descritor de arquivo PID especificado em id não é bloqueante e o processo ao qual ele se refere não foi finalizado.\n");
        else if(myerrno == 3)
             printf("myshell: pid é igual a INT_MIN.");

    } else {
        if(!WIFEXITED(*wstatus)){

            if(WIFSIGNALED(*wstatus)){
                printf("myshell: processo %d finalizou de forma anormal com sinal %d: %s.\n", pid, WTERMSIG(*wstatus), strsignal(WTERMSIG(*wstatus)));
            }
            
        } else {
            printf("myshell: processo %d finalizou normalmente com status %d.\n", pid, WEXITSTATUS(*wstatus));
        }
    }
}


void run(){

}

void stop(){

}

void continueProcess(){

}