#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>

typedef double(*fx)(double); 

double f (double x){
return x*x;
}

double trapezium (double start, double end, int segments, fx fun){
    double total = 0;
    double delta = (end-start)/segments;
    for (int i=1;i<segments;i++){
        total += fun(i*delta+start);
    }     
    total *= 2;
    total += fun(start);
    total += fun(end);
    total *= delta/2; 
    return total;
}

double trapezium_mp (double start, double end, int segments, fx fun, int processes){
    double total = 0;
    int status = 0;
    double buf;
    double delta = (end-start)/(processes);
    int pipefd[processes][2];
    segments /= processes;
    // use main process to manage forks, each fork runs
    for (int i=0;i<processes;i++){
        pipe(pipefd[i]);
        pid_t pid = fork();
        if (pid<0){
            printf("FORK ERROR");
            exit(1);
        }
        if (pid==0){
            close(pipefd[i][0]);
            buf = trapezium(start+i*delta, start+(i+1)*delta, segments, fun);
            write(pipefd[i][1],&buf,sizeof(buf));
            exit(0);
        }
        // close write end of pipe i for main process
        close(pipefd[i][1]);    
    }
    wait(&status);    
    for (int i=0;i<processes;i++){
        read(pipefd[i][0],&buf,sizeof(buf));
        total += buf;
    }
    return total;
}


int main() {
    double total;
    double total2;
    total2 = trapezium_mp(0,1,100,*f,3);
    total = trapezium(0,1,100,*f);
    printf("trapezium: %f\n",total2);


    return 0;
}

