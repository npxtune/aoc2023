#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAXLINE 200

typedef struct {
    uint16_t red;
    uint16_t green;
    uint16_t blue;
} cube_colours;

typedef struct {
    char* word;
    uint8_t number;
} lookup_t;

enum colour_numbers {blue, red, green};

uint32_t check_cubes(FILE* ptr, cube_colours limit, lookup_t words[]) {
    char file_buffer[MAXLINE];
    uint32_t sum_game_id = 0, current_game_id = 1;
    cube_colours colours = {0,0,0};
    while (!feof(ptr)) {
        bool is_valid = true;
        fgets(file_buffer, MAXLINE, ptr);
        for (int32_t i = 0; i < MAXLINE && file_buffer[i] != '\0'  && is_valid == true; i++) {
            for (int32_t j = 0; j < 3; j++) {
                if (strncmp(words[j].word, &file_buffer[i], strlen(words[j].word)) == 0) {
                    switch (words[j].number) {
                        case blue:
                            colours.blue = file_buffer[i-3] == ' ' ? digittoint(file_buffer[i-2]) : digittoint(file_buffer[i-3]) * 10 + digittoint(file_buffer[i-2]);
                            if (colours.blue > limit.blue) {
                                is_valid = false;
                            }
                            break;
                        case red:
                            colours.red = file_buffer[i-3] == ' ' ? digittoint(file_buffer[i-2]) : digittoint(file_buffer[i-3]) * 10 + digittoint(file_buffer[i-2]);
                            if (colours.red > limit.red) {
                                is_valid = false;
                            }
                            break;
                        case green:
                            colours.green = file_buffer[i-3] == ' ' ? digittoint(file_buffer[i-2]) : digittoint(file_buffer[i-3]) * 10 + digittoint(file_buffer[i-2]);
                            if (colours.green > limit.green) {
                                is_valid = false;
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        if (is_valid == true) {
            sum_game_id += current_game_id;
        }
        current_game_id++;
    }
    return sum_game_id;
}

int32_t main() {
    const cube_colours colour_limit = {12, 13, 14};    // Limit of colored cubes to check for

    const lookup_t words[] = {    // Words to check for
        {"blue", blue},
        {"red", red},
        {"green", green}
    };
    FILE* ptr = fopen("input", "r");
    if (ptr == NULL) {
        printf("Error, can't read file content!\n");
        return -1;
    }
    printf("\nSum: %d", check_cubes(ptr, colour_limit, words));
    return 0;
}