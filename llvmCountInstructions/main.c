#include <stdio.h>

int add(int a,int b){
    return a+b;
}

void greet(char *s){
    printf("%s",s);
}

int main(){
    greet("feddffd");
    printf("%d",add(3,4));
}