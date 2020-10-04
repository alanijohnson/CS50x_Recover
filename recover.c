#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    //input checking
    if (argc != 2) {
        printf("The program requires two arguments. Program filename.\n");
        return 1;
    }

    //file cannot be read
    FILE *file = fopen(argv[1], "r");
    if (file == NULL){
        printf("File could not be opened\n");
        return 1;
    }

    //start program
    int endReached = 0;
    int fileCount = 0;
    BYTE buffer[512];
    int i = 0;
    FILE *image = NULL;
    char fname[7];


    int num = fread(&buffer, sizeof(BYTE), 512, file);
    while( num >= 512 ){
        //jpeg identified
        if( buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef){
            if(image != NULL){
                fclose(image);
            }

            sprintf(fname, "%03i.jpg", fileCount++);
            image = fopen(fname,"w");
        }

        if (image != NULL){
            fwrite(&buffer, sizeof(BYTE), 512, image);
        }

        //printf("%i %i %i\n",i,fileCount,num);
        i++;
        num = fread(&buffer, sizeof(BYTE), 512, file);
        //printf("%i\n",num);
    };

    fread(&buffer, sizeof(BYTE), num, file);
    fclose(image);



}
