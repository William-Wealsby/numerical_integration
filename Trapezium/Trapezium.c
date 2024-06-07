#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

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
    double delta = (end-start)/(processes);
    // use main process to manage forks, each fork runs
    for (int i=0;i<processes;i++){
        pid_t pid = fork();
        if (pid<0){
            printf("FORK ERROR");
            exit(1);
        }
        if (pid==0){
            printf("\n start %f:", start+i*delta);
            printf("\n end %f:", start+(i+1)*delta);
            total = trapezium(start+i*delta, start+(i+1)*delta, segments, fun);
            printf("\n total = %f", total);
            exit(0);
        }
    }
    printf("\n mp: %f", total);
    wait(&status);    
    return total;
}


int main() {
    double total;
    total = trapezium_mp(0,1,10,*f,3);
    total = trapezium(0,1,10,*f);
    printf("\n trapezium: %f",total);
    printf("\n");


    return 0;
}

