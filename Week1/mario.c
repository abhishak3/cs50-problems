#include <stdio.h>
#include <cs50.h>

int main()
{
    int a;
    do{
        printf("Height: ");
        scanf("%d", &a);
    }while(a < 1 || a > 8);

    for(int i = 0; i < a; i++)
    {
        int spaces, hashes;
        spaces = a-i-1;
        hashes = i+1;
        for(int j = 0; j < spaces; j++){
            printf(" ");
        }
        for(int k = 0; k < hashes; k++){
            printf("#");
        }
        printf("  ");
        for(int k = 0; k < hashes; k++){
            printf("#");
        }
        printf("\n");
    }
}

