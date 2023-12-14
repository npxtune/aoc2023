#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#define MAXLINE 500

int32_t get_winning_numbers(FILE *file) {
    char buffer[MAXLINE];
    int32_t length = 0;
    bool is_counting = false;

    if (fgets(buffer, MAXLINE, file) != NULL) {
        for (int32_t i = 0; buffer[i] != '|'; ++i) {
            if (buffer[i] == ':') {
                is_counting = true;
                continue;
            }
            if (isnumber(buffer[i]) && isnumber(buffer[i+1]) && is_counting == true) {
                length++;
                i++;
            } else if (isnumber(buffer[i]) && is_counting == true) {
                length++;
            }
        }
    }
    if (fseek(file, 0L, SEEK_SET) != 0) {
        return -1;
    }
    return length;
}

int32_t get_points(const char *buffer, const int32_t *winning_numbers, int32_t index, int32_t pos) {
    int32_t value = 0;
    for (int i = pos; buffer[i] != '\0'; ++i) {
        if (isnumber(buffer[i])) {
            int32_t local_number = buffer[i] - '0';

            if (isnumber(buffer[i + 1])) {
                local_number = local_number * 10 + buffer[++i] - '0';
            }

            for (int j = 0; j < index; ++j) {
                if (local_number == winning_numbers[j]) {
                    if (value == 0) {
                        value = 1;
                    }
                    value *= 2;
                    break;
                }
            }
        }
    }
    printf("\t\t%d\n", value/2);
    return value/2;
}

int32_t cards_points(FILE *file) {
    int32_t winning_numbers[get_winning_numbers(file)];
    int32_t index = 0, pos = 0, value = 0;
    char buffer[MAXLINE];
    while (fgets(buffer, MAXLINE, file) != NULL) {
        bool is_counting = false;
        for (; pos < MAXLINE && buffer[pos] != '|'; ++pos) {
            if (buffer[pos] == ':') {
                is_counting = true;
                continue;
            }
            if (isnumber(buffer[pos]) && is_counting) {
                int32_t number_length = 1;
                winning_numbers[index] = buffer[pos] - '0';

                if (isnumber(buffer[pos + 1])) {
                    winning_numbers[index] = winning_numbers[index] * 10 + buffer[pos + number_length++] - '0';
                }
                pos+= number_length-1;
                index++;
            }
        }
        for (int i = 0; i < index; ++i) {
            printf("%d ", winning_numbers[i]);
        }
        //printf("\n");
        value += get_points(buffer, winning_numbers, index, pos);
        pos = 0, index = 0;
    }
    return value;
}

int main(void) {
    FILE *file = fopen("../day4/input", "r");
    if (file == NULL) {
        return -1;
    }

    printf("\nTotal points worth: %d\n", cards_points(file));
    fclose(file);
    return 0;
}