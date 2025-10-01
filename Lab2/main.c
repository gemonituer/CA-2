#include <stdio.h>
#include <stdlib.h>
#include "string_utils.h"

#define INITIAL_BUFFER_SIZE 100

int main() {
    char *str = malloc(INITIAL_BUFFER_SIZE);
    if (str == NULL) {
        perror("Memory allocation error");
        return 1;
    }

    size_t capacity = INITIAL_BUFFER_SIZE;
    size_t length = 0;
    int ch;

    printf("Enter a string: ");

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            capacity *= 2;
            char *new_str = realloc(str, capacity);
            if (new_str == NULL) {
                free(str);
                perror("Memory reallocation error");
                return 1;
            }
            str = new_str;
        }

        str[length++] = (char)ch;
    }

    str[length] = '\0';

    printf("\nString length: %zu\n", string_length(str));

    printf("Number of digits in the string: %d\n", count_digits(str));

    to_upper_case(str);
    printf("String in upper case: %s\n", str);

    free(str);

    return 0;
}
