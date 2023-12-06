#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

int64_t check_digits(FILE* ptr) {
    char buffer[MAX];
    int64_t value = 0, digits[2];
    bool first_value = true;

    while (!feof(ptr)) {
        fgets(buffer, MAX, ptr);
        for (int32_t i = 0; i < MAX; i++) {
            if (isdigit(buffer[i])) {   // Check if there is a calibration digit
                if (first_value == true) {
                    digits[0] = buffer[i] - '0';
                    first_value = false;
                }
                digits[1] = buffer[i] - '0';
                } else {    // Check if there is a "character digit"
                    switch (buffer[i]) {
                        case 'o':   // 1
                            if (strncmp(&buffer[i], "one", 3) == 0) {
                                if (first_value == true) {
                                    digits[0] = 1;
                                    first_value = false;
                                }
                                digits[1] = 1;
                            }
                            break;

                        case 't':   // 2, 3
                            if (strncmp(&buffer[i], "two", 3) == 0) {
                                if (first_value == true) {
                                    digits[0] = 2;
                                    first_value = false;
                                }
                                digits[1] = 2;
                            } else if (strncmp(&buffer[i], "three", 5) == 0) {
                                if (first_value == true) {
                                    digits[0] = 3;
                                    first_value = false;
                                }
                                digits[1] = 3;
                            }
                            break;

                        case 'f':   // 4, 5
                            if (strncmp(&buffer[i], "four", 4) == 0) {
                                if (first_value == true) {
                                    digits[0] = 4;
                                    first_value = false;
                                }
                                digits[1] = 4;
                            } else if (strncmp(&buffer[i], "five", 4) == 0) {
                                if (first_value == true) {
                                    digits[0] = 5;
                                    first_value = false;
                                }
                                digits[1] = 5;
                            }
                            break;

                        case 's':   // 6, 7
                            if (strncmp(&buffer[i], "six", 3) == 0) {
                                if (first_value == true) {
                                    digits[0] = 6;
                                    first_value = false;
                                }
                                digits[1] = 6;
                            } else if (strncmp(&buffer[i], "seven", 5) == 0) {
                                if (first_value == true) {
                                    digits[0] = 7;
                                    first_value = false;
                                }
                                digits[1] = 7;
                            }
                            break;

                        case 'e':   // 8
                            if (strncmp(&buffer[i], "eight", 5) == 0) {
                                if (first_value == true) {
                                    digits[0] = 8;
                                    first_value = false;
                                }
                                digits[1] = 8;
                            }
                            break;

                        case 'n':   // 9
                            if (strncmp(&buffer[i], "nine", 4) == 0) {
                                if (first_value == true) {
                                    digits[0] = 9;
                                    first_value = false;
                                }
                                digits[1] = 9;
                            }
                            break;

                        case 'z':   // 0
                            if (strncmp(&buffer[i], "zero", 4) == 0) {
                                if (first_value == true) {
                                    digits[0] = 0;
                                    first_value = false;
                                }
                                digits[1] = 0;
                            }
                            break;

                        default:    // no first char for digit found
                            break;
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
    printf("\n%ld\n", check_digits(ptr));
    fclose(ptr);
    return 0;
}