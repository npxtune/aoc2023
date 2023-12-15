#include <stdio.h>
#include <ctype.h>
#include "day4.h"
#define MAXLINE 210

match_Tuple get_matches(const char *buffer, const int32_t *winning_num, int32_t index, int32_t pos) {
    match_Tuple matches = {1, 0};
    for (int32_t i = pos; buffer[i] != '\0'; ++i) {
        if (isnumber(buffer[i])) {
            int32_t local_number = buffer[i] - '0';
            if (isnumber(buffer[i + 1])) {
                local_number = local_number * 10 + buffer[++i] - '0';
            }
            for (int32_t j = 0; j < index; ++j) {
                local_number == winning_num[j] ? matches.part1 *= 2 : 0;
                local_number == winning_num[j] ? matches.part2 += 1 : 0;
            }
        }
    }
    if (matches.part1 == 1) {
        matches.part1 = 0;
    }
    matches.part1 /= 2;
    return matches;
}

void check_card(FILE *file) {
    match_Tuple values = {0,0};
    int32_t winning_num[MAXLINE], card_instances[MAXLINE], card = 0;
    clear_array(card_instances, MAXLINE);
    char buffer[MAXLINE];
    for (; fgets(buffer, MAXLINE, file) != NULL; card++) {
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
        match_Tuple matches = get_matches(buffer, winning_num, index, pos);
        values.part1 += matches.part1;
        for (int32_t i = card+1; i < card+matches.part2+1; ++i) {
            card_instances[i] += card_instances[card]+1;
        }
        values.part2 += card_instances[card]+1;
    }
    printf("Part1: %d\nPart2: %d\n", values.part1, values.part2);
}

int main(void) {
    FILE *file = fopen("../day4/input", "r");
    if (file == NULL) {
        return -1;
    }
    check_card(file);
    fclose(file);
    return 0;
}