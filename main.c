#include <stdio.h>
#include <malloc.h>
#include "header.h"
#include "math.h"
#include <string.h>
#include <libgen.h>

int main(int argc, char *argv[]) {
    if (argc==2) {
        printf("Sciezka do pliku - %s\n", argv[1]);

        unsigned long width = 0;
        unsigned long height = 0;
        unsigned long offset = 0;

        FILE *file = fopen(argv[1], "rb");

        long filesize;

        fseek(file, 0, SEEK_END);
        filesize = ftell(file);
        rewind(file);
        char *fileContent = (char*)malloc((filesize+1)*sizeof(char));

        if (fileContent == NULL) {
            printf("Problem z alokacją pamięci!");
            getchar();
            return 1;
        }

        if (file == NULL) {
            free(fileContent);
            printf("Nie znaleziono pliku!");
            getchar();
            return 2;
        }

        for(int i = 0; i < filesize; i++) {
            fread(fileContent+i, 1, 1, file);
        }

        fclose(file);

        printf("Rozmiar pliku %.2fMB\n", (float)((float)filesize/(float)1000000));

        union fourBytes o_union;
        o_union.b[0] = fileContent[10];
        o_union.b[1] = fileContent[11];
        o_union.b[2] = fileContent[12];
        o_union.b[3] = fileContent[13];

        union fourBytes w_union;
        w_union.b[0] = fileContent[18];
        w_union.b[1] = fileContent[19];
        w_union.b[2] = fileContent[20];
        w_union.b[3] = fileContent[21];

        union fourBytes h_union;
        h_union.b[0] = fileContent[22];
        h_union.b[1] = fileContent[23];
        h_union.b[2] = fileContent[24];
        h_union.b[3] = fileContent[25];

        offset = o_union.l;
        width = w_union.l;
        height = h_union.l;

        printf("Rozmiar: %dx%d, offset: %d\n", width, height, offset);

        FILE *negativeFile = fopen("negative.bmp", "wb");

        if (negativeFile == NULL) {
            printf("Problem z utworzeniem pliku!");
            free(fileContent);
            getchar();
            return 3;
        }

        for (int i=0; i<filesize; i++) {
            if (i < offset) {
                fputc(fileContent[i], negativeFile);
            } else {
                fputc(negativeValue(fileContent[i]), negativeFile);
            }
        }

        fputc(EOF, negativeFile);
        fclose(negativeFile);
        printf("Zapisano negatyw do pliku \"negative.bmp\"");

        free(fileContent);

    } else {
        printf("Podaj jeden parametr - sciezke do pliku!");
        getchar();
        return 4;
    }

    return 0;
}

unsigned char negativeValue(unsigned char c) {
    return (c > 128 ? 128 - abs(c - 127) : 127 + abs(c - 127))%256;
}

