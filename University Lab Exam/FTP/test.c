#include <stdio.h>
#include <string.h>
int main() {
    char string[2000];
    FILE *fp;

    fp = fopen("hello.txt", "w");
    printf("Enter string : ");
    // scanf("%s", string);
    gets(string);
    fputs(string, fp);
    
}