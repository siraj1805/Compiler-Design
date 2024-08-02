#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int is_comment_line(char *line) {
    // Check for single-line comment
    if (strstr(line, "//") != NULL) {
        return 1;
    }
    // Check for start of multi-line comment
    if (strstr(line, "/*") != NULL) {
        return 1;
    }
    return 0;
}

void process_file(const char *input_filename, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "r");
    FILE *output_file = fopen(output_filename, "w");
    if (input_file == NULL) {
        perror("Error opening input file");
        return;
    }
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int comment_count = 0;
    int in_multiline_comment = 0;

    while (fgets(line, sizeof(line), input_file)) {
        // Check if the line contains the end of a multi-line comment
        if (in_multiline_comment) {
            fputs("\n", output_file); // Preserve line breaks
            if (strstr(line, "*/") != NULL) {
                in_multiline_comment = 0;
            }
            continue;
        }

        // Check for single-line comments or the start of a multi-line comment
        if (is_comment_line(line)) {
            comment_count++;
            if (strstr(line, "/*") != NULL && strstr(line, "*/") == NULL) {
                in_multiline_comment = 1;
            }
            continue;
        }

        // Write non-comment lines to the output file
        fputs(line, output_file);
    }

    printf("Number of comment lines: %d\n", comment_count);

    fclose(input_file);
    fclose(output_file);
}

int main() {
    const char *input_filename = "input.c";
    const char *output_filename = "output.c";

    process_file(input_filename, output_filename);

    return 0;
}
