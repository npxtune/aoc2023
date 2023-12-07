#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "struct_types.h"

#define MAXLINE 200

uint32_t parse_digit(char line_buffer[], const int32_t index) {   // "Parse" the digit
    if (line_buffer[index-3] == ' ') {
        return digittoint(line_buffer[index-2]);
    }
    return digittoint(line_buffer[index-3]) * 10 + digittoint(line_buffer[index-2]);
}

void check_word(char* file_buffer, const lookup_t* words, cube_colours* max_digit, const int32_t i) {
    for (int32_t j = 0; j < 3; j++) {
        if (strncmp(words[j].word, &file_buffer[i], strlen(words[j].word)) == 0) {
            const uint32_t current_digit = parse_digit(file_buffer, i);
            switch (j) {
                case 0: // blue
                    max_digit->blue = fmax(current_digit, max_digit->blue);
                    break;
                case 1: // red
                    max_digit->red = fmax(current_digit, max_digit->red);
                    break;
                case 2: // green
                    max_digit->green = fmax(current_digit, max_digit->green);
                    break;
                default:
                    break;
            }
        }
    }
}

cube_colours get_digit(char file_buffer[], lookup_t words[]) {
    cube_colours max_digit = {0,0,0};
    for (int32_t i = 0; file_buffer[i] != '\0'; i++) {  // Check the entire line in the file buffer for matching words
        check_word(file_buffer, words, &max_digit, i);
    }
    return max_digit;
}

void check_input(FILE* ptr, const cube_colours limit, lookup_t words[]) {
    uint32_t sum_game_id = 0, current_game_id = 1, game_powers = 0;
    while (!feof(ptr)) {
        char* file_buffer = fgets(file_buffer, MAXLINE, ptr);
        const cube_colours max_digit = get_digit(file_buffer, words); // Get matching words + digits from the input file
        if (max_digit.red <= limit.red && max_digit.blue <= limit.blue && max_digit.green <= limit.green) {
            sum_game_id += current_game_id++;
        }
        game_powers += max_digit.red * max_digit.green * max_digit.blue;
    }
    printf("\nPower: %d", game_powers);
    printf("\nSum: %d\n", sum_game_id);
}

int32_t main() {
    FILE* ptr = fopen("input", "r");
    if (ptr == NULL) {
        printf("Error, can't read file content!\n");
        return -1;
    }
    check_input(ptr, (cube_colours){12, 13, 14}, (lookup_t[]){{"blue"}, {"red"}, {"green"}});
    return 0;
}