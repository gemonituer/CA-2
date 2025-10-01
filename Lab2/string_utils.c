#include "string_utils.h"
#include <ctype.h>

size_t string_length(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int count_digits(const char *str) {
    int digit_count = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            digit_count++;
        }
    }
    return digit_count;
}

void to_upper_case(char *str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        str[i] = (char)toupper((unsigned char)str[i]);
    }
}
