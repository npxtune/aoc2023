#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXLINE 200

typedef struct {
    uint32_t red;
    uint32_t green;
    uint32_t blue;
} cube_colours;

typedef struct {
    char* word;
} lookup_t;

uint32_t get_digit(char line_buffer[], const int32_t index) {
    if (line_buffer[index-3] == ' ') {
        return digittoint(line_buffer[index-2]);
    }
    return digittoint(line_buffer[index-3]) * 10 + digittoint(line_buffer[index-2]);
}

void check_cubes(FILE* ptr, const cube_colours limit, lookup_t words[]) {
    char file_buffer[MAXLINE];
    uint32_t sum_game_id = 0, current_game_id = 1, game_powers = 0;
    while (!feof(ptr)) {
        cube_colours minimum_digit = {0,0,0};
        fgets(file_buffer, MAXLINE, ptr);
        for (int32_t i = 0; file_buffer[i] != '\0'; i++) {
            for (int32_t j = 0; j < 3; j++) {
                if (strncmp(words[j].word, &file_buffer[i], strlen(words[j].word)) == 0) {
                    const uint32_t current_digit = get_digit(file_buffer, i);
                    switch (j) {
                        case 0: // blue
                            minimum_digit.blue = fmax(current_digit, minimum_digit.blue);
                            break;
                        case 1: // red
                            minimum_digit.red = fmax(current_digit, minimum_digit.red);
                            break;
                        case 2: // green
                            minimum_digit.green = fmax(current_digit, minimum_digit.green);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        if (minimum_digit.red <= limit.red && minimum_digit.blue <= limit.blue && minimum_digit.green <= limit.green) {
            sum_game_id += current_game_id++;
        }
        game_powers += minimum_digit.red * minimum_digit.green * minimum_digit.blue;
    }
    printf("\nPower: %d", game_powers);
    printf("\nSum: %d\n", sum_game_id);
}

int32_t main() {
    const lookup_t words[] = {    // Words to check for
        {"blue"},
        {"red"},
        {"green"}
    };
    FILE* ptr = fopen("input", "r");
    if (ptr == NULL) {
        printf("Error, can't read file content!\n");
        return -1;
    }
    check_cubes(ptr, (cube_colours){12, 13, 14}, words);
    return 0;
}