#include <stdio.h>
#include <string.h>

int add(int a, int b) { return a + b; }
void greet(const char *name) { printf("Hello, %s!\n", name); }
int main() { 
    char buffer[12];
    printf("%d\n", add(1, 2)); return 0;
    strcpy(buffer,"fefefd");
    printf("%s\n",buffer);
}