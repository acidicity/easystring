#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <es/string.h>


String string_init(char *str) {
    String string;
    
    int length = strlen(str);

    string.length = length;
    string.capacity = length + 1;
    string.contents = malloc(string.capacity);

    memcpy(string.contents, str, length);
    string.contents[string.length] = '\0';

    return string;
}

void string_free(String str) {
    free(str.contents);
}

char* string_to_cstr(String str) {
    return str.contents;
}

void string_concat(String *str_a, String str_b) {
    int new_length = str_a->length + str_b.length;

    if (new_length > str_a->length)
        str_a->contents = realloc(str_a->contents, new_length + 1);
    else
        return;
    
    memcpy(str_a->contents + str_a->length, str_b.contents, str_b.length);

    str_a->length = new_length;
    str_a->capacity = new_length + 1;
    str_a->contents[str_a->length] = '\0';
}

void string_concat_cstr(String *str_a, char *str_b) {
    String temp = string_init(str_b);

    string_concat(str_a, temp);
}

int string_find(String str_a, String str_b) {
    for (int i = 0; i < str_a.length; i++) {
        int j;
        for (j = 0; j < str_b.length; j++) {
            if (string_to_cstr(str_a)[i+j] == string_to_cstr(str_b)[j])
                continue;
            else 
                break;
        }
        
        if (j != str_b.length)
            continue;

        return i;
        
    }
    return ES_STRING_ERROR;
}

int string_find_cstr(String str_a, char *str_b) {
    String temp = string_init(str_b);

    return string_find(str_a, temp);
}

int string_startswith(String str_a, String str_b) {
    int index = string_find(str_a, str_b);
    if(index == 0)
        return 1;
    else 
        return 0;
}

int string_startswith_cstr(String str_a, char *str_b) {
    String temp = string_init(str_b);

    return string_startswith(str_a, temp);
}

int string_endswith(String str_a, String str_b) {
    for (int i = 0; i < str_b.length ; i++)
    {
        if(string_to_cstr(str_a)[str_a.length - i] == string_to_cstr(str_b)[str_b.length - i])
            continue;
        
        return 0;
    }
    
    return 1;
}

int string_endswith_cstr(String str_a, char *str_b) {
    String temp = string_init(str_b);

    return string_endswith(str_a, temp);
}

int string_compare(String str_a, String str_b) {
    if(str_a.length == str_b.length && string_find(str_a, str_b) == 0 || str_a.contents[0] == '\0' && str_b.contents[0] == '\0')
        return 1;
    else
        return 0;
}

int string_compare_cstr(String str_a, char *str_b) {
    String temp = string_init(str_b);

    return string_compare(str_a, temp);
}

String string_slice(String str, int start, int end) {
    if (start > end) {
        fprintf(stderr, "Error : string_slice() - the provided start is lesser than the end.");
        exit(ES_STRING_ERROR);
    }

    if(start == end) {
        fprintf(stderr, "Error: string_slice() - the provided start and the end are equal.");
        exit(ES_STRING_ERROR);
    }
    
    if(end > str.length) {
        fprintf(stderr, "Error: string_slice() - the provided end is greater than the length of the string.");
        exit(ES_STRING_ERROR);
    }

    String slice;

    slice.length = end - start;
    slice.capacity = slice.length + 1;
    slice.contents = (char *)malloc(slice.capacity);

    memcpy(slice.contents, str.contents + start, slice.length);

    slice.contents[slice.length] = '\0';

    return slice;
}

String string_read_file(FILE *fp) {
    
    String str;
    
    if (fp == NULL)
    {
        fprintf(stderr, "Error: string_read_file() - the provided file pointer is NULL.");
        exit(ES_STRING_ERROR);
    }

    fseek(fp, 0, SEEK_END);
    long bytes = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    str.length = bytes;
    str.capacity = str.length + 1;
    str.contents = (char *)malloc(str.capacity);
    
    fread(str.contents, sizeof(char), str.length, fp);

    str.contents[str.length] = '\0';

    return str;    
}