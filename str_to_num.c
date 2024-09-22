#include <limits.h>

int string_to_int(char *str) {
    unsigned long long num = 0;

    while (*str) {
        if (*str < '0' || *str > '9') {
            return -1;
        }
        num = num * 10 + (*str - '0');
        str++;

        if (num > INT_MAX) {
            return -1;
        }
    }
    return (int)num;
}

int is_valid_number(char *str) {
    if (*str == '\0') {
        return 0;
    }

    while (*str) {
        if (*str < '0' || *str > '9') {
            return 0;
        }
        str++;
    }
    return 1;
}
