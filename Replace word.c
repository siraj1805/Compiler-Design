#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void replaceWordInFile(const char *fileName, const char *oldWord, const char *newWord) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Create a temporary file
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    size_t oldWordLength = strlen(oldWord);
    size_t newWordLength = strlen(newWord);

    while (fgets(line, sizeof(line), file)) {
        char *pos;
        // Write the line to the temp file, replacing occurrences of oldWord with newWord
        while ((pos = strstr(line, oldWord)) != NULL) {
            // Write the part before oldWord
            fwrite(line, 1, pos - line, tempFile);
            // Write the newWord
            fwrite(newWord, 1, newWordLength, tempFile);
            // Move past the oldWord
            line = pos + oldWordLength;
        }
        // Write the remaining part of the line
        fputs(line, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    // Rename temp file to original file
    if (remove(fileName) != 0) {
        perror("Error deleting original file");
        exit(EXIT_FAILURE);
    }
    if (rename("temp.txt", fileName) != 0) {
        perror("Error renaming temporary file");
        exit(EXIT_FAILURE);
    }

    printf("Replacement done successfully.\n");
}

int main() {
    char fileName[100];
    char oldWord[100];
    char newWord[100];

    printf("Enter the name of the file: ");
    scanf("%s", fileName);

    printf("Enter the word to replace: ");
    scanf("%s", oldWord);

    printf("Enter the new word: ");
    scanf("%s", newWord);

    replaceWordInFile(fileName, oldWord, newWord);

    return 0;
}
