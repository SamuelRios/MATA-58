char* removeBreakLine(char* s) {
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

int start(char** words) {

    errno = 0;
    int pid = fork();
    if(pid == -1){
        int myerrno = errno;
        if(myerrno == 11){
            printf("myshell: erro: recurso temporariamente indisponível. (fork, EAGAIN)\n");
        } else if(myerrno == 12){
            printf("myshell: erro: não foi possível alocar memória. (fork, ENOMEM)");
        } else if(myerrno == 38){
            printf("myshell: erro: função não implementada. (fork, ENOSYS)");
        }     
    } else if(pid ==0){
        char** args = (char**) words+1;
        execvp(args[0],  args);
        return pid;
    }
    if(strcmp("start", words[0]) == 0)
        printf("myshell: processo %d iniciado.\n", pid);
    return pid;
}

void waitProcess() {
    int* wstatus;

    errno = 0;
    int pid = wait(wstatus);

    if(pid == -1){
        int myerrno = errno;
        
        if(myerrno == 10)
            printf("myshell: não há processos restantes.\n");
        else if(myerrno == 11)
             printf("myshell: erro: o descritor de arquivo PID especificado em id não é bloqueante e o processo ao qual ele se refere não foi finalizado. (wait, EAGAIN)\n");
        else if(myerrno == 3)
             printf("myshell: erro: pid é igual a INT_MIN., (wait, ESRCH)");

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

void runprocess(char** words){

    int pid = start(words);

    if(pid > 0){

        int* wstatus;

        errno = 0;  
        int pidreturned = waitpid(pid, wstatus, 0);

        if(pidreturned == -1){
            int myerrno = errno;

            if(myerrno == 10)
                printf("myshell: não há processo filho. (waitpid, ECHILD)\n");
            else if(myerrno == 4)
                printf("myshell: erro: chamada de sistema interrompida. (waitpid, EINTR)\n");
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
}

void killProcess(char* pidString){
    errno = 0;
    int pid = atoi(pidString);
    if(pid != 0 || strcmp("0", pidString) == 0){
        int returnkill = kill(pid, SIGKILL);
        if(returnkill == -1){
            int myerrno = errno;
            if(myerrno == 1)
                printf("myshel: sem permissão para finalizar o processo %d.\n", pid);
            else if(myerrno == 3)
                printf("myshel: o id informado não pertence a nenhum processo.\n");
        } else
            printf("myshell: processo %d foi finalizado.\n", pid);
    } else {
       printf("myshell: id informado é inválido.\n");
    }
}

void stopProcess(char* pidString){
    errno = 0;
    int pid = atoi(pidString);
    if(pid != 0 || strcmp("0", pidString) == 0){
        int returnkill = kill(pid, SIGSTOP);
        if(returnkill == -1){
            int myerrno = errno;
            if(myerrno == 1)
                printf("myshel: sem permissão para suspender o processo %d.\n", pid);
            else if(myerrno == 3)
                printf("myshel: o id informado não pertence a nenhum processo.\n");
        } else
            printf("myshell: processo %d parou a execução.\n", pid);
    } else {
       printf("myshell: id informado é inválido.\n");
    }
}


void continueProcess(char* pidString){
    errno = 0;
    int pid = atoi(pidString);
    if(pid != 0 || strcmp("0", pidString) == 0){
        int returnkill = kill(pid, SIGCONT);
        if(returnkill == -1){
            int myerrno = errno;
            if(myerrno == 1)
                printf("myshel: sem permissão para continuar o processo %d.\n", pid);
            else if(myerrno == 3)
                printf("myshel: o id informado não pertence a nenhum processo.\n");
        } else
            printf("myshell: processo %d voltou a execução.\n", pid);
    } else {
       printf("myshell: id informado é inválido.\n");
    }   
}