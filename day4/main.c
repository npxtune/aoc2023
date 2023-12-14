#include <stdio.h>
#include <ctype.h>
#define MAXLINE 200

int32_t get_matches(const char *buffer, const int32_t *winning_num, int32_t index, int32_t pos) {
    int32_t value = 1;
    for (int32_t i = pos; buffer[i] != '\0'; ++i) {
        if (isnumber(buffer[i])) {
            int32_t local_number = buffer[i] - '0';
            if (isnumber(buffer[i + 1])) {
                local_number = local_number * 10 + buffer[++i] - '0';
            }
            for (int j = 0; j < index; ++j) {
                local_number == winning_num[j] ? value *= 2 : 0;
            }
        }
    }
    if (value == 1) {
        return 0;
    }
    return value/2;
}

int32_t check_card(FILE *file) {
    int32_t winning_num[MAXLINE / 2], value = 0;
    char buffer[MAXLINE];
    while (fgets(buffer, MAXLINE, file) != NULL) {
        int32_t index = 0, pos = 8;
        for (; pos < MAXLINE && buffer[pos] != '|'; ++pos) {
            if (isnumber(buffer[pos])) {
                int32_t length = 1;
                winning_num[index] = buffer[pos] - '0';

                if (isnumber(buffer[pos + 1])) {
                    winning_num[index] = winning_num[index] * 10 + buffer[pos + length++] - '0';
                }
                pos+= length - 1;
                index++;
            }
        }
        value += get_matches(buffer, winning_num, index, pos);
    }
    return value;
}

int main(void) {
    FILE *file = fopen("../day4/input", "r");
    if (file == NULL) {
        return -1;
    }
    printf("\nPart 1: %d\n", check_card(file));
    fclose(file);
    return 0;
}