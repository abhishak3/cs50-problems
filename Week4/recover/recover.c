#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Invalid Number of arguments
    if(argc != 2){
        printf("USAGE: ./recover IMAGE");
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    // File Opening Failed
    if(input == NULL){
        printf("Can't open image: %s", argv[1]);
        return 1;
    }

    FILE* output = fopen("delete_this", "w");
    char signature[7]; signature[6] = '\0';
    char filename[8]; filename[7] = '\0';
    uint8_t block[BLOCK_SIZE];
    int i = 0; // file counter

    while(fread(block, BLOCK_SIZE, 1, input)){
        sprintf(signature, "%x%x%x",block[0],block[1],block[2]); // signature format
        sprintf(filename, "%03i.jpg",i); // filename format

        //if signature found
        if(!strcmp(signature, "ffd8ff")){
            if(block[3] >= 0xe0 && block[3] <= 0xef){
                fclose(output);
                output = fopen(filename, "w"); //opening new .jpg file
                i++; // increasing file counter
            }
        }

        //writing block to jpeg
        fwrite(block, 512, 1, output);
    }
}
