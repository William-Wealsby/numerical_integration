#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

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


int main() {
    double total;
    total = trapezium(0,1,10,*f);
    printf("integral = %f \n", total);




    return 0;
}

