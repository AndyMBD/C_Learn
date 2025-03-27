#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "file_write.h"
FILE* create_file_to_write(char *file_name);
FILE* create_file_to_write(char *file_name)
{
    FILE *output_file;
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_str[6];
    strftime(time_str, sizeof(time_str), "%H%M", tm_info);

    char new_name[256];
    char *dot = strrchr(file_name, '.');
    if (dot) {
        int base_len = dot - file_name;
        snprintf(new_name, sizeof(new_name), "%.*s_%s%s", base_len, file_name, time_str, dot);
    } else {
        snprintf(new_name, sizeof(new_name), "%s_%s", file_name, time_str);
    }
    // remove(new_name);
    output_file = fopen(new_name, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error opening output file %s!\n", new_name);
        return NULL;
    }
    return output_file;
}