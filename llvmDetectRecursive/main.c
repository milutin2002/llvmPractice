#include <stdio.h>

int sum(int n){
    if(n==1){
        return 1;
    }
    printf("%d %d\n",n,n-1);
    int res=sum(n-1);
    printf("%d\n",res);
    return n+sum(n-1);
}

int fakt(int n){
    if(n==1){
        return 1;
    }
    printf("%d %d\n",n,n-1);
    int res=fakt(n-1);
    printf("%d\n",res);
    return n*res;
}


int main(int argc,char *argv[]){
    printf("Hello wordl");
    printf("%d",sum(5));
    printf("%d",fakt(4));
    return 0;
}