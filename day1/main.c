#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

typedef struct {
    char* word;
    uint32_t digit;
} lookup_t;

uint32_t check_digits(FILE* ptr, const lookup_t *table) {
    char buffer[MAX];
    uint32_t value = 0, digits[2];
    bool first_value = true;

    while (!feof(ptr)) {
        fgets(buffer, MAX, ptr);
        for (uint32_t i = 0; i < MAX; i++) {
            if (isdigit(buffer[i])) {   // Check if there is a calibration digit
                if (first_value == true) {
                    digits[0] = digittoint(buffer[i]);
                    first_value = false;
                }
                digits[1] = digittoint(buffer[i]);
                } else {    // Check if there is a "character digit"
                    for (uint32_t j = 0; j < 10; j++) {
                        if (strncmp(table[j].word, &buffer[i], strlen(table[j].word)) == 0) {
                            if (first_value == true) {
                                digits[0] = table[j].digit;
                                first_value = false;
                            }
                            digits[1] = table[j].digit;
                            break;
                        }
                    }
            }
            if (buffer[i] == '\n' || buffer[i] == '\0') {
                first_value = true;
                value += digits[0] * 10 + digits[1];
                break;
            }
        }
    }
    return value;
}

int32_t main() {
    FILE* ptr = fopen("input", "r");
    if (NULL == ptr) {
        printf("Error, can't read file content\n");
        return -1;
    }

    const lookup_t table[] = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9},
        {"zero", 0}
    };

    printf("Sum of calibration values: %d\n", check_digits(ptr, table));
    fclose(ptr);
    return 0;
}