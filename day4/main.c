#include <stdio.h>
#include <ctype.h>
#include "day4.h"
#define ARRAY_LENGTH 210
#define START_POSITION 8

match_Tuple compare_numbers(const char *buffer, const int32_t *winning_num, int32_t index, int32_t pos) {
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

match_Tuple get_matches(const char *buffer) {
    int32_t winning_num[ARRAY_LENGTH], index = 0, pos = START_POSITION;
    for (; pos < ARRAY_LENGTH && buffer[pos] != '|'; ++pos) {
        if (isnumber(buffer[pos])) {
            winning_num[index++] = buffer[pos] - '0';
            if (isnumber(buffer[pos + 1])) {
                winning_num[index-1] = winning_num[index-1] * 10 + buffer[++pos] - '0';
            }
        }
    }
    return compare_numbers(buffer, winning_num, index, pos);
}

void check_card(FILE *file) {
    match_Tuple points = {0, 0};
    int32_t card_instances[ARRAY_LENGTH];
    clear_array(card_instances, ARRAY_LENGTH);
    char buffer[ARRAY_LENGTH];
    for (int32_t card = 0; fgets(buffer, ARRAY_LENGTH, file) != NULL; card++) {
        match_Tuple matches = get_matches(buffer);
        points.part1 += matches.part1;
        for (int32_t i = card+1; i < card+matches.part2+1; ++i) {
            card_instances[i] += card_instances[card]+1;
        }
        points.part2 += card_instances[card] + 1;
    }
    printf("Part1: %d\nPart2: %d\n", points.part1, points.part2);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        return -1;
    }
    check_card(file);
    fclose(file);
    return 0;
}