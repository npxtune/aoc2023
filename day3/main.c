#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 100
#define PERIOD '.'

int32_t get_line_length(FILE *file) {
    char buffer[MAXLINE];
    int32_t length = 0;
    if (fgets(buffer, MAXLINE, file) != NULL) {
        while (buffer[length] != '\0' && buffer[length] != '\n') {
            length++;
        }
    }
    if (fseek(file, 0L, SEEK_SET) != 0) {
        return -1;
    }
    return length;
}

int32_t check_part() {
    int32_t output = 0;

    return output;
}

int32_t part_number_sum(FILE *file) {
    int32_t line_length = get_line_length(file);
    char buffer[MAXLINE];
    fgets(buffer, MAXLINE, file);
    fgets(buffer, MAXLINE, file);
    for (int i = 0; i < line_length; ++i) {
        if (!isnumber(buffer[i]) && buffer[i] != '.') {
            printf("\t%c\n", buffer[i]);
            fseek(file, 0+i-1, SEEK_SET);
            printf("%c\t%c\t%c\n", fgetc(file),fgetc(file),fgetc(file));
            fseek(file, (line_length+1)*2+i-1, SEEK_SET);
            printf("%c\t%c\t%c\n", fgetc(file),fgetc(file),fgetc(file));
            break;
        }
    }
    return 0;
}
//    while (fgets(buffer, MAXLINE, file) != NULL) {
//        for (int i = 0; i < line_length; ++i) {
//            if (!isnumber(buffer[i]) && buffer[i] != '.') {
//                printf("%c\n", buffer[i]);
//            }
//        }
//    }
//    return 0;
//}

int main(void) {
    FILE *file = fopen("../day3/input", "r");
    if (file == NULL) {
        printf("Error, can't read file content!\n");
        return -1;
    }

    printf("\nSum: %d\n", part_number_sum(file));
    fclose(file);
    return 0;
}