#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

int64_t add_values(FILE* ptr) {
    char file_char;
    int64_t value = 0, digits[2];
    bool first_value = true;

    do {
        file_char = fgetc(ptr);
        if (isdigit(file_char)) {
            if (first_value == true) {
                digits[0] = file_char - '0';
                first_value = false;
            }
            digits[1] = file_char - '0';
        }
        if (file_char == '\n') {
            first_value = true;
            value += digits[0] * 10 + digits[1];
        }
    } while (file_char != EOF);
    return value;
}

int32_t main()
{
    FILE* ptr = fopen("document.txt", "r");
    if (NULL == ptr) {
        return -1;
    }
    printf("Sum of calibration values: %ld", add_values(ptr));
    fclose(ptr);
    return 0;
}