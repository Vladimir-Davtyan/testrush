#include "dict.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int my_strlen(char *str) {
    int len = 0;
    while (*str++) len++;
    return len;
}

void my_strcpy(char *dest, char *src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

void my_strcat(char *dest, char *src) {
    while (*dest) dest++;
    my_strcpy(dest, src);
}

Dictionary load_dictionary(char *file_path) {
    int fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        write(1, "Error opening file\n", 19);
        return NULL;
    }

    Dictionary dict = malloc(sizeof(DictionaryEntry) * DICTIONARY_SIZE);
    if (!dict) {
        close(fd);
        write(1, "Memory allocation error\n", 24);
        return NULL;
    }

    char buffer[256];
    int bytes_read;
    int index = 0;
    int start = 0;
    while ((bytes_read = read(fd, buffer + start, 255 - start)) > 0) {
        buffer[bytes_read + start] = '\0'; 

        char *line = buffer;
        while (1) {
            char *newline = line;
            while (*newline && *newline != '\n') newline++;
            if (*newline == '\n') {
                *newline = '\0';

                char *key = line;
                char *value = line;
                while (*value && *value != ':') value++;
                if (*value == ':') {
                    *value = '\0';
                    value++;
                }

                while (*value == ' ') value++;

                if (*key == '\0' || *value == '\0') {
                    line = newline + 1;
                    continue;
                }

                dict[index].key = string_to_int(key);
                dict[index].value = malloc(my_strlen(value) + 1);
                my_strcpy(dict[index].value, value);
                index++;

                line = newline + 1;
            } else {
                start = my_strlen(line);
                my_strcpy(buffer, line);
                break;
            }
        }
    }

    close(fd);
    return dict;
}

void free_dictionary(Dictionary dict) {
    for (int i = 0; i < DICTIONARY_SIZE; i++) {
        free(dict[i].value);
    }
    free(dict);
}

int get_word_from_dict(Dictionary dict, int num, char *result) {
    for (int i = 0; i < DICTIONARY_SIZE; i++) {
        if (dict[i].key == 0 && dict[i].value == NULL) break;

        if (dict[i].key == num) {
            my_strcat(result, dict[i].value);
            return 1;
        }
    }
    return 0;
}
