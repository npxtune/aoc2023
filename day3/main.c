#include <stdio.h>
#include <ctype.h>
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

int32_t part_number_sum(FILE *file) {
    int32_t line_length = get_line_length(file);
    char buffer[MAXLINE], symbol[line_length];
    while (fgets(buffer, MAXLINE, file) != NULL) {
        for (int i = 0; i < line_length; ++i) {
            buffer[i] != PERIOD ? printf("%c", buffer[i]) : 0;
        }
        printf("\n");
    }
    return 0;
}

int main(void) {
    FILE *file = fopen("../day3/input", "r");
    if (file == NULL) {
        printf("Error, can't read file content!\n");
        return -1;
    }

    printf("Sum: %d\n", part_number_sum(file));
    fclose(file);
    return 0;
}