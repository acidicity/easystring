#ifndef ES_STRING_H
#define ES_STRING_H

#include <stdio.h>

#define ES_STRING_ERROR -1

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct {
    int length;
    int capacity;
    char *contents;
} String;

String string_init(char *str);

void string_free(String str);

char* string_to_cstr(String str);

void string_concat(String *str_a, String str_b);

void string_concat_cstr(String *str_a, char *str_b);

int string_find(String str_a, String str_b);

int string_find_cstr(String str_a, char *str_b);

int string_startswith(String str_a, String str_b);

int string_startswith_cstr(String str_a, char *str_b);

int string_endswith(String str_a, String str_b);

int string_endswith_cstr(String str_a, char *str_b);

int string_compare(String str_a, String str_b);

int string_compare_cstr(String str_a, char *str_b);

String string_slice(String str, int start, int end);

String string_read_file(FILE *fp);

#if defined(__cplusplus)
}
#endif

#endif // ES_STRING_H