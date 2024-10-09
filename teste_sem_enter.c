#include <stdio.h>
#include <conio.h>

int main() {

    char input;

    while(1) {
        input = getch();
        fflush(stdin);
        printf("Você precionou a tecla %c\n", input);
    }
    
    return 0;
}