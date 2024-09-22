#include <unistd.h>
#include <stdlib.h>
#include "dict.h"
#include "converter.h"

void print_error(char *message) {
    write(1, message, 6);
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        print_error("Error\n");
        return 1;
    }

    char *dictionary_path = (argc == 3) ? argv[1] : "numbers.dict";
    char *number_to_convert = argv[argc - 1];

    if (!is_valid_number(number_to_convert)) {
        print_error("Error\n");
        return 1;
    }

    Dictionary dict = load_dictionary(dictionary_path);
    if (dict == NULL) {
        print_error("Dict Error\n");
        return 1;
    }

    char *result = convert_number_to_words(dict, number_to_convert);
    if (result == NULL) {
        print_error("Dict Error\n");
    } else {
        write(1, result, my_strlen(result));
        write(1, "\n", 1);
        free(result);
    }

    free_dictionary(dict);
    return 0;
}
