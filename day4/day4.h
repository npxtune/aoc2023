
#ifndef AOC2023_DAY4_H
#define AOC2023_DAY4_H
typedef struct matches{
    int32_t part1;
    int32_t part2;
} match_Tuple;

void clear_array(int32_t *array, int32_t length) {
    for (int i = 0; i < length; ++i) {
        array[i] = 0;
    }
}
#endif //AOC2023_DAY4_H
