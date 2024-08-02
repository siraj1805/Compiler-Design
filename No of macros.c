#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// Function to count macros and header files
void countMacrosAndHeaders(const char *filename, int *macroCount, int *headerCount) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        // Check for macro definitions
        if (strncmp(line, "#define", 7) == 0) {
            (*macroCount)++;
        }

        // Check for header file inclusions
        if (strncmp(line, "#include", 8) == 0) {
            // Check if the line includes a header file
            char *includePart = line + 8; // Skip "#include"
            while (*includePart == ' ' || *includePart == '\t') {
                includePart++;
            }
            if (*includePart == '<' || *includePart == '"') {
                (*headerCount)++;
            }
        }
    }

    fclose(file);
}

int main() {
    char filename[100];
    int macroCount = 0;
    int headerCount = 0;

    printf("Enter the name of the C source file: ");
    scanf("%s", filename);

    countMacrosAndHeaders(filename, &macroCount, &headerCount);

    printf("Number of macros defined: %d\n", macroCount);
    printf("Number of header files included: %d\n", headerCount);

    return 0;
}
