#include "converter.h"
#include "dict.h"
#include <stdlib.h>
#include <unistd.h>

char *convert_number_to_words(Dictionary dict, char *number) {
    char *result = malloc(256);
    if (!result) return NULL;
    result[0] = '\0';

    int num = string_to_int(number);
    if (!get_word_from_dict(dict, num, result)) {
        free(result);
        return NULL;
    }

    return result;
}
