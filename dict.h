#ifndef DICTIONARY_H
#define DICTIONARY_H

#define DICTIONARY_SIZE 100

typedef struct {
    int key;
    char *value;
} DictionaryEntry;

typedef DictionaryEntry* Dictionary;

int my_strlen(char *str);
void my_strcpy(char *dest, char *src);
void my_strcat(char *dest, char *src);

Dictionary load_dictionary(char *file_path);
void free_dictionary(Dictionary dict);
int get_word_from_dict(Dictionary dict, int num, char *result);

int string_to_int(char *str);
int is_valid_number(char *str);

#endif
